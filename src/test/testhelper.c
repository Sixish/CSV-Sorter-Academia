/* testhelper.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Contains unit testing helper functions.
 */
#include "testhelper.h"

/*******************************************************************************
 *                              HELPER FUNCTIONS                               *
 *******************************************************************************/

/*
 * Helper function for unit testing. Tests result and, if false (the expected did
 * not hold), returns 1 to indicate an error and outputs a message.
 */
int expect(char *fnName, bool result, char *message)
{
    int errorCount = 0;
    if (!result)
    {
        printf("Test failed for %s! (%s)\n", fnName, message);
        errorCount++;
    }

    return errorCount;
}
