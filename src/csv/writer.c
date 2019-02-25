/* writer.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Handles writing a CSV Table to a file.
 */
#include "writer.h"

/********************************************************************************
 *                             UTILITY FUNCTIONS                                *
 ********************************************************************************/

/*
 * Writes a Table to a file in the CSV format.
 * Returns an error code, or 0 on success.
 */
int write(char *filename, Table *table)
{
    /* The error code to be returned. */
    int errorCode = 0;

    /* The file stream we are writing to. */
    FILE *fPtr = NULL;

    /* Open the file for writing. */
    fPtr = fopen(filename, "w");

    if (fPtr != NULL)
    {
        DynamicString *dStr = NULL;
        if (!serialize(table, &dStr))
        {
            char *text = serializeDynamicString(dStr);

            /* We've opened the file for writing. Write the contents. */
            fwrite(text, sizeof(char), getDynamicStringLength(dStr), fPtr);

            /* The dynamic string allocated a block of memory for the serialized
             * string. Free the memory since we're not using it anymore. */
            free(text);

            /* Close the stream. */
            fclose(fPtr);
        }
        else
        {
            /* We failed to serialize the Table. */
        }
        freeDynamicString(dStr);
    }
    else
    {
        /* We failed to open the file for writing. This may have been due to
         * a permissions error. */
        errorCode = ERROR_OPENING_FILE;
    }

    return errorCode;
}

/*
 * Serializes the Table contained within the container, and exports the result,
 * a DynamicString structure, to the address pointed to by outDynStr.
 */
int serialize(Table *table, DynamicString **outDynStr)
{
    /* The error code to be returned. */
    int errorCode = 0;

    /* Check if there's any table to serialize. If not, then we have nothing
     * to do. */
    if (table != NULL && outDynStr != NULL)
    {
        DynamicString *dStr = NULL;
        serializeCSVTable(table, &dStr);
        if (dStr != NULL)
        {
            *outDynStr = dStr;
        }
        else
        {
            errorCode = ERROR_SERIALIZING_TABLE;
        }
    }

    return errorCode;
}

