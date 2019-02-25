/* sorter.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Handles sorting a CSV file.
 */
#include "sorter.h"

/*******************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                             *
 *******************************************************************************/

/*
 * Creates a SortConfiguration structure and initializes its fields.
 */
SortConfig *createSortConfiguration(void)
{
    SortConfig *config = (SortConfig *)malloc(sizeof(SortConfig));

    /* Initialize the fields. */
    config->sortDataType = 0;
    config->sortOrder = 0;
    config->sortColumn = 0;
    config->sortColumnName = NULL;

    return config;
}

/*******************************************************************************
 *                             ACCESSOR FUNCTIONS                              *
 *******************************************************************************/

/*
 * Gets the sort column from the configuration.
 */
int getSortColumn(SortConfig *config)
{
    int sortColumn = config->sortColumn;
    return sortColumn;
}

/*
 * Gets the name of the column being sorted by.
 */
char *getSortColumnName(SortConfig *config)
{
    char *sortColumnName = config->sortColumnName;
    return sortColumnName;
}

/*
 * Gets the sort order from the configuration.
 */
int getSortOrder(SortConfig *config)
{
    int sortOrder = config->sortOrder;
    return sortOrder;
}

/*
 * Gets the sort data type from the configuration.
 */
int getSortDataType(SortConfig *config)
{
    int dataType = config->sortDataType;
    return dataType;
}

/*
 * Translates the sort order ID to a user-friendly string.
 */
char *getSortOrderName(int sortOrder)
{
    char *orderName = NULL;
    switch (sortOrder)
    {
        case SORT_ORDER_ASC:
            orderName = "Ascending";
            break;
        case SORT_ORDER_DESC:
            orderName = "Descending";
            break;
        case SORT_ORDER_SHUFFLE:
            orderName = "Shuffle";
            break;
        default:
            orderName = "Default";
            break;
    }
    return orderName;
}

/*******************************************************************************
 *                             MUTATOR FUNCTIONS                               *
 *******************************************************************************/

/*
 * Sets the sort column for the configuration.
 */
void setSortColumn(SortConfig *config, int value)
{
    config->sortColumn = value;
}

/*
 * Sets the name of the column being sorted by. Creates and uses a copy of the
 * input string. This function does not modify or reuse the passed string.
 */
void setSortColumnName(SortConfig *config, char *sortColumnName)
{
    int len = strlen(sortColumnName);
    char *cName = (char *)malloc((len + 1) * sizeof(char));

    /* Copy the string from sortColumnName into the buffer. */
    strncpy(cName, sortColumnName, len);

    /* Append the null-terminator just in case strncpy did not. */
    cName[len] = '\0';
    config->sortColumnName = cName;
}
/*
 * Sets the sort order for the configuration.
 */
void setSortOrder(SortConfig *config, int value)
{
    config->sortOrder = value;
}

/*
 * Sets the sort data type for the configuration.
 */
void setSortDataType(SortConfig *config, int dataType)
{
    config->sortDataType = dataType;
}


/*
 * Frees all memory associated with a SortConfig structure.
 */
void freeSortConfiguration(SortConfig *config)
{
    /* Free the strings we have allocated for this structure. */
    if (config != NULL)
    {
        if (config->sortColumnName != NULL)
        {
            /* Free the sort column name. Since this was dynamically allocated,
             * we need to free it individually. */
            free(config->sortColumnName);
        }
        /* Free the structure itself. */
        free(config);
    }
}

/*******************************************************************************
 *                            COMPARATOR FUNCTIONS                             *
 *******************************************************************************/

/*
 * Compares two column values lexicographically.
 */
static int compareStringValues(char *value1, char *value2)
{
    int result = 0;

    /* Use the string comparison function to determine the difference. */
    result = strcmp(value1, value2);

    return result;
}

/*
 * Compares two column values numerically. The specifications only require us
 * to handle strings an integers. Thus, assume the columns are integers.
 */
static int compareNumericValues(char *value1, char *value2)
{
    int result = 0, val1, val2;

    /* Parse these values as integers. */
    val1 = atoi(value1);
    val2 = atoi(value2);

    /* Get the difference between the two values and return it. */
    result = (val1 - val2);

    return result;
}

/*
 * Calculates the difference between two typed variables. this function is a
 * proxy function; all it does is call the corresponding functions based on the
 * specified dataType. See compareStringValues(), compareNumericValues().
 *
 * This is defined as static because it is used solely by the compareRows
 * function and has no relevance to external applications. It's not defined in
 * table.c because it has one very specific purpose.
 *
 * Valid dataTypes are:
 * DATATYPE_STRING    : Compares their alphanumeric order.
 * DATATYPE_NUMBER    : Compares their numeric order.
 */
static int compareTypedValues(char *value1, char *value2, int dataType)
{
    int result = 0;
    if (value1 != NULL && value2 != NULL)
    {
        if (dataType == DATATYPE_INTEGER)
        {
            result = compareNumericValues(value1, value2);
        }
        else if (dataType == DATATYPE_STRING)
        {
            result = compareStringValues(value1, value2);
        }
    }
    return result;
}

/*
 * Compares two values and determines if they should be swapped or not based on
 * the imported sortOrder.
 */
static int compareValues(char *value1, char *value2, int sortOrder, int sortType)
{
    int swapStatus = KEEP, diff;
    if (!strcmp(value1, ""))
    {
        /* Per specification: empty columns should always be at the bottom. */
        swapStatus = SWAP;
    }
    else if (!strcmp(value2, ""))
    {
        /* Per specification: empty columns should always be at the bottom. */
        swapStatus = KEEP;
    }
    else
    {
        diff = compareTypedValues(value1, value2, sortType);

        if ((diff > 0 && sortOrder == SORT_ORDER_ASC) || 
            (diff < 0 && sortOrder == SORT_ORDER_DESC) ||
            (sortOrder == SORT_ORDER_SHUFFLE && rand() > (RAND_MAX / 2)))
        {
            swapStatus = SWAP;
        }
    }

    return swapStatus;
}

/*
 * Determines if two Rows are in order according to the configuration.
 * Performs comparisons on the column specified in the configuration, and returns
 * KEEP if they are in the correct order, or SWAP otherwise.
 * If this function is not passed a configuration, the function will always
 * return KEEP.
 */
static int compareRows(void *rowSelection, void *rowPivot, void *vConfig)
{
    int swapStatus = KEEP;
    /* If there's no configuration, we can't know what to do.
     * So do nothing. */
    int sortOrder, sortColumn, sortDataType;

    /* Assume that we have been passed vConfig, which points to a valid
     * instance of SortConfig. */
    SortConfig *config = (SortConfig *)vConfig;

    /* Strings corresponding to the column contents.  */
    char *value1 = NULL, *value2 = NULL;

    /* Read the sort configuration. */
    sortOrder = getSortOrder(config);
    sortColumn = getSortColumn(config);
    sortDataType = getSortDataType(config);

    value1 = getRowColumnValue((Row *)rowSelection, sortColumn);
    value2 = getRowColumnValue((Row *)rowPivot, sortColumn);

    swapStatus = compareValues(value1, value2, sortOrder, sortDataType);

    /* Free the memory that was allocated for the serialized strings. */
    free(value1);
    free(value2);

    return swapStatus;
}


/*******************************************************************************
 *                             UTILITY FUNCTIONS                               *
 *******************************************************************************/

/*
 * Sorts the table based on the SortConfig. This function uses the compareRows
 * function to determine whether two rows should be swapped.
 */
void sort(Table *table, SortConfig *config)
{
    /* Sort the table rows. */
    sortTableRows(table, (void *)config, &compareRows);
}

