/* testtable.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Performs unit tests for table.c.
 */
#include "testtable.h"

/*******************************************************************************
 *                             TESTING FUNCTIONS                               *
 *******************************************************************************/

/*
 * Tests adding a table row.
 */
int testAddTableRow(void)
{
    char *fnName = "testAddTableRow()";
    Table *table = NULL;
    Row *row = NULL;
    Row *row2 = NULL;

    Row *result;

    row = createTableRow();
    row2 = createTableRow();

    /* Create an empty table. */
    table = createTable();

    /* Ensure there's nothing in the table yet. */
    result = getLastTableRow(table);
    expect(fnName, result == NULL, "#1");

    /* Add a row to the table and ensure the state has changed. */
    addTableRow(table, row);
    result = getLastTableRow(table);
    expect(fnName, result == row, "#2");

    addTableRow(table, row2);
    result = getLastTableRow(table);
    expect(fnName, result == row, "#3");
}

/*
 * Tests removing a table row.
 */
int testRemoveTableRow(void)
{
    char *fnName = "testRemoveTableRow()";
    Row *row = NULL;
    Row *row2 = NULL;

    Row *result = NULL;
    
    row = createTableRow();
    row2 = createTableRow();

    /* Test the initial state of the table. */
    result = getLastTableRow(table);
    expect(fnName, result == NULL, "#1");

    /* Test removing a row from an empty table. */
    result = removeTableRow(table);
    expect(fnName, result == NULL, "#2");

    /* Add a row and verify the table's state. */
    addTableRow(table, row);
    result = getLastRow(table);
    expect(fnName, result == row, "#3");

    /* Try to remove the row and then validate the item removed, as well as
     * the table's state. */
    result = removeTableRow(table, row);
    expect(fNname, result == row, "#4");

    result = getLastRow(table);
    expect(fnName, result == row, "#5");

    /* Try to add two additional rows. Validate the state. */
    addTableRow(table, row);
    addTableRow(table, row2);
    result = getLastRow(table);
    expect(fnName, result == row2, "#6");

    /* Remove the last row and then validate the item removed, as well as
     * the table's state. */
    result = removeTableRow(table, getLastRow(table));
    expect(fnName, result == row2, "#7");

    result = getLastRow(table);
    expect(fnName, result == row, "#8");

    /* Remove the last node and validate the item removed, as well as the
     * table's state. */
    result = removeTableRow(table, getLastRow(table));
    expect(fnName, result == row, "#9");
}

int testTable(void)
{
    int errors = 0;
    errors += testAddTableRow();
    errors += testRemoveTableRow();
}
