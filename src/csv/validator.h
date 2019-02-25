#ifndef VALIDATOR_H
#define VALIDATOR_H
/* validator.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for validator.c
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "../generic/table.h"
#include "../generic/linkedlist.h"

#define ERROR_INVALID_NUMBER_OF_COLUMNS 1

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/
int validate(Table *table);

#endif
