/* parser.c
 * 
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions for interacting CSV files. See also
 * Table.c which contains the structure used to represent CSV tables.
 */
#include "parser.h"

/********************************************************************************
 *                            VALIDATION FUNCTIONS                              *
 ********************************************************************************/

/*
 * Validates a CSV string against illegal (unprintable) characters.
 * Returns true if the string is OK to parse, false otherwise.
 * The length is required so that we can correctly parse strings that contain the
 * null-terminator character \0.
 */
bool isValidCSVString(char *str, int length)
{
    /* Whether or not this string is valid. */
    bool isValid = true;

    /* Position we are at within the string. */
    int pos = 0;

    /* Test each character against an illegal set of characters. */
    while (isValid && pos < length)
    {
        isValid = isValidTextFileCharacter(str[pos]);
        pos++;
    }

    return isValid;
}

/*
 * Validates a CSV file's contents against illegal (unprintable) characters.
 * Returns true if the file is OK to parse; false otherwise.
 */
bool isValidCSVFile(FILE *fPtr)
{
    /* The number of bytes read. We use this to check if we've reached the end. */
    int bytesRead = 0;

    /* Whether or not the file is valid. Assume it is true. */
    bool isValid = true;

    /* The buffer to temporarily read file contents. */
    char *buf = (char *)malloc(FILE_READ_BUFFER_SIZE * sizeof(char));
    
    do
    {
        /* Read from the file and check if there are any invalid characters. */
        bytesRead = fread(buf, sizeof(char), FILE_READ_BUFFER_SIZE, fPtr);
        isValid = isValidCSVString(buf, bytesRead);
    } while (isValid && bytesRead == FILE_READ_BUFFER_SIZE);

    /* Free the file reading buffer we created. */
    free(buf);

    return isValid;
}

/*
 * Determines if a character is terminating a column. A character is terminating
 * a column if:
 * (a)
 *   (1) the parser is in escaped mode; AND
 *   (2) the character is not in the set { E0F }.
 * OR
 * (b)
 *   (1) the parser is not in escaped mode; AND
 *     (i)  the parser is in literal mode; AND
 *     (ii) the character is in the set { '"', EOF };
 *     OR
 *     (i)  the parser is not in literal mode; AND
 *     (ii) the character is in the set { ',', '\n', '\r', EOF }.
 */
bool isEndingColumn(char c, bool isInLiteralMode, bool isInEscapeMode)
{
    /* Whether or not this character ends the column. */
    bool isEnding = false;

    /* Different rules apply if the parser is in literal mode. */
    if (isInEscapeMode)
    {
        /* We must still check for the EOF even in escape mode. */
        isEnding = (c == EOF);
    }
    else
    {
        if (isInLiteralMode)
        {
            /* In escape mode you can do: \" - so if we're in escape mode, don't
             * read the DQUOTE as a terminator. */
            isEnding = (c == '"' || c == EOF);

        }
        else
        {
            isEnding = (c == ',' || c == '\n' || c == '\r' || c == EOF);
        }
    }

    return isEnding;
}

/********************************************************************************
 *                             PARSING FUNCTIONS                                *
 ********************************************************************************/

/*
 * Internal use only. Parses a column starting at the string specified.
 * Returns the Column parsed.
 */
