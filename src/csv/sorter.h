#ifndef SORTER_H
#define SORTER_H
/* sorter.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for sorter.c
 */

/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Local. */
#include "datatype.h"
#include "../generic/linkedlist.h"
#include "../generic/table.h"
#include "../generic/util.h"

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

#define COUNT_TASKS 5

#define SORT_ORDER_ASC 1
#define SORT_ORDER_DESC 2
#define SORT_ORDER_SHUFFLE 3

/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/* Declare a special type of function (pointers) that will be used to create
 * a generic timing function. */
typedef int (ParseTask)(void *);

/*
 * SortConfig is a container struct for sort characteristics.
 */
typedef struct SortConfig
{
    /* Which datatype to assume when sorting. */
    int sortDataType;

    /* The order in which we are sorting (asc, desc). */
    int sortOrder;

    /* The column name and ID (position) within the row. */
    char *sortColumnName;
    int sortColumn;

} SortConfig;

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

int runTimedTask(char *, ParseTask, void *);

/* Constructor Functions. */
SortConfig *createSortConfiguration(void);

/* Accessor Functions. */
int getSortColumn(SortConfig *);
char *getSortColumnName(SortConfig *);
int getSortOrder(SortConfig *);
int getSortDataType(SortConfig *);
char *getSortOrderName(int);

/* Mutator Functions. */
void setSortColumn(SortConfig *, int);
void setSortColumnName(SortConfig *, char *);
void setSortOrder(SortConfig *, int);
void setSortDataType(SortConfig *, int);

/* Destructor Functions. */
void freeSortConfiguration(SortConfig *);

/* Core Functions. */
void sort(Table *, SortConfig *);

#endif
