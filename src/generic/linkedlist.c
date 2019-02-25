/* linkedlist.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions for interacting with LinkedLists, as defined in
 * linkedlist.h.
 *
 * This file contains the following groups of functions:
 *
 * Constructor functions, for safe creation of LinkedLists and LinkedListNodes.
 *
 * Accessor functions, for accessing information about a LinkedList or
 * LinkedListNode, including traversal of lists.
 * 
 * Mutator functions, for modifying the state of a LinkedList and/or
 * LinkedListNode, including sorting of lists.
 *
 * Destructor functions, for safely disposing of structures and clearing their
 * allocated memory.
 *
 * Information functions, for printing out debugging information about a
 * LinkedListNode or LinkedList.
 */
#include "linkedlist.h"

/********************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Creates a linked list and initializes its fields.
 */
LinkedList *createLinkedList(void)
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));

    /* Create a struct to obtain a default value for its fields, and place it
     * inside the dynamic memory we allocated previously. */
    LinkedList l;
    *list = l;

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

/*
 * Creates a linked list node, which can also serve as the root node.
 * This function is for internal-use only.
 */
static LinkedListNode *createNode(void *value)
{
    /* Create the node and allocate persistent memory for it. */
    LinkedListNode *ptr = (LinkedListNode *)
        malloc(sizeof(LinkedListNode));

    LinkedListNode node;
    /* Assign the node to the memory address we just allocated,
     * & return this address so we can use it again. */
    *ptr = node;

    /* Initialize the node. */
    ptr->value = value;
    ptr->nextNode = NULL;
    ptr->prevNode = NULL;

    return ptr;
}

/********************************************************************************
 *                             ACCESSOR FUNCTIONS                               *
 ********************************************************************************/

/*
 * Gets the node following the specified node.
 */
LinkedListNode *getNextNode(LinkedListNode *node)
{
    LinkedListNode *nextNode = NULL;
    /* Check if we're given a node. If not, then there's obviously no next
     * node. */
    if (node != NULL)
    {
        /* Get a reference to the next node. */
        nextNode = node->nextNode;
    }
    return nextNode;
}

/*
 * Gets the node preceding the specified node.
 */
LinkedListNode *getPrevNode(LinkedListNode *node)
{
    LinkedListNode *prevNode = NULL;
    /* Check if we're given a node. If not, then there's obviously no prev
     * node. */
    if (node != NULL)
    {
        prevNode = node->prevNode;
    }
    return prevNode;
}

/*
 * Determines if a node has a following node.
 *
 * This function should not be used when iterating the list to check if the end
 * has been reached; instead, check if the getNextNode() function returns NULL.
 */
bool hasNextNode(LinkedListNode *root)
{
    return (getNextNode(root) != NULL);
}

/* 
 * Gets the tail of the linked list.
 */
LinkedListNode *getLinkedListTail(LinkedList *list)
{
    LinkedListNode *tail = NULL;
    /* Check if the list has been provided. If not, obviously there is no tail. */
    if (list != NULL)
    {
        tail = list->tail;
    }
    return tail;
}

/*
 * Gets the head of the linked list.
 */
LinkedListNode *getLinkedListHead(LinkedList *list)
{
    LinkedListNode *head = NULL;
    /* Check if the list has been provided. If not, obviously there is no head. */
    if (list != NULL)
    {
        head = list->head;
    }
    return head;
}

/*
 * Gets the nth node. Returns the node nth children from the head of the list,
 * or NULL if the list has fewer than n items in it.
 */
