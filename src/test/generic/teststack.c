/* teststack.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Performs unit tests for stack.c.
 */
#include "teststack.h"

/*******************************************************************************
 *                             TESTING FUNCTIONS                               *
 *******************************************************************************/

int testStack(void)
{
    int errors = 0;
    Stack *s = createStack();
    char *out1, *out2, *out3;
    char *exp1, *exp2, *exp3;

    push(s, "Hello");
    push(s, "Goodbye");
    push(s, "Wait what?");

    out1 = (char *)pop(s);
    out2 = (char *)pop(s);
    out3 = (char *)pop(s);

    exp1 = "Wait what?";
    exp2 = "Goodbye";
    exp3 = "Hello";

    if (strcmp(out1, exp1))
    {
        printf("Test failed: Stack #1.");
        errors++;
    }
    if (strcmp(out2, exp2))
    {
        printf("Test failed: Stack #2.");
        errors++;
    }
    if (strcmp(out3, exp3))
    {
        printf("Test failed: Stack #3.");
        errors++;
    }
    return errors;
}
