/* menu.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Handles the menu functions.
 */
#include "menu.h"

/********************************************************************************
 *                            PROMPTING FUNCTIONS                               *
 ********************************************************************************/

/*
 * Reads a line from the user and converts it to a string that is comparable.
 *
 * This function attempts to read a line between 0 and INPUT_BUFFER_LENGTH
 * characters long; this input is then trimmed of any leading and trailing
 * whitespace characters and converted to lowercase for effective,
 * case-insensitive comparisons.
 */
char *readComparableLine(void)
{
    /* Create the buffer. */
    char lineBuf[INPUT_BUFFER_LENGTH];

    /* The input once it has been (1) trimmed, and (2) trimmed and converted to
     * lower-case. We need to store these separately so that we can free them,
     * because the functions we use create copies, they do not not modify the
     * original strings. */
    char *lineTrimmed = NULL;
    char *lineLowerCase = NULL;

    /* Read a line from stdin. We are using fgets because it's portable, and
     * because it reads a full line: the user is expected to enter a newline
     * after their desired sort column. We want to consume this newline. */
    fgets(lineBuf, INPUT_BUFFER_LENGTH, stdin);

    /* Remove any leading or trailing whitespace. */
    lineTrimmed = trimWhitespace(lineBuf);

    /* Allow case insensitive matches. */
    lineLowerCase = toLowerCase(lineTrimmed);

    /* Free the memory that we don't need anymore. */
    free(lineTrimmed);

    return lineLowerCase;
}

/*
 * Reads a filename from the standard input stream.
 * 
 * This function reads a line from the user and removes the trailing newline.
 */
char *readFileName(void)
{
    /* Create the buffer. */
    char lineBuf[INPUT_BUFFER_LENGTH];

    /* The input once it has been (1) trimmed, and (2) trimmed and converted to
     * lower-case. We need to store these separately so that we can free them,
     * because the functions we use create copies, they do not not modify the
     * original strings. */
    char *lineTrimmed = NULL;
    char *lineLowerCase = NULL;

    /* Read a line from stdin. We are using fgets because it's portable, and
     * because it reads a full line: the user is expected to enter a newline
     * after their desired sort column. We want to consume this newline. */
    fgets(lineBuf, INPUT_BUFFER_LENGTH, stdin);

    /* Remove any leading or trailing whitespace. */
    lineTrimmed = trim(lineBuf, "\n", 1);

    /* Free the memory that we don't need anymore. */
    free(lineTrimmed);

    return lineLowerCase;
}

/*
 * Prompts the user for a file name.
 *
 * This function takes a message to send to the user before prompting for a file
 * name. It then reads a line and trims ONLY new line characters from the input.
 *
 * Validation:
 * Linux is very loose when it comes to valid filenames. No validation is
 * performed on the filename. However, our program will not behave well with a
 * filename that has a newline in it because we use the newline to indicate the
 * end of the token (filename).
 *
 * Most Linux distributions have a maximum filename length of 255 characters.
 * However, because we want to accept all kinds of paths (not just filenames),
 * we won't perform validation on the length and assume that the user is aware of
 * what they are doing.
 */
char *menuPromptFileName(char *prompt)
{
    char *filename = (char *)malloc(LIMIT_FILENAME_CHARS * sizeof(char));
    /* Prompt the user for the filename. */
    printf("%s", prompt);
    filename = readFileName();

    /* It's unlikely that the filename consumes LIMIT_FILENAME_CHARS chars.
     * reduce the block of memory to the size it actually consumes, + 1 for
     * the null-terminator. */
    filename = realloc(filename, (strlen(filename) + 1) * sizeof(char));

    return filename;
}

/*
 * Takes a FieldList and prompts the user for one of the items within the list.
 * This will export the result which corresponds to the column being sorted.
 */
Field *menuSortColumnFromList(FieldList *list)
{
    int c;
    char *input = NULL;
    Field *field = NULL;

    printf(" -----+--------------------------------+------------\n");
    printf("| %-3s | %-30s | %-10s |\n", "num", "field", "datatype");
    printf("|-----+--------------------------------+------------|\n");
    for (c = 0; c < list->fieldCount; c++)
    {
        Field *field = list->fields[c];

        /* Print the option to the user. */
        printf("| %3d | %-30s | %-10s |\n", c, field->fieldName,
            translateIntToDataType(field->dataType));
    }
    printf(" -----+--------------------------------+------------\n");

    printf("Sort by which column?\nColumn: ");
    input = readComparableLine();
    field = getFieldBySortKey(list, input);
    while (field == NULL)
    {
        printf("Oops! \"%s\" is not a column.\nColumn: ", input);
        free(input);
        input = readComparableLine();
        field = getFieldBySortKey(list, input);
    }
    free(input);

    return field;
}

/*
 * Prompts the user to enter a column to sort by.
 */
void menuSortColumn(SortConfig *sortConfig, Table *table)
{
    /* Get a list of all the header row's columns. */
    FieldList *list = readTableFields(table);

    /* The Field selected by the user. */
    Field *userChoice = NULL;

    /* We've populated the two arrays of strings. Prompt the user for an option
     * inside the arrays. */
    userChoice = menuSortColumnFromList(list);

    /* Store the choice inside the container so that we can use it when we are
     * sorting. */
    setSortColumn(sortConfig, getFieldColumnID(userChoice));
    setSortColumnName(sortConfig, getFieldName(userChoice));
    setSortDataType(sortConfig, getFieldDataType(userChoice));

    /* We're done with the FieldList; free the memory associated with it. */
    freeFieldList(list);
}

void menuSortOrder(SortConfig *config)
{
    /* The sort type as defined as a preprocessor constant. */
    int sortOrder;

    /* The line string entered by the user. */
    char *line = NULL;

    /* Prompt the user. */
    printf("Sort {Ascending} or {Descending}? Or {Shuffle} the data?\nOrder: ");

    /* Read a line from the input stream. */
    line = readComparableLine();
    printf("\n");

    while (strcmp(line, "ascending") && strcmp(line, "descending") &&
        strcmp(line, "shuffle"))
    {
        /* Repeat the process until the user enters a valid string. */
        printf("That choice was invalid. Try again: \n");
        free(line);
        line = readComparableLine();
    }

    /* The user has entered "ascending", "descending" or "shuffle". */

    /* Compare the first characters. We can do this because the first character
     * of each option is unique across the set of options and line is guaranteed
     * to be valid at this point. */
    switch (*line)
    {
        case 'a':
            /* User entered 'ascending'. */
            sortOrder = SORT_ORDER_ASC;
            break;
        case 'd':
            /* user entered 'descending'. */
            sortOrder = SORT_ORDER_DESC;
            break;
        case 's':
            /* User entered 'shuffle'. */
            sortOrder = SORT_ORDER_SHUFFLE;
            break;
        default:
            /* This should never happen, but OK. */
            sortOrder = SORT_ORDER_ASC;
            break;
    }

    /* The line we read was dynamically allocated. Free it since it's no longer
     * needed. */
    free(line);
    /* Apply the sort order to the configuration. */
    setSortOrder(config, sortOrder);
}

