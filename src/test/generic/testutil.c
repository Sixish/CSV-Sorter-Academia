/* testutil.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Tests the functions defined in the util.c file.
 */
#include "testutil.h"

/*******************************************************************************
 *                             TESTING FUNCTIONS                               *
 *******************************************************************************/

static int testCharToLowerCase(void)
{
    char input, exp, result;
    char *fnName = "charToLowerCase()";
    int errors = 0;

    /* Test any few capital letters. */
    input = 'A';
    exp = 'a';
    result = charToLowerCase(input);
    errors += expect(fnName, result == exp, "#1");

    input = 'F';
    exp = 'f';
    result = charToLowerCase(input);
    errors += expect(fnName, result == exp, "#2");

    /* Test that lowercase characters aren't "destroyed". */
    input = 'a';
    exp = 'a';
    result = charToLowerCase(input);
    errors += expect(fnName, result == exp, "#3");

    input = 'k';
    exp = 'k';
    result = charToLowerCase(input);
    errors += expect(fnName, result == exp, "#4");

    /* Test that non-printable characters are completely ignored (not changed). */
    input = '\n';
    exp = '\n';
    result = charToLowerCase(input);
    errors += expect(fnName, result == exp, "#5");

    input = '\t';
    exp = '\t';
    result = charToLowerCase(input);
    errors += expect(fnName, result == exp, "#6");

    return errors;
}

/*
 * Runs the 'util' testing process. This should be the only function exposed to
 * external scripts - everything else is called from this.
 */
int testUtil(void)
{
    int errors = 0;
    errors += testCharToLowerCase();

    return errors;
}