static int parseColumn(ParserStateManager *manager, char **str,
    Column **pColumn)
{
    int status = 0;
    ParserState *state = getParserState(manager);
    Column *column = NULL;

    /* Create a dynamic string to store the column value. This structure allows
     * us to continue appending to it and then generate the whole string instead
     * of creating an arbitrarily large buffer to store it, which may not be
     * sufficient space. */
    DynamicString *columnValue = NULL;

    /* Parse the column. */
    char c = **str;

    if (getParserStateType(state) == PARSER_STATE_PARSE_COLUMN)
    {
        /* We've already started parsing the column. Recover the state. */
        column = getStateColumn(state);
        columnValue = getColumnValue(column);
    }
    else
    {
        /* This is a new state - we're parsing a new column. Create a new
         * state and create a buffer to store the column value in. */
        state = createParserState(manager, PARSER_STATE_PARSE_COLUMN);
        column = createColumn();

        columnValue = getColumnValue(column);
        setColumnValue(column, columnValue);

        setStateColumn(state, column);
        setStateColumnStart(state, true);
    }

    /* If the 'column start' state is active, then we should try to trim
     * any leading whitespace. This is important because the first non-whitespace
     * character has an important meaning, and we don't know what that is yet.
     * When we are done, check for any special meanings of the first
     * non-whitespace character. */
    if (getStateColumnStart(state))
    {
        /* At the start of each column, check for a column delimiter (','). If we
         * are continuing from a column on the same row, then we will encounter a
         * comma to separate the two columns. We do this here, because if we
         * consumed the delimiter at the end of each column parsed, then the
         * parseRow function would ignore an empty column at the end of a line,
         * and prematurely end the row. Validation would fail and the program
         * would produce errors. Thus, The order of parsing is important. DO NOT
         * MOVE THIS UNLESS YOU UNDERSTAND THE CONSEQUENCES OF THIS. */
        if (c == ',')
        {
            /* Consume the ',' by moving to the next address. */
            (*str)++;
            c = **str;
        }

        /* Skip over all leading whitespace characters. */
        while (isWhitespace(c))
        {
            (*str)++;
            c = **str;
        }

        /* Per RFC 4180(2)(5): the double quote appearing as the first character
         * in a column makes this column literal. */
        if (c == '"')
        {
            setStateColumnLiteralMode(state, true);
            /* Consume the double quotes, they are not part of the value. */
            (*str)++;
            c = **str;
        }
        setStateColumnStart(state, false);
    }

    /* Parse the actual column. We may encounter the end of the string before we
     * encounter the end of the column. In this case, we should stop processing
     * and (later) indicate that we're not done yet. */
    while (!isEndingColumn(c, getStateColumnLiteralMode(state),
        getStateColumnEscapedMode(state)) && c != '\0')
    {
        if (c == '\\' && !getStateColumnEscapedMode(state))
        {
            /* This is an escape character. We need to escape the next
             * character. */
            setStateColumnEscapedMode(state, true);
        }
        else
        {
            /* this is a valid character. Add it to the column value; then,
             * remove (consume) the literal mode flag as it only applies to one
             * character. */
            appendCharToDynamicString(columnValue, **str);
            setStateColumnEscapedMode(state, false);
        }
        (*str)++;
        c = **str;

    }

    /* If this was a literal column, end the sequence. */
    if (getStateColumnLiteralMode(state))
    {
        /* Check if the next character is an (ending) double-quote. */
        if (c == '"')
        {
            /* Good. Skip over it. */
            (*str)++;
            c = **str;
            setStateColumnLiteralMode(state, false);
        }
        else
        {
            /* This column was supposed to be in literal mode, but it did not
             * terminate with a closing double quote. It appears this is an
             * invalid CSV file. */
        }
    }

    /* Check if we've reached a character that terminates the column. These
     * characters are: ',' (next column), '\r' and/or '\n' (next line),
     * and EOF (end table).
     * If we've found anything else, then we must wait for the next time
     * this function is called to continue parsing. This is the whole purpose
     * of storing the state - so that we can restore if needed. */
    if (isEndingColumn(c, getStateColumnLiteralMode(state),
        getStateColumnEscapedMode(state)))
    {
        /* We're done with this state now. We've finished parsing the column. */
        endState(manager, state);
        /* We've ended the state. We need to end the row & table. */
        status = PARSE_COMPLETE;
    }
    else
    {
        /* If we've found the end of the string (null-terminator), then
         * signal that we've reached the end of the fragment and need
         * additional information to continue. */
        status = PARSE_INCOMPLETE;
    }

    /* If the caller specified where to assign the column, then do so. */
    if (pColumn != NULL)
    {
        *pColumn = column;
    }

    return status;
}

/*
 * Internal use only. Parses a row from the string specified.
 * Returns the Row parsed.
 */
static int parseRow(ParserStateManager *manager, char **str, Row **pRow)
{
    int status = PARSE_INCOMPLETE;
    ParserState *state = getParserState(manager);
    char c = **str;
    Row *row;

    if (getParserStateType(state) == PARSER_STATE_PARSE_ROW)
    {
        /* We've already started parsing the row. Recover the state. */
        row = getStateRow(state);
    }
    else
    {
        /* This is a new state. Create the state and the data it needs. */
        row = createRow();
        state = createParserState(manager, PARSER_STATE_PARSE_ROW);
        setStateRow(state, row);
    }

    /* 'state' should not be NULL anymore. */


    /* Attempt parsing lines. */
    while (c != '\n' && c != '\r' && c != '\0' && c != EOF)
    {
        Column *col = NULL;
        /* Parse columns until we reach the end of the line. */
        parseColumn(manager, str, &col);

        /* Add each column to the row. */
        addRowColumn(row, col);

        /* Update c so that the while condition is changed. */
        c = **str;
    }

    /* Check if we've reached a character that terminates the line. These
     * characters are: '\n' (next line), EOF (end table).
     * If we've found anything else, then we must wait for the next time
     * this function is called to continue parsing the line. This is the
     * reason we store 'recovery information' inside a state manager. */
    if (c == '\n' || c == '\r' || c == EOF)
    {
        /* We've finished parsing the line. End the state. */
        endState(manager, state);
        status = PARSE_COMPLETE;
    }
    else
    {
        /* Signal to the caller that we need additional information to continue
         * parsing this row. */
        status = PARSE_INCOMPLETE;
    }

    /* Handle Windows-based new-lines. It's not likely that a user
     * enters a carriage return (0xD), so assume it starts a new line. */
    if (c == '\r')
    {
        /* Consume the '\r' by moving to the next address. */
        (*str)++;
        c = **str;
    }

    /* If we found a newline, then we are starting a new row.
     * Consume the '\n' token. */
    if (c == '\n')
    {
        /* Consume the '\n' by moving to the next address. */
        (*str)++;
    }

    if (pRow != NULL)
    {
        *pRow = row;
    }

    return status;
}

