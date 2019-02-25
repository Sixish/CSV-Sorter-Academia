/* validator.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions related to CSV Table validation.
 */
#include "validator.h"

/********************************************************************************
 *                                 VALIDATION                                   *
 ********************************************************************************/

/*
 * Checks that the imported table has an equal number of columns in each row.
 */
int validate(Table *table)
{
    int errorCode = 0;
    if (table != NULL)
    {
        int lineNumber = 0;
        /* Assume that the header row contains the exact number of columns
         * that we are expecting. */
        int expectedColumnCount = getColumnCount(table->headerRow);

        /* Node whose Row we are checking. */
        LinkedListNode *node = getLinkedListHead(table->rows);

        /* Iterate across all nodes until we reach the end, or encounter a
         * validation error. */
        while (node != NULL)
        {
            Row *row = (Row *)getNodeValue(node);
            lineNumber++;

            /* Check if this row has the expected number of columns. */
            if (getColumnCount(row) != expectedColumnCount)
            {
                errorCode = ERROR_INVALID_NUMBER_OF_COLUMNS;
            }

            /* Continue on with the next (unless we encountered an error). */
            node = node->nextNode;
        }
    }

    return errorCode;
}

