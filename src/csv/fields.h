#ifndef FIELDS_H
#define FIELDS_H
/* fields.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for fields.c. Defines a field structure which represents
 * the metadata for a column.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <string.h>

/* Local. */
#include "datatype.h"
#include "../generic/table.h"
#include "../generic/util.h"

/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * Fields are used to store information about a Table. Typically, each Column in
 * a Row has a corresponding Field, which is shared across like Columns. Fields
 * contain data that is not part of the data itself. This metadata is parsed from
 * the table header row, which should contain a declaration for each Column:
 *
 *     field_name (data_type)
 *
 * The information is not part of Table, because it is not relevant to the Table.
 * Instead, it is a higher-level representation of data, and is only used to
 * assist in interpreting (sorting, etc.) the data within a Table.
 */
typedef struct Field
{
    /* The position within each row. */
    int columnID;

    /* The type of data stored in columns of this field. */
    FieldDataType dataType;

    /* The name of the field. This should be used only for displaying data,
     * not for comparisons; for comparisons, use the case-insensitive sortKey. */
    char *fieldName;

    /* The string to use for case-sensitive comparisons of the field name. */
    char *sortKey;
} Field;

/*
 * FieldLists are used to store a list of Fields. One FieldList should correspond
 * to exactly one Table; where each Field represents a set of Columns at some
 * index of each Row.
 */
typedef struct FieldList
{
    int fieldCount;
    Field **fields;

} FieldList;

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Constructor Functions. */
FieldList *createFieldList(int);
Field *createField(int, char *, char *, FieldDataType);

/* Accessor Functions. */
int getFieldIndexBySortKey(FieldList *, char *);
Field *getFieldBySortKey(FieldList *, char *);
int getFieldColumnID(Field *);
int getFieldDataType(Field *);
const char *getFieldDataTypeName(Field *);
char *getFieldSortKey(Field *);
char *getFieldName(Field *);

/* Mutator Functions. */
void setFieldDataType(Field *, int);
void setFieldDataTypeName(Field *, char *);
void setFieldColumnID(Field *, int);
void setFieldName(Field *, char *);
void setFieldSortKey(Field *, char *);

/* Parsing Functions. */
char *readFieldName(char *);
char *readFieldDataType(char *);
FieldList *readTableFields(Table *);

/* Destruction Functions. */
void freeFieldList(FieldList *);
void freeField(Field *);

#endif
