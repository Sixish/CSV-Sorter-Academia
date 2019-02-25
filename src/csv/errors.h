#ifndef ERRORS_H
#define ERRORS_H
/* errors.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines error codes and functions to translate it to a useful error
 * message.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdlib.h>

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

#define STATUS_OK 0
#define ERROR_INVALID_INPUT_FILENAME 1
#define ERROR_INVALID_OUTPUT_FILENAME 2
#define ERROR_UNRECOGNIZED_ARGUMENT 3
#define ERROR_OPENING_FILE 4
#define ERROR_INVALID_FILE_FORMAT 5
#define ERROR_SERIALIZING_TABLE 6
#define ERROR_MISSING_PARSE_TABLE 7
#define ERROR_MISSING_PARSE_CONTAINER 8
#define ERROR_TABLE_INCOMPLETE 9
#define ERROR_MISSING_COMPARATOR 10
#define ERROR_INTERNAL_NO_OUTPUT_ADDRESS 11

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

const char *getErrorMessage(int);

#endif
