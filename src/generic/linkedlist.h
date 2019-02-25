#ifndef LinkedList_H
#define LinkedList_H
/* linkedlist.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for linkedlist.c:
 *   Includes library dependencies of linkedlist.c functions;
 *   Defines macro definitions used by linkedlist.c;
 *   Declares type definitions for linkedlists;
 *   Declares function prototypes for external files.
 */


/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

/* Determines that two elements should be swapped when sorting. */
#define SWAP 1
/* Determines that two elements should be kept in order when sorting. */
#define KEEP 0


/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * LinkedList wrapper structure. Stores the first node and the last node, as well
 * as the count for efficient retrieval.
 *
 * The state of the LinkedList must be updated every time the contents changes.
 * That is, if an item is added to the list, we need to check if the tail has
 * changed; we also need to update the count, etc.. It is the responsibility of
 * the function that performs this change.
 */
typedef struct LinkedList
{
    /* The head is the first node added to the list. */
    struct LinkedListNode *head;

    /* The tail is the last node added to the list. */
    struct LinkedListNode *tail;

    /* The number of nodes in the list. */
    int count;

} LinkedList;

/*
 * LinkedListNode structure. Stores a value and references two nodes - the next
 * and the previous nodes.
 *
 * Contract:
 *   LinkedListNode X is the head of LinkedList L if and only if
 *   X.prevNode = NULL.
 * Subcontract:
 *   There can only ever be one head of each LinkedList.
 *
 * Contract:
 *   LinkedListNode Y is the tail of LinkedList L if and only if
 *   Y.nextNode = NULL.
 * Subcontract:
 *   There can only ever be one head of each LinkedList.
 */
typedef struct LinkedListNode
{
    /* The parent LinkedListNode. */
    struct LinkedListNode *prevNode;

    /* The Child LinkedListNode. */
    struct LinkedListNode *nextNode;

    /* The value this node contains. */
    void *value;

} LinkedListNode;

/*
 * Defines the type of a generic linked list comparison function.
 * The function takes two linked list nodes (two items for comparisons)
 * and arbitrary data (e.e, a structure containing 'metadata') which the
 * function may need.
 * The function should return SWAP if the items should be swapped, or
 * KEEP if the items are in the correct order.
 */
typedef int (*LinkedListComparator)(void *, void *, void *);


/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Creation & Initialisation & Destruction. */
LinkedList *createLinkedList();

/* Mutator Fucntions. */
void addValue(LinkedList *, void *);
void *removeLinkedListValue(LinkedList *list, void *value);
void addNode(LinkedList *root, void *value);
void removeNode(LinkedList *list, LinkedListNode *node);

/* Accessor Functions. */
LinkedListNode *getLinkedListHead(LinkedList *list);
LinkedListNode *getLinkedListTail(LinkedList *list);
LinkedListNode *getLinkedListNodeAt(LinkedList *root, int depth);
void *getLinkedListValueAt(LinkedList *root, int depth);

LinkedListNode *getNextNode(LinkedListNode *node);
LinkedListNode *getPrevNode(LinkedListNode *node);

bool linkedListIsEmpty(LinkedList *list);
bool hasNextNode(LinkedListNode *root);
void *getNodeValue(LinkedListNode *elem);
int getNodeCount(LinkedList *count);

/* Destructor Functions. */
void freeLinkedList(LinkedList *);
void freeNode(LinkedListNode *root);

/* Information Functions. */
void printNode(LinkedListNode *root);

/* Sorting Functions. */
void sortLinkedList(LinkedList *, void *config,
    int (*sortFn)(void *val1, void *val2, void *config));

#endif
