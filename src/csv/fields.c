/* fields.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions for creating and interacting with Fields - metadata
 * containers for Columns.
 */
#include "fields.h"

/*********************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                               *
 *********************************************************************************/

/*
 * Creates and initializes a FieldList with enough size for the specified number
 * of Fields. This function does not create any Fields.
 */
FieldList *createFieldList(int count)
{
    /* Allocate memory for the FieldList. */
    FieldList *list = (FieldList *)malloc(sizeof(FieldList));

    /* Initialize the fields as appropriate. */
    list->fields = (Field **)malloc(count * sizeof(Field *));
    list->fieldCount = count;

    return list;
}

/*
 * Creates and initializes a Field, which stores high-level data about a column
 * in a Table.
 * are not columns
 */
Field *createField(int columnID, char *fieldName, char *sortKey,
    FieldDataType dataType)
{
    Field *field = (Field *)malloc(sizeof(Field));
    
    /* Initialize the fields. */
    setFieldColumnID(field, columnID);
    setFieldDataType(field, dataType);
    setFieldSortKey(field, sortKey);
    setFieldName(field, fieldName);

    return field;
}


/*********************************************************************************
 *                             PARSING FUNCTIONS                                 *
 *********************************************************************************/

/*
 * Reads a Field name from a header row's column value.
 */
char *readFieldName(char *str)
{
    const char wsChars[] = { '\t', '\r', '\n', ' ', '\f' };
    char *fieldName = NULL;
    int len = 0;
    /* Find the end of the string. */
    len = strlen(str);

    /* Len now stores the length of the whole string. However, we only want
     * to include the text up until the last opening brackets, less any whitespace
     * prior to it. Navigate backwards until we find a character matching this. */
    if (len)
    {
        while (len && str[len] != '(')
        {
            len--;
        }

        if (str[len] == '(')
        {
            /* Len now stores the length of the fieldname, plus whitespace, plus
             * 1 additional character for the opening bracket. */
            len--;
        }

        /* Len now stores the length of the field name plus whitespace. */
        while (len && charMatches(str[len], wsChars, 5))
        {
            len--;
        }

        /* Len now stores the position of the last item in the field name. */
        len++;

        /* Len now stores the length of the field name. */
        
        /* Allocate the memory for the string, and copy from the imported. */
        fieldName = (char *)malloc((len + 1) * sizeof(char));
        strncpy(fieldName, str, len);
        fieldName[len] = '\0';
    }

    return fieldName;
}

/*
 * Reads a Field's data type from a header row's colum value.
 */
char *readFieldDataType(char *str)
{
    char *dataType = NULL;
    int end = 0, start = 0;
    /* Find the end of the string. */
    end = strlen(str);

    /* Len now stores the length of the whole string. However, we only want
     * to include the text between the last set of brackets. Navigate backwards
     * until we find the last closing bracket in the string. */
    if (end)
    {
        while (end && str[end] != ')')
        {
            end--;
        }
        /* End now stores the length of the string within the brackets. We are
         * assuming that the brackets does not contain whitespace. */
        start = end;
        while (start && str[start] != '(')
        {
            start--;
        }
        /* Start now stores the position of the first opening bracket. */
        start++;
        printf("%d", (end - start));

        /* Start now stores the start position of the datatype string. */

        /* Allocate memory and copy memory from the imported to the string. */
        if ((end - start) > 0)
        {

            dataType = (char *)malloc((end - start + 1) * sizeof(char));
            strncpy(dataType, &str[start], end - start);
            
            /* Set the null-terminator so that we don't overrun the stirng when
             * using it. */
            dataType[end - start] = '\0';
        }
    }

    return dataType;
}

/*
 * Reads a set of Fields from a Table. This function retrieves the header row
 * from the table and parses each column in sequence to determine the column ID,
 * field name and data type. The function collects all of this data and returns it
 * inside a FieldList container.
 */
FieldList *readTableFields(Table *table)
{
    Row *row = getHeaderRow(table);

    /* Retrieve the number of columns and thus, how many fields we need to
     * allocate memory for. */
    int columns = getColumnCount(row);

    /* Create a field list to store the fields in. */
    FieldList *list = createFieldList(columns);

    int i;

    /* Populate the string arrays with options. */
    for (i = 0; i < columns; i++)
    {
        /* Strings for processing only. These must be freed. */
        char *procStr = NULL, *strDataType = NULL;

        /* The actual data that is stored in the Field. */
        char *sortKey = NULL, *fieldName = NULL;
        FieldDataType dataType;

        /* The header row column we're taking the string from. */
        Column *column = getRowColumn(row, i);
        
        /* Use the Column's serialize function to create copies of the value.
         * Because the function creates copies, we don't need to allocate the
         * memory ourselves (but we will need to free it!). */
        procStr = serializeColumn(column);

        /* We've got the column contents. We need to extract the field name
         * and data type from this column. */
        fieldName = readFieldName(procStr);
        strDataType = readFieldDataType(procStr);

        /* The data type as a string is no use to us. Translate it to an int. */
        dataType = translateDataTypeToEnum(strDataType);

        /* We're done with the serialized column and data type string. These were
         * only used as intermediary variables and should be freed now that they
         * are of no use to us. */
        free(strDataType);
        free(procStr);

        /* The sort key is the actual key as entered by the user. This basically
         * allows us to prompt the user for case in-sensitive field names. */
        sortKey = toLowerCase(fieldName);

        /* Create the field and add it to the list. */
        list->fields[i] = createField(i, fieldName, sortKey, dataType);
    }

    return list;
}

