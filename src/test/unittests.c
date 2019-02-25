/* unittests.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Unit testing program for components of the CSV parser.
 */
#include "unittests.h"

/*******************************************************************************
 *                                ENTRY POINT                                  *
 *******************************************************************************/

int main(void)
{
    int errors = 0;
    errors += testStack();
    errors += testLinkedList();
    errors += testDynamicString();
    if (!errors)
    {
        printf("All unit tests completed successfully.\n");
    }
    else
    {
        printf("Encountered %d errors during unit testing.\n", errors);
    }
    return 0;
}
