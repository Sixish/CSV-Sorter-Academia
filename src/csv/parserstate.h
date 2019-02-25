#ifndef PARSERSTATE_H
#define PARSERSTATE_H
/* parserstate.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for parserstate.c. Defines structures used to contain
 * a parser's state.
 */

/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

#include "../generic/stack.h"
#include "../generic/table.h"
#include "../generic/linkedlist.h"

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

typedef enum
{
    PARSER_STATE_PARSE_TABLE,
    PARSER_STATE_PARSE_ROW,
    PARSER_STATE_PARSE_COLUMN
} ParserStateType;


/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * This structure stores the state of the parser.
 * It's used to facilitate 'partial parsing', so that we do not need a full, valid
 * CSV string to attempt parsing.
 * Overall, the use of this structure means:
 * - Lower memory usage. Files do not need to be fully loaded before
 *   they can be parsed.
 * - Looser restrictions on the size of data. Since there's no need to store
 *   the whole string, a buffer does not need to be created to contain such a
 *   string. This results in a larger supported filesize limited mostly by the
 *   available system memory.
 */
typedef struct ParserStateManager
{
    Stack *states;
} ParserStateManager;

/*
 * Represents a State of the parser. Because C doesn't support inheritance, we
 * are using aggregation to mimic the functionality.
 */
typedef struct ParserState
{
    int type;
    void *state;
} ParserState;

/*
 * A specialized state. Indicates that the parser is currently parsing a Column.
 */
typedef struct ParseColumnState
{
    Column *column;
    /* Determines if we are still parsing the 'start' of the column, where
     * we trim whitespace and interpret double quotes. */
    bool stateStart;
    /* Determines if we are in 'escaped mode', where a single following character
     * is treated as literal. */
    bool stateEscapedMode;

    /* Determines if we are in 'literal mode', where all characters are treated
     * as literals (i.e., meaningless) including newlines and commas which
     * would otherwise change the state (terminate columns or lines). */
    bool stateLiteralMode;
} ParseColumnState;

/*
 * A specialized state. Indicates that the parser is currently parsing a Row.
 */
typedef struct ParseRowState
{
    Row *row;

} ParseRowState;

/*
 * A specialized state. Indicates that the parser is currently parsing a Table.
 */
typedef struct ParseTableState
{
    Table *table;

} ParseTableState;


/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Constructor Functions. */
ParserStateManager *createParserStateManager(void);
ParserState *createParserState(ParserStateManager *, int);
ParseTableState *createParseTableState(void);
ParseRowState *createParseRowState(void);
ParseColumnState *createParseColumnState(void);

/* Accessor Functions. */
ParserState *getParserState(ParserStateManager *);
int getParserStateType(ParserState *);
bool getStateColumnStart(ParserState *);
bool getStateColumnEscapedMode(ParserState *);
bool getStateColumnLiteralMode(ParserState *);
void setStateRow(ParserState *, Row *);
Row *getStateRow(ParserState *);
Table *getStateTable(ParserState *);
bool parserStateManagerIsEmpty(ParserStateManager *);

/* Mutator Functions. */
Column *getStateColumn(ParserState *);
void setStateColumn(ParserState *, Column *);
void setStateColumnStart(ParserState *, bool);
void setStateColumnEscapedMode(ParserState *, bool);
void setStateColumnLiteralMode(ParserState *, bool);
void setStateTable(ParserState *, Table *);

/* Destructor Functions. */
void endState(ParserStateManager *, ParserState *);
void freeStateTable(ParseTableState *);
void freeStateRow(ParseRowState *);
void freeStateColumn(ParseColumnState *);
void freeState(ParserState *);
void freeStateManager(ParserStateManager *);

#endif
