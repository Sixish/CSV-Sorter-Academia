#ifndef TABLE_H
#define TABLE_H
/* table.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for table.c:
 *   Includes library dependencies of table.c functions;
 *   Defines macro definitions used by table.c;
 *   Declares type definitions for Tables;
 *   Declares function prototypes for external files.
 */


/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "linkedlist.h"
#include "dynamicstring.h"


/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * Defines the type of a column. This structure contains information about
 * what is stored in the corresponding column. A Column will typically be
 * contained within a list of Rows.
 */
typedef struct
{
    /* Value of the column. */
    DynamicString *value;
} Column;

/*
 * Defines the type of a row. This structure contains a dynamic list of
 * columns. A Row is typically contained by a Table.
 */
typedef struct
{
    /* Dynamic list of columns. */
    LinkedList *columns;
} Row;

/*
 * Defines the type of a table. This structure contains a dynamic list of
 * rows stored in the table, as well as a header row which is to be excluded
 * from sorting.
 */
typedef struct
{
    /* Header row. */
    Row *headerRow;

    /* Dynamic list of rows. */
    LinkedList *rows;
} Table;


/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Constructor Functions. */
Table *createTable(void);
Row *createRow(void);
Column *createColumn(void);

/* Accessor Functions. */
int getRowCount(Table *);
int getColumnCount(Row *);
Row *getHeaderRow(Table *);
Row *getLastTableRow(Table *);
Column *getRowColumn(Row *, int);
DynamicString *getColumnValue(Column *);
char *serializeColumn(Column *);
char *getRowColumnValue(Row *, int);

/* Mutator Functions. */
void setHeaderRow(Table *, Row *);
void addTableRow(Table *, Row *);
void addRowColumn(Row *, Column *);
void setColumnValue(Column *, DynamicString *);
Row *removeTableRow(Table *, Row *);

/* Sorting */
void sortTableRows(Table *, void *, LinkedListComparator sortFn);

/* Information Functions. */
void printTable(Table *);
void printRows(LinkedList *);
void printColumns(LinkedList *);

/* Destructor Functions. */
void freeTable(Table *);
void freeRow(Row *);
void freeColumn(Column *);

#endif