/*
 * Internal use only. Parses a string containing a fragment of a CSV table.
 */
static int parseTable(ParserStateManager *manager, char **str, Table **table)
{
    int status = 0;
    ParserState *state = getParserState(manager);

    /* If we have a state, recover from it.  */
    if (state != NULL)
    {
        if (getParserStateType(state) == PARSER_STATE_PARSE_TABLE)
        {
            /* We've already started parsing the table. Recover the state. */
            *table = getStateTable(state);
        }
    }
    else
    {
        /* This is a new state. Create the state and the table. */
        state = createParserState(manager, PARSER_STATE_PARSE_TABLE);
        *table = createTable();
        setStateTable(state, *table);
    }

    if (*table != NULL)
    {
        char c = **str;
        /* Parse lines until we reach the end of file, or a null-terminator. */
        while (c != EOF && c != '\0')
        {
            Row *row = NULL;
            parseRow(manager, str, &row);
            addTableRow(*table, row);
            c = **str;
        }

        /* If we encountered the end of file, we've finished parsing the table.
         * If we've encountered anything else (i.e., a null-terminator), then
         * we need additional information to continue parsing this table. */
        if (c == EOF)
        {
            endState(manager, state);
            status = PARSE_COMPLETE;
        }
        else
        {
            status = PARSE_INCOMPLETE;
        }
    }

    return status;
}

/*
 * Parses a CSV file and exports the resulting Table.
 * Returns an error code, or 0 on success.
 */
int parse(FILE *fPtr, Table **ptr)
{
    int status = PARSE_INCOMPLETE;

    /* The length of the buffer. This is how many bytes we can consume from
     * the CSV file at a time. */
    int bufferLength = 0xFFFF;

    /* The number of bytes read from the stream. */
    int bytesRead;

    /* Table to output to. */
    Table *table = NULL;

    /* Allocate a block of memory to store a fragment of the file. */
    char *buf = (char *)calloc(bufferLength + 1, sizeof(char));

    /* The parser's state manager. This structure allows us to store
     * information (state) between function calls, so that we can parse
     * small parts of the file sequentially. */
    ParserStateManager *manager = createParserStateManager();

    while ((bytesRead = fread(buf, sizeof(char), bufferLength, fPtr)))
    {
        /* A reference to the buffer. We need a copy of this address
         * because we plan on iterating across the buffer many times, and the
         * start & pivot both need to be retained. */
        char *bufPos = buf;

        /* A reference to the copy of the buffer's address, so that the called
         * functions can change the address pointed to. This is only relevant
         * within this loop, because if we retained the value throughout the
         * function then we'd need to reset the pointers to the start of the 
         * buffer every iteration anyway. */
        char **bufPtr = &bufPos;

        if (bytesRead < bufferLength)
        {
            /* Signal the end of stream for the parser. */
            buf[bytesRead] = EOF;
        }

        while (**bufPtr != EOF && **bufPtr != '\0')
        {
            ParserState *state = getParserState(manager);
            int stateType = getParserStateType(state);

            if (stateType == PARSER_STATE_PARSE_COLUMN)
            {
                parseColumn(manager, bufPtr, NULL);
            }
            else if (stateType == PARSER_STATE_PARSE_ROW)
            {
                parseRow(manager, bufPtr, NULL);
            }
            else
            {
                status = parseTable(manager, bufPtr, &table);
            }

        }
    }

    if (ptr != NULL)
    {
        /* If the user has passed a reference pointer to which we can assign the
         * table, then do so. */
        *ptr = table;
    }
    else
    {
        /* The caller didn't pass an address to which we can export the table.
         * This is probably an error, but not necessarily. */
        status = ERROR_MISSING_REFERENCE_POINTER;
    }


    /* We've finished parsing. Free the dynamic memory that we've allocated to
     * perform the parsing. */
    free(buf);
    buf = NULL;
    freeStateManager(manager);

    return status;
}
