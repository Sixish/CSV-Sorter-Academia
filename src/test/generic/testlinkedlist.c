/* testlinkedlist.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Performs unit tests for linkedlist.c
 */
#include "testlinkedlist.h"

/*******************************************************************************
 *                             TESTING FUNCTIONS                               *
 *******************************************************************************/

int testGetNextNode(void)
{
    int errors = 0;
    int val1 = 1, val2 = 2, val3 = 3;
    void *addr1 = &val1, *addr2 = &val2, *addr3 = &val3;
    LinkedListNode *node1, *node2, *node3;
    LinkedList *list = createLinkedList();


    addNode(list, (void *)&addr1);
    addNode(list, (void *)&addr2);
    addNode(list, (void *)&addr3);

    node1 = getLinkedListNodeAt(list, 0);
    node2 = getLinkedListNodeAt(list, 1);
    node3 = getLinkedListNodeAt(list, 2);

    if (getNextNode(node1) != node2)
    {
        printf("Test failed: GetNextNode #1.");
        errors++;
    }

    if (getNextNode(node2) != node3)
    {
        printf("Test failed: GetNextNode #2.");
        errors++;
    }

    if (getNextNode(node3) != NULL)
    {
        printf("Test failed: GetNextNode #3.");
        errors++;
    }

    return errors;
}

int testGetPrevNode(void)
{
    int errors = 0;
    int val1 = 1, val2 = 2, val3 = 3;
    void *addr1 = &val1, *addr2 = &val2, *addr3 = &val3;
    LinkedListNode *node1, *node2, *node3;
    LinkedList *list = createLinkedList();


    addNode(list, (void *)&addr1);
    addNode(list, (void *)&addr2);
    addNode(list, (void *)&addr3);

    node1 = getLinkedListNodeAt(list, 0);
    node2 = getLinkedListNodeAt(list, 1);
    node3 = getLinkedListNodeAt(list, 2);

    if (getPrevNode(node1) != NULL)
    {
        printf("Test failed: GetPrevNode #1.");
        errors++;
    }

    if (getPrevNode(node2) != node1)
    {
        printf("Test failed: GetPrevNode #2.");
        errors++;
    }

    if (getPrevNode(node3) != node2)
    {
        printf("Test failed: GetPrevNode #3.");
        errors++;
    }

    return errors;
}

int testLinkedList(void)
{
    int errors = 0;
    errors += testGetNextNode();
    errors += testGetPrevNode();

    return errors;
}

