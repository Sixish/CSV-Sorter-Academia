/* errors.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines errors and their corresponding output messages.
 */
#include "errors.h"

/*******************************************************************************
 *                             ACCESSOR FUNCTIONS                              *
 *******************************************************************************/

/*
 * Gets the error message from an error code.
 */
const char *getErrorMessage(int errorCode)
{
    const char *msg = NULL;
    switch (errorCode)
    {
        case STATUS_OK:
            msg = "(OK)";
            break;
        case ERROR_INVALID_INPUT_FILENAME:
            msg = "Input filename is not valid.";
            break;
        case ERROR_INVALID_OUTPUT_FILENAME:
            msg = "Output filename is not valid.";
            break;
        case ERROR_UNRECOGNIZED_ARGUMENT:
            msg = "Unrecognized command line argument.";
            break;
        case ERROR_OPENING_FILE:
            msg = "Could not open the file.";
            break;
        case ERROR_INVALID_FILE_FORMAT:
            msg = "The file format was invalid.";
            break;
        case ERROR_SERIALIZING_TABLE:
            msg = "Failed to serialize the table.";
            break;
        case ERROR_MISSING_PARSE_TABLE:
            msg = "No parse table provided.";
            break;
        case ERROR_MISSING_PARSE_CONTAINER:
            msg = "No parse container provided.";
            break;
        case ERROR_TABLE_INCOMPLETE:
            msg = "The end of file was not found.";
            break;
        default:
            msg = "An unknown error occurred.";
            break;
    }
    return msg;
}