LinkedListNode *getLinkedListNodeAt(LinkedList *list, int depth)
{
    LinkedListNode *node = NULL;
    if (list != NULL)
    {
        /* The function to call to determine the next node. We will be traversing
         * backwards for negative depth; so this can either be &getNextNode or
         * &getPrevNode. */
        LinkedListNode *(*fnTraversal)(LinkedListNode *) = NULL;

        /* The current depth, used as a loop index. */
        int curDepth = 0;

        if (depth < 0)
        {
            /* We're traversing backward. */

            /* Start at the tail. */
            node = getLinkedListTail(list);

            /* On each iteration we go to the previous node. */
            fnTraversal = &getPrevNode;

            /* Adjust the depth and current depth to account for the difference.
             * Flip the sign so that it's positive and increment the index by 1,
             * because -1 should correspond to +0 at the tail. */
            depth = -depth;
            curDepth++;
        }
        else
        {
            /* We're traversing forward. */
            node = getLinkedListHead(list);
            fnTraversal = &getNextNode;
        }

        /* We shouldn't use a for loop here because we may prematurely find the
         * end of the list. */
        while (curDepth < depth && node != NULL)
        {
            node = (fnTraversal)(node);
            curDepth++;
        }
    }

    return node;
}

/*
 * Gets the value of the node at a certain depth.
 */
void *getLinkedListValueAt(LinkedList *list, int depth)
{
    LinkedListNode *node = getLinkedListNodeAt(list, depth);
    void *val = getNodeValue(node);

    return val;
}

/*
 * Gets the node's value.
 */
void *getNodeValue(LinkedListNode *node)
{
    void *value = NULL;
    if (node != NULL)
    {
        value = node->value;
    }
    return value;
}

/*
 * Determines if the linked list is empty.
 */
bool linkedListIsEmpty(LinkedList *list)
{
    bool empty = false;
    if (list != NULL)
    {
        empty = (list->head == NULL);
    }
    return empty;
}

/*
 * Gets the number of nodes in the LinkedList.
 */
int getNodeCount(LinkedList *list)
{
    int count = 0;
    if (list != NULL)
    {
        count = list->count;
    }
    return count;
}

/********************************************************************************
 *                             MUTATOR FUNCTIONS                                *
 ********************************************************************************/


/*
 * Appends a linked list node to the base node.
 */
static void append(LinkedListNode *base, LinkedListNode *addition)
{
    if (base != NULL && addition != NULL)
    {
        /* Update the references. */
        addition->nextNode = base->nextNode;
        addition->prevNode = base;
        base->nextNode = addition;
        if (addition->nextNode != NULL)
        {
            addition->nextNode->prevNode = addition;
        }
    }

}

/*
 * Adds a node to the provided linked list.
 */
void addNode(LinkedList *list, void *value)
{
    LinkedListNode *node = createNode(value);
    if (list != NULL)
    {
        LinkedListNode *tail = getLinkedListTail(list);

        if (tail != NULL)
        {
            append(tail, node);
        }
        else
        {
            list->head = node;
        }
        list->tail = node;
        list->count++;
    }

}

/*
 * Creates a Node for the specified value and inserts it into the LinkedList.
 */
void addValue(LinkedList *list, void *value)
{
    addNode(list, value);
}

/*
 * Removes the first occurrence of the value in the list. This function only
 * compares references.
 */
void *removeLinkedListValue(LinkedList *list, void *value)
{
    LinkedListNode *node = getLinkedListHead(list);

    /* The value we removed from the list. */
    void *removedValue = NULL;

    /* Traverse until we either reach the end of the list or find the value. */
    while (node != NULL && getNodeValue(node) != value)
    {
        node = getNextNode(node);
    }
    removedValue = getNodeValue(node);

    return removedValue;
}

/*
 * Removes a node from the linked list and updates the references within the
 * LinkedList.
 */
void removeNode(LinkedList *list, LinkedListNode *node)
{
    /* Ensure we have something to remove (or a list to remove from). */
    if (list != NULL && node != NULL)
    {
        /* Replace the tail and head before removing it. */
        if (list->tail == node)
        {
            list->tail = node->prevNode;
        }
        if (list->head == node)
        {
            list->head = node->nextNode;
        }

        /* We only need to check for NULLs when we're accessing. */
        if (node->prevNode != NULL)
        {
            /* If node->nextNode is NULL, the previous node will receive
             * NULL as their nextNode. This is OK, because the parent should have
             * no child if we are removing the tail node. */
            node->prevNode->nextNode = node->nextNode;
        }
        if (node->nextNode != NULL)
        {
            /* If node->prevNode is NULL, the next node will receive
             * NULL as their prevNode. This is OK, because the child should have
             * no parent if we are removing the head node. */
            node->nextNode->prevNode = node->prevNode;
        }

        /* NULL the node references so that we don't, for some strange reason,
         * try to traverse from this node. */
        node->prevNode = NULL;
        node->nextNode = NULL;
    }

}

