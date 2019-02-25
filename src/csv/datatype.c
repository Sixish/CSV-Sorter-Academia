/* datatype.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Contains functions for interacting with data types supported by the
 * CSV sorting program.
 */
#include "datatype.h"

/********************************************************************************
 *                             ACCESSOR FUNCTIONS                               *
 ********************************************************************************/

/*
 * Translates a string to a FieldDataType enum.
 * {"int", "integer"} => DATATYPE_INTEGER
 * {"string"} => DATATYPE_STRING
 */
FieldDataType translateDataTypeToEnum(char *str)
{
    FieldDataType type = DATATYPE_INVALID;
    /* Make sure the caller passed a string. If not, then the datatype is left
     * as invalid. */
    if (str != NULL)
    {
        /* Compare the strings with each data type name. */
        if (!strcmp(str, "int") || !strcmp(str, "integer"))
        {
            /* The strings match - this is an integer. */
            type = DATATYPE_INTEGER;
        }
        else if (!strcmp(str, "string"))
        {
            /* The strings match - this is a string. */
            type = DATATYPE_STRING;
        }
    }

    return type;
}

/*
 * Translates an integer, as defined by the preprocessor constants, to a string.
 * This function returns a const string; and thus deallocation is handled by the
 * compiler.
 */
const char *translateIntToDataType(int dataTypeId)
{
    /* The data type name. */
    const char *dataTypeName;

    switch (dataTypeId)
    {
        case DATATYPE_INTEGER:
            /* This value represents an integer. */
            dataTypeName = "number";
            break;
        case DATATYPE_STRING:
            /* This value represents a string. */
            dataTypeName = "string";
            break;
        default:
            /* I have no idea. You're on your own. */
            dataTypeName = "UNKNOWN";
            break;
    }

    return dataTypeName;
}

