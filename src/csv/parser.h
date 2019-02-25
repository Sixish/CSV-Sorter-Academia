#ifndef PARSER_H
#define PARSER_H
/* parser.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for parser.c.
 */

/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../generic/linkedlist.h"
#include "../generic/dynamicstring.h"
#include "../generic/util.h"
#include "../generic/table.h"
#include "parserstate.h"

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

/* Macros for file limitations. */
#define COLUMN_TERMINATOR_COUNT 5
#define LINE_TERMINATOR_COUNT   1

#define PARSE_COMPLETE 1
#define PARSE_INCOMPLETE 2

#define ERROR_MISSING_REFERENCE_POINTER 2

#define FILE_READ_BUFFER_SIZE 0xF

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/************** Forward Declarations *************/ 

/* Validation functions. */
bool isValidCSVString(char *, int);
bool isValidCSVFile(FILE *);

/* Parsing functions. */
int parse(FILE *, Table **);


/* Interactions with parser states. */
ParserStateManager *createParserStateManager(void);
ParserState *getParserState(ParserStateManager *);
void endState(ParserStateManager *, ParserState *);
ParserState *createParserState(ParserStateManager *, int);
ParseTableState *createParseTableState(void);
ParseRowState *createParseRowState(void);
ParseColumnState *createParseColumnState(void);
int getParserStateType(ParserState *);

/* Columns */
void setStateColumn(ParserState *, Column *);
void setStateColumnStart(ParserState *, bool);
void setStateColumnEscapedMode(ParserState *, bool);

Column *getStateColumn(ParserState *);
bool getStateColumnStart(ParserState *);
bool getStateColumnEscapedMode(ParserState *);

/* Rows */
void setStateRow(ParserState *, Row *);
Row *getStateRow(ParserState *);

/* Tables */
void setStateTable(ParserState *, Table *);
Table *getStateTable(ParserState *);

#endif

