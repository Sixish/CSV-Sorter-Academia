#ifndef WRITER_H
#define WRITER_H
/* writer.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for writer.c.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "errors.h"
#include "parser.h"
#include "serializer.h"

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/
int write(char *, Table *);
int serialize(Table *, DynamicString **);

#endif