/*
 * Sorts a linked list according to a sorting function.
 */
void sortLinkedList(LinkedList *list, void *sortConfig,
    int (*sortFn)(void *node1, void *node2, void *config))
{
    /* The new root of the list. */
    LinkedListNode *newRoot = list->head;

    /* We start at the second node in the list, i.e. the root's child node. */
    LinkedListNode *nodePivot = getNextNode(newRoot);

    /* Traverse the whole linked list. */
    while (nodePivot != NULL)
    {
        /* The parent before swaps. */
        LinkedListNode *currParent = getPrevNode(nodePivot);

        /* The child before swaps. */
        LinkedListNode *currChild = getNextNode(nodePivot);

        /* The designated (new) parent, i.e. the node that will reference it. */
        LinkedListNode *newParent = currParent;

        /* Iterate across all previous nodes until we find the correct parent
         * for this node, as defined by the sorting callback. */
        while (newParent != NULL &&
            sortFn(getNodeValue(newParent), getNodeValue(nodePivot),
                sortConfig) == SWAP)
        {
            newParent = getPrevNode(newParent);
        }

        /* If the before-and-after parents are the same, then we don't
         * perform any swaps. */
        if (newParent != currParent)
        {
            /* Update the references to previous and next nodes. */

            /* Step 1: Update all current references to this node. */
            if (nodePivot->prevNode != NULL)
            {
                nodePivot->prevNode->nextNode = nodePivot->nextNode;
            }

            if (nodePivot->nextNode != NULL)
            {
                nodePivot->nextNode->prevNode = nodePivot->prevNode;
            }

            /* Step 2: Update the pivot's references. */
            nodePivot->prevNode = newParent;
            if (nodePivot->prevNode != NULL)
            {
                nodePivot->nextNode = nodePivot->prevNode->nextNode;
            }
            else
            {
                /* There's no parent: this node becomes the new root. */
                nodePivot->nextNode = newRoot;
                newRoot->prevNode = nodePivot;
                newRoot = nodePivot;
            }

            /* Step 3: Create new references to this node. */
            if (nodePivot->nextNode != NULL)
            {
                nodePivot->nextNode->prevNode = nodePivot;
            }
            if (nodePivot->prevNode != NULL)
            {
                nodePivot->prevNode->nextNode = nodePivot;
            }
        }
        nodePivot = currChild;
    }

    list->head = newRoot;
}

/********************************************************************************
 *                            DESTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Frees a Node and all of the nodes that follow it.
 */
void freeNode(LinkedListNode *root)
{
    /* Originally, I had a recursive solution to free all nodes. However, when
     * handling particularly large files, the program would cause stack overflows.
     * Instead of recursively freeing, we'll iterate over them. */
    LinkedListNode *node = root;
    LinkedListNode *next = NULL;

    while (node != NULL)
    {
        /* Get the next node. We need this because the node will be freed and
         * thus we cannot access the next node afterwards. */
        next = getNextNode(node);
        free(node);
        node = next;
    }
}

/*
 * Frees all memory associated with a linked list.
 */
void freeLinkedList(LinkedList *list)
{
    if (list != NULL)
    {
        freeNode(list->head);
        free(list);
    }
}

/********************************************************************************
 *                           INFORMATION FUNCTIONS                              *
 ********************************************************************************/

/*
 * Prints details about the values of the node.
 */
void printNode(LinkedListNode *root)
{
    if (root->nextNode != NULL)
    {
        printNode(root->nextNode);
    }
    printf("Value: %d | Address: %p\n", *((int *)root->value), (void *)root);
}

/*
 * Prints a linked list.
 */
void printLinkedList(LinkedList *list)
{
    printNode(list->head);
}

