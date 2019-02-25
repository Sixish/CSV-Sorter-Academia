#ifndef TESTHELPER_H
#define TESTHELPER_H
/* testhelper.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for testhelper.c.
 */


/*******************************************************************************
 *                            LIBRARY DEPENDENCIES                             *
 *******************************************************************************/

#include <stdbool.h>
#include <stdio.h>

/*******************************************************************************
 *                            FORWARD DECLARATION                              *
 *******************************************************************************/

int expect(char *fnName, bool result, char *message);

#endif
