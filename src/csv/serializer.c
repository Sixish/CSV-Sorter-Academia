/* serializer.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions used to serialize a Table in CSV format.
 */
#include "serializer.h"

/********************************************************************************
 *                           SERIALIZING FUNCTIONS                              *
 ********************************************************************************/

/*
 * Converts a CSV table to a string. This is not handled by table.c because Table
 * is a generic container structure. This takes a table and serializes it.
 */
int serializeCSVTable(Table *table, DynamicString **ptr)
{
    int errorCode = 0;

    if (ptr != NULL)
    {
        /* Create a dynamic string so that we can have an arbitrarily large
         * string. */
        DynamicString *output = createDynamicString();

        /* The current row node. */
        LinkedListNode *rowNode = getLinkedListHead(table->rows);

        /* The current row. */
        Row *row = getHeaderRow(table);

        /* Read the header row first. */
        serializeCSVRow(row, output);

        while (rowNode != NULL)
        {
            /* Get the row from the node. */
            row = (Row *)getNodeValue(rowNode);

            /* Because there was definitely a header row; append a newline to
             * start a new row. */
            appendCharToDynamicString(output, '\n');
            
            /* Serialize the row. */
            serializeCSVRow(row, output);

            /* Repeat the process for the next row. */
            rowNode = getNextNode(rowNode);
        }

        /* Assign the output to the reference parameter. */
        *ptr = output;
    }
    else
    {
        errorCode = ERROR_INTERNAL_NO_OUTPUT_ADDRESS;
    }

    return errorCode;
}

/*
 * Converts a CSV Row to a string.
 */
int serializeCSVRow(Row *row, DynamicString *dStr)
{
    int errorCode = 0;
    /* Current column node we are serializing. */
    LinkedListNode *node = getLinkedListHead(row->columns);
    bool hasCol = false;

    /* Iterate across all column nodes and serialize the values within. */
    while (node != NULL)
    {
        /* The current column. */
        Column *column = (Column *)getNodeValue(node);

        /* Check if we've already serialized a column for this row. If we have,
         * we need to delimit the two columns with a column separator (comma). */
        if (hasCol)
        {
            /* Append a comma to delimit the previous column and the current
             * column. */
            appendCharToDynamicString(dStr, ',');
        }

        /* Serialize the column. */
        serializeCSVColumn(column, dStr);
        hasCol = true;

        /* Repeat the process for the next node. */
        node = getNextNode(node);
    }
    return errorCode;
}

/*
 * Converts a CSV Column to a string.
 */
int serializeCSVColumn(Column *column, DynamicString *dStr)
{
    int errorCode = 0;
    char *data = serializeColumn(column);
    /* Get the value from the table. */
    appendStringToDynamicString(dStr, data);

    /* The DynamicString took a copy of the value. We still need to free this
     * ourselves. */
    free(data);
    return errorCode;
}

