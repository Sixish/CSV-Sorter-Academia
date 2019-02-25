/* table.c
 * 
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions for interacting with tables, generic containers
 * which have dynamic rows and columns.
 */
#include "table.h"


/********************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Creates a Table and initializes it with default values.
 * This function should always be used over initializing a struct,
 * because it initializes references properly such that garbage
 * does not create internal conflicts.
 */
Table *createTable(void)
{
    /* Create and initialize the table. */
    Table *ptr = (Table *)malloc(sizeof(Table));

    Table table;
    table.headerRow = NULL;
    table.rows = NULL;

    *ptr = table;
    return ptr;
}

/*
 * Creates a row, returning a pointer to the row.
 */
Row *createRow(void)
{
    Row *ptr = (Row *)malloc(sizeof(Row));

    ptr->columns = NULL;
    return ptr;
}

/*
 * Dynamically creates a column. Exports the Column created.
 */
Column *createColumn(void)
{
    Column *ptr = (Column *)malloc(sizeof(Column));
    Column column;
    column.value = createDynamicString();
    
    *ptr = column;
    return ptr;
}
/********************************************************************************
 *                             ACCESSOR FUNCTIONS                               *
 ********************************************************************************/

/*
 * Gets the last row in a table.
 */
Row *getLastRow(Table *table)
{
    Row *row = NULL;
    if (table->rows != NULL)
    {
        LinkedListNode *node = getLinkedListTail(table->rows);
        row = (Row *)getNodeValue(node);
    }

    return row;
}

/*
 * Gets the number of rows in a table, not including the header row.
 */
int getRowCount(Table *table)
{
    int count = 0;
    if (table != NULL && table->rows != NULL)
    {
        count = getNodeCount(table->rows);
    }
    return count;
}

/*
 * Gets the header row of a table.
 */
Row *getHeaderRow(Table *table)
{
    Row *row = table->headerRow;
    return row;
}

/*
 * Gets a column from the row.
 */
Column *getRowColumn(Row *row, int depth)
{
    Column *col = NULL;

    /* Get the node at depth=depth. If this is NULL, return NULL.
     * Otherwise, get the node value and return that. */
    col = (Column *)getLinkedListValueAt(row->columns, depth);

    return col;
}

/*
 * Gets the number of columns in a row.
 */
int getColumnCount(Row *row)
{
    int count = 0;
    if (row != NULL && row->columns != NULL)
    {
        count = getNodeCount(row->columns);
    }
    return count;
}

/*
 * Gets the value of a column.
 */
DynamicString *getColumnValue(Column *column)
{
    DynamicString *value = NULL;
    if (column != NULL)
    {
        value = column->value;
    }
    return value;
}

/*
 * Gets the text value of a column at the specified position in the specified row.
 */
char *getRowColumnValue(Row *row, int index)
{
    /* Get the (index)'th column of the row. */
    Column *col = getRowColumn(row, index);

    /* Finally, serialize the column to get its value. */
    char *value = serializeColumn(col);

    return value;
}

/*
 * Converts the column to string format for comparisons.
 */
char *serializeColumn(Column *column)
{
    char *str = NULL;
    if (column != NULL)
    {
        DynamicString *dStr = NULL;

        dStr = getColumnValue(column);
        if (dStr != NULL)
        {
            str = serializeDynamicString(dStr);
        }
    }

    return str;
}

/********************************************************************************
 *                             MUTATOR FUNCTIONS                                *
 ********************************************************************************/

/*
 * Removes a table row from the specified table. This abstracts the logic of how
 * rows are removed from the table. Functions that remove from tables should
 * never implement this logic themselves.
 */
Row *removeTableRow(Table *table, Row *row)
{
    Row *removedRow = (Row *)removeLinkedListValue(table->rows, (void *)row);

    /* Return the row that we've just removed. */
    return removedRow;
}

/*
 * Sets the header row of a table.
 */
void setHeaderRow(Table *table, Row *row)
{
    /* Set the header row. */
    table->headerRow = row;
}

/*
 * Appends a column to the row.
 */
void addRowColumn(Row *row, Column *col)
{
    if (row->columns == NULL)
    {
        row->columns = createLinkedList();
    }
    addValue(row->columns, col);
}

/*
 * Sets the value of a column.
 */
