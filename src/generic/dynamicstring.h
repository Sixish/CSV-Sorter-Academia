#ifndef DYNAMICSTRING_H
#define DYNAMICSTRING_H
/* dynamicstring.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for dynamicstring.c:
 *   Includes library dependencies of dynamicstring.c functions;
 *   Defines macro definitions used by dynamicstring.c;
 *   Declares type definitions for Dynamic Strings;
 *   Declares function prototypes for external files.
 */


/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "linkedlist.h"

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

/* How big should each substring be? */
#define SIZE_DYNAMIC_STRING_BLOCK 0xFF

/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * Defines a DynamicString. A DynamicString is just a struct with a LinkedList and
 * a length corresponding to the size of the list.
 */
typedef struct DynamicString
{
    /* Each Node of the linked list contains a substring. Each Node contains 1
     * to SIZE_DYNAMIC_STRING_BLOCK characters. Every Node should contain
     * SIZE_DYNAMIC_BLOCK characters unless it is the tail of the list. */
    LinkedList *substrings;

    /* The current length of the DynamicString. That is, how many characters
     * are stored in the cumulative string. This is used by the functions to
     * determine the current position, i.e. so we know where to append to. */
    int length;

} DynamicString;

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Creation Functions. */
DynamicString *createDynamicString(void);

/* Mutator Functions. */
void setDynamicStringValue(DynamicString *dStr, char *str);
void appendStringToDynamicString(DynamicString *dStr, char *str);
void appendCharToDynamicString(DynamicString *dStr, char chr);

/* Accessor Functions. */
int getDynamicStringLength(DynamicString *dStr);
char *serializeDynamicString(DynamicString *dStr);

/* Destruction Functions. */
void freeDynamicString(DynamicString *dStr);

#endif
