/* stack.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions to interact with Stack structures.
 */
#include "stack.h"

/********************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/* 
 * Creates a new instance of a Stack and initializes its fields.
 */
Stack *createStack(void)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    Stack s;
    *stack = s;

    stack->list = createLinkedList();

    return stack;
}

/********************************************************************************
 *                             ACCESSOR FUNCTIONS                               *
 ********************************************************************************/

/*
 * Pops an item from the Stack, returning the value that was removed.
 */
void *pop(Stack *stack)
{
    void *ret = NULL;
    if (stack != NULL && stack->list != NULL)
    {
        LinkedListNode *tail = getLinkedListTail(stack->list);
        ret = getNodeValue(tail);
        removeNode(stack->list, tail);

        /* This won't free the value stored within the node. */
        free(tail);
    }

    return ret;
}

/*
 * Pushes an item to the Stack.
 */
void push(Stack *stack, void *val)
{
    if (stack != NULL)
    {
        addValue(stack->list, val);
    }
}

/*
 * Gets the last item from the Stack.
 */
void *getLastStackItem(Stack *stack)
{
    void *val = NULL;
    if (stack != NULL && stack->list != NULL)
    {
        LinkedListNode *node = getLinkedListTail(stack->list);
        if (node != NULL)
        {
            val = getNodeValue(node);
        }
    }
    return val;
}

/*
 * Determines if the stack is empty.
 */
bool stackIsEmpty(Stack *stack)
{
    bool isEmpty = true;
    if (stack != NULL)
    {
        isEmpty = linkedListIsEmpty(stack->list);
    }
    return isEmpty;
}


/********************************************************************************
 *                            DESTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Frees all data associated with a Stack.
 */
void freeStack(Stack *stack)
{
    if (stack != NULL)
    {
        freeLinkedList(stack->list);
        free(stack);
    }
}

