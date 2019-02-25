#ifndef MENU_H
#define MENU_H
/* menu.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for menu.h.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdio.h>

/* Local. */
#include "csv/fileconfig.h"
#include "csv/sorter.h"
#include "csv/fields.h"

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

#define INPUT_BUFFER_LENGTH 0xFF
#define LIMIT_FILENAME_CHARS 0xFF

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Generic Reading Functions.*/
char *readComparableLine(void);
char *readFileName(void);

/* Specific Reading Functions. */
char *menuPromptFileName(char *);
Field *menuSortcolumnFromList(FieldList *);
void menuSortColumn(SortConfig *, Table *);
void menuSortOrder(SortConfig *);

#endif
