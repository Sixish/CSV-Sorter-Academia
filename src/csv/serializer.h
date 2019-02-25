#ifndef SERIALIZER_H
#define SERIALIZER_H
/* serializer.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for serializer.h.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "../generic/table.h"
#include "errors.h"


/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Serialize */
int serializeCSVTable(Table *, DynamicString **);
int serializeCSVRow(Row *, DynamicString *);
int serializeCSVColumn(Column *, DynamicString *);

#endif
