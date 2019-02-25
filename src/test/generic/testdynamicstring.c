/* testdynamicstring.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Containg unit testing functions for DynamicString.c
 */
#include "testdynamicstring.h"


/*******************************************************************************
 *                             TESTING FUNCTIONS                               *
 *******************************************************************************/

/*
 * Test appending to a dynamic string. Ensure that the serialized value after the
 * appending is as expected.
 */
int testAppendStringToDynamicString(void)
{
    int errors = 0;
    char *fnName = "appendStringToDynamicString()";
    DynamicString *dStr = createDynamicString();
    char *str1 = "Lorem ipsum dolor sit amet, ";
    char *str2 = "consectetur adipiscing elit. ";
    char *str3 = "Suspendisse porta, dui id malesuada porta, ";
    char *str4 = "dolor tellus hendrerit velit.";

    char *exp1 = "";
    char *exp2 = "Lorem ipsum dolor sit amet, ";
    char *exp3 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
    char *exp4 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Suspendisse porta, dui id malesuada porta, ";
    char *exp5 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Suspendisse porta, dui id malesuada porta, dolor tellus "
        "hendrerit velit.";

    char *result = NULL;

    /*
     * Output: ""
     */
    result = serializeDynamicString(dStr);
    errors += expect(fnName, (strcmp(result, exp1) == 0), "#1");
    free(result);

    /*
     * Output: "Lorem ipsum dolor sit amet, "
     */
    appendStringToDynamicString(dStr, str1);
    result = serializeDynamicString(dStr);
    errors += expect(fnName, (strcmp(result, exp2) == 0), "#2");
    free(result);

    /*
     * Output: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
     */
    appendStringToDynamicString(dStr, str2);
    result = serializeDynamicString(dStr);
    errors += expect(fnName, (strcmp(result, exp3) == 0), "#3");
    free(result);

    /*
     *  Output: "Lorem ipsum dolor sit amet, consectetur adipiscing elit.
     *           Suspendisse porta, dui id malesuada porta, "
     */
    appendStringToDynamicString(dStr, str3);
    result = serializeDynamicString(dStr);
    errors += expect(fnName, (strcmp(result, exp4) == 0), "#4");
    free(result);

    /*
     * Output: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
     *          Suspendisse porta, dui id malesuada porta, dolor tellus 
     *          hendrerit velit.";
     */
    appendStringToDynamicString(dStr, str4);
    result = serializeDynamicString(dStr);
    errors += expect(fnName, (strcmp(result, exp5) == 0), "#5");
    free(result);

    return errors;
}

/*
 * Performs tests on the appendCharToDynamicString function.
 */
static int testAppendCharToDynamicString(void)
{
    int errors = 0;
    char *fnName = "appendCharToDynamicString()";
    DynamicString *dStr = NULL;

    char *result = NULL, *expected = NULL;
    dStr = createDynamicString();

    /*
     * Output: "L"
     */
    appendCharToDynamicString(dStr, 'L');
    result = serializeDynamicString(dStr);
    expected = "L";
    errors += expect(fnName, strcmp(result, expected) == 0, "#1");

    /*
     * Output: "Lo"
     */
    appendCharToDynamicString(dStr, 'o');
    result = serializeDynamicString(dStr);
    expected = "Lo";
    errors += expect(fnName, strcmp(result, expected) == 0, "#2");

    /*
     * Output: "Lor"
     */
    appendCharToDynamicString(dStr, 'r');
    result = serializeDynamicString(dStr);
    expected = "Lor";
    errors += expect(fnName, strcmp(result, expected) == 0, "#3");

    /*
     * Output: "Lore"
     */
    appendCharToDynamicString(dStr, 'e');
    result = serializeDynamicString(dStr);
    expected = "Lore";
    errors += expect(fnName, strcmp(result, expected) == 0, "#4");

    /*
     * Output: "Lorem"
     */
    appendCharToDynamicString(dStr, 'm');
    result = serializeDynamicString(dStr);
    expected = "Lorem";
    errors += expect(fnName, strcmp(result, expected) == 0, "#5");

    return errors;
}

/*
 * Tests the contract between DynamicString functions.
 */
int testDynamicString(void)
{
    int errors = 0;
    errors += testAppendStringToDynamicString();
    errors += testAppendCharToDynamicString();

    return errors;
}
