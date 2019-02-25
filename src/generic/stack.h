#ifndef STACK_H
#define STACK_H
/* stack.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for stack.c:
 *   Includes library dependencies of stack.c functions;
 *   Defines macro definitions used by stack.c;
 *   Declares type definitions for Stacks;
 *   Declares function prototypes for external files.
 */


/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/
/* Standard. */
#include <stdio.h>

/* Local. */
#include "linkedlist.h"

/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * Generic Stack implementation.
 *
 * This structure permits only pushing and popping elements. It uses a LinkedList
 * for a dynamic structure; and imposes restrictions on accessing and removing
 * elements from it.
 */
typedef struct
{
    LinkedList *list;
} Stack;

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Constructor Functions. */
Stack *createStack(void);

/* Mutator Functions. */
void *pop(Stack *);
void push(Stack *, void *);

/* Accessor Functions. */
void *getLastStackItem(Stack *);
bool stackIsEmpty(Stack *stack);

/* Destructor Functions. */
void freeStack(Stack *);

#endif
