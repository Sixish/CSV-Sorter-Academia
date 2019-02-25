/* reader.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions related to the reading of a CSV file.
 */
#include "reader.h"

/********************************************************************************
 *                             UTILITY FUNCTIONS                                *
 ********************************************************************************/

/*
 * Takes a stream and passes it to the parse function defined by the parser. This
 * function serves as a proxy for the parse function - it translates the status
 * message returned by parse into something we can use for this program.
 */
int proxyParse(FILE *fPtr, Table **ptr)
{
    int errorCode = STATUS_OK, result = 0;

    result = parse(fPtr, ptr);
    switch (result)
    {
        case PARSE_INCOMPLETE:
            errorCode = ERROR_TABLE_INCOMPLETE;
            break;
        case PARSE_COMPLETE:
        default:
            errorCode = STATUS_OK;
            break;
    }

    return errorCode;
}

int read(char *filename, Table **ptrTable)
{
    /* Error code to be returned. */
    int errorCode = 0;

    /* File stream we are using to read the file. */
    FILE *fPtr = NULL;

    /* Open the file. */
    fPtr = fopen(filename, "r");
    if (fPtr != NULL)
    {
        /* Check if the file is a valid CSV file. */
        if (isValidCSVFile(fPtr))
        {
            Table *table = NULL;
            /* Rewind the file stream so that we can parse it. */
            rewind(fPtr);

            /* We know it's valid, so parse the file. */
            errorCode = proxyParse(fPtr, &table);

            /* Assign the parsed table to the container so that we can use it
             * elsewhere. */
            *ptrTable = table;
        }
        else
        {
            errorCode = ERROR_INVALID_FILE_FORMAT;
        }

        /* We're done with the file. Close it. */
        fclose(fPtr);
    }
    else
    {
        /* File could not be opened. Might not exist? */
        errorCode = ERROR_OPENING_FILE;
    }

    return errorCode;
}

