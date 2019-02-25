#ifndef READER_H
#define READER_H
/* reader.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for reader.c
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "../generic/table.h"
#include "errors.h"
#include "parser.h"

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

int read(char *, Table **);

#endif
