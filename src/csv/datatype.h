#ifndef DATATYPE_H
#define DATATYPE_H
/* datatype.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines data types supported by the CSV sort program.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdlib.h>
#include <string.h>

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

typedef enum
{
    DATATYPE_INVALID,
    DATATYPE_STRING,
    DATATYPE_INTEGER
} FieldDataType;

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Functions to translate between integers and strings. */
FieldDataType translateDataTypeToEnum(char *);
const char *translateIntToDataType(int);

#endif
