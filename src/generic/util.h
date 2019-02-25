#ifndef UTIL_H
#define UTIL_H
/* util.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for util.c:
 *   Includes library dependencies of util.c functions;
 *   Declares function prototypes for external files.
 */

/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Comparisons. */
bool isWhitespace(char);
bool charMatches(char, const char *, const int);

/* Conversions. */
char charToLowerCase(char);

bool isValidTextFileCharacter(char);
bool isValidFileName(char *);
int floatSign(float);

char *toLowerCase(char *);

/* Trimming. */
char *trim(char *, const char *, const int);
char *trimWhitespace(char *);

#endif