/*********************************************************************************
 *                             ACCESSOR FUNCTIONS                                *
 *********************************************************************************/
char *getFieldSortKey(Field *field)
{
    char *sortKey = NULL;
    if (field != NULL)
    {
        sortKey = field->sortKey;
    }
    return sortKey;
}

/*
 * Checks if the field has the specified sort key.
 */
bool fieldHasSortKey(Field *field, char *sortKey)
{
    char *fieldSortKey = getFieldSortKey(field);

    /* If strcmp returns 0, then the field has the sort key. */
    return !strcmp(fieldSortKey, sortKey);
}

/*
 * Finds and returns the first Field in a FieldList containing a specified sort
 * key.
 */
Field *getFieldBySortKey(FieldList *list, char *sortKey)
{
    Field *field = NULL;
    if (list != NULL)
    {
        int i = 0, count = list->fieldCount;
        Field **fields = list->fields;

        while (i < count && !fieldHasSortKey(fields[i], sortKey))
        {
            i++;
        }

        if (i < count)
        {
            field = fields[i];
        }

    }
    return field;
}

/*
 * Finds and returns the position of the first Field in the FieldList with the
 * specified sort key. If the sort key is not found, returns -1.
 */
int getFieldIndexBySortKey(FieldList *list, char *sortKey)
{
    int index = -1;
    if (list != NULL)
    {
        int i = 0, fieldCount = list->fieldCount;

        /* Iterate across all fields. */
        while (i < fieldCount && index == -1)
        {
            Field *field = list->fields[i];

            if (!strcmp(sortKey, field->sortKey))
            {
                index = i;
            }
            i++;
        }
    }

    return index;
}

/*
 * Gets the column ID from a Field. This corresponds to the position within each
 * row of the Table.
 */
int getFieldColumnID(Field *field)
{
    int id = -1;
    if (field != NULL)
    {
        id = field->columnID;
    }
    return id;
}

/*
 * Gets the data type ID from a Field. This corresponds to the data type each
 * column can contain. For a string representation (name) of the data type, use
 * getFieldDataTypeName().
 */
int getFieldDataType(Field *field)
{
    int dataType = DATATYPE_INVALID;
    if (field != NULL)
    {
        dataType = field->dataType;
    }
    return dataType;
}

/*
 * Gets the data type name from a Field. For comparisons, prefer to use the data
 * type ID as retrieved by getfieldDataType().
 */
const char *getFieldDataTypeName(Field *field)
{
    int dataType = DATATYPE_INVALID;
    const char *dataTypeName = NULL;
    if (field != NULL)
    {
        dataType = field->dataType;
    }

    dataTypeName = translateIntToDataType(dataType);
    return dataTypeName;
}

/*
 * Gets the name of the field.
 */
char *getFieldName(Field *field)
{
    char *fieldName = NULL;
    if (field != NULL)
    {
        fieldName = field->fieldName;
    }
    return fieldName;
}

/*********************************************************************************
 *                             MUTATOR FUNCTIONS                                 *
 *********************************************************************************/

/*
 * Sets a Field's name. This function takes a pointer to a string which will be
 * used as the name of the field. That is, the function will not copy the string;
 * and freeing the string after assignment causes undefined behavior.
 */
void setFieldName(Field *field, char *name)
{
    if (field != NULL)
    {
        field->fieldName = name;
    }
}

/*
 * Sets a Field's sort key. This function takes a pointer to a string which will
 * be used as the sort key of the field. That is, the function will not copy the
 * string; and freeing the string after assignment causes undefined behavior.
 */
void setFieldSortKey(Field *field, char *sortKey)
{
    if (field != NULL)
    {
        field->sortKey = sortKey;
    }
}

/*
 * Sets a Field's data type. This data type should, but is not required to, be
 * as defined by a preprocessor constant (DATATYPE_NUMBER, DATATYPE_STRING).
 */
void setFieldDataType(Field *field, int newDataType)
{
    if (field != NULL)
    {
        field->dataType = newDataType;
    }
}

/*
 * Sets a Field's data type based on a data type's name. For efficiency, the
 * Field struct does not store data type names; the input will be translated to
 * a corresponding data type and will be stored as an integer.
 */
void setFieldDatatypeName(Field *field, char *dataTypeName)
{
    if (field != NULL)
    {
        /* We don't store the data type itself; only an integer representing
         * it. */
        setFieldDataType(field, translateDataTypeToEnum(dataTypeName));
    }
}

/*
 * Sets a Field's Column ID. This column ID should, but is not required to,
 * correspond to the position of a Column within each Row of a Table.
 */
void setFieldColumnID(Field *field, int columnID)
{
    if (field != NULL)
    {
        field->columnID = columnID;
    }
}


/*********************************************************************************
 *                            DESTRUCTOR FUNCTIONS                               *
 *********************************************************************************/
/*
 * Frees all memory associated with a FieldList, including the Fields within it.
 */
void freeFieldList(FieldList *list)
{
    if (list != NULL)
    {
        int i, len = list->fieldCount;
        for (i = 0; i < len; i++)
        {
            freeField(list->fields[i]);
        }
        free(list->fields);
        free(list);
    }
}

/*
 * Frees all memory associated with a Field.
 */
void freeField(Field *field)
{
    if (field != NULL)
    {
        if (field->sortKey != NULL)
        {
            free(field->sortKey);
        }
        if (field->fieldName != NULL)
        {
            free(field->fieldName);
        }
        free(field);
    }
}