void setColumnValue(Column *column, DynamicString *dStr)
{
    if (column != NULL)
    {
        column->value = dStr;
    }
}

/*
 * Adds a table row to the specified table. This abstracts the logic of how
 * rows are added to the table. Functions that append to tables should never
 * implement this logic themselves.
 */
void addTableRow(Table *table, Row *row)
{
    if (table->headerRow == NULL)
    {
        /* The first row will be the header. */
        setHeaderRow(table, row);
    }
    else
    {
        /* This is not a header row. Check if we've got a head for the linked
         * list. If not, create it. */
        if (table->rows == NULL)
        {
            /* If we've got a header row but not a linked list node of rows,
             * create the latter. */
            table->rows = createLinkedList();
        }

        /* Add the row to the linked list. */
        addValue(table->rows, row);
    }
}

/********************************************************************************
 *                            INFORMATION FUNCTION                              *
 ********************************************************************************/

/*
 * Prints a table.
 */
void printTable(Table *table)
{
    if (table->rows != NULL)
    {
        printRows(table->rows);
    }
}

/*
 * Prints information contained in a list of rows.
 */
void printRows(LinkedList *root)
{
    int rowNumber = 0;
    LinkedListNode *node = getLinkedListHead(root);
    while (node != NULL)
    {
        Row *row = (Row *)getNodeValue(node);

        printf("|%-3d|", ++rowNumber);
        printColumns(row->columns);
        printf("\n");

        node = getNextNode(node);
    }
}


/*
 * Prints information about the columns in a linked list of rows.
 */
void printColumns(LinkedList *list)
{
    LinkedListNode *node = getLinkedListHead(list);
    while (node != NULL)
    {
        Column *column = (Column *)getNodeValue(node);
        DynamicString *dStr = getColumnValue(column);

        printf("%-10s|", serializeDynamicString(dStr));
        node = getNextNode(node);
    }
}

/********************************************************************************
 *                             SORTING FUNCTIONS                                *
 ********************************************************************************/

/*
 * Sorts table rows according to the given sorting function.
 */
void sortTableRows(Table *table, void *config,
    LinkedListComparator sortFn)
{
    LinkedList *root = table->rows;

    /* Sort the linked list. We don't need to export the list, since the table
     * is passed to us. */
    sortLinkedList(root, config, sortFn);
}


/********************************************************************************
 *                            DESTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Frees all memory associated with a Table.
 */
void freeTable(Table *table)
{
    if (table != NULL)
    {
        /* Current row node we are working on freeing. */
        LinkedListNode *rowNode = getLinkedListHead(table->rows);

        /* Iterate across all rows and free them. */
        while (rowNode != NULL)
        {
            Row *row = (Row *)getNodeValue(rowNode);
            freeRow(row);
            rowNode = getNextNode(rowNode);
        }

        /* Free the LinkedList. */
        freeLinkedList(table->rows);

        /* Prevent future attempts to use this pointer. */
        table->rows = NULL;

        /* Free the header row. */
        if (table->headerRow != NULL)
        {
            freeRow(table->headerRow);
            /* Prevent future attempts to use this pointer. */
            table->headerRow = NULL;
        }
        /* Finally, free the allocated memory for the Table itself. */
        free(table);
    }
}

/*
 * Frees all memory associated with a Row.
 */
void freeRow(Row *row)
{
    if (row != NULL)
    {
        /* current column we are working on freeing. */
        LinkedListNode *columnNode = getLinkedListTail(row->columns);

        /* Iterate across all columns and free them. */
        while (columnNode != NULL)
        {
            Column *column = (Column *)getNodeValue(columnNode);
            freeColumn(column);
            columnNode = getPrevNode(columnNode);
        }
        /* Free the LinkedList. */
        freeLinkedList(row->columns);

        /* Finally, free the allocated memory for the Row itself. */
        free(row);
    }
}

/*
 * Frees all memory associated with a Column.
 */
void freeColumn(Column *column)
{
    if (column != NULL)
    {
        DynamicString *dStr = getColumnValue(column);
        if (dStr != NULL)
        {
            /* Free the column's string value. */
            freeDynamicString(dStr);
        }

        /* Null the field to prevent future use of this address. */
        column->value = NULL;

        /* Finally, free the memory containing the Column itself. */
        free(column);
    }
}

