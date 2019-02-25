/* main.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Entry point for the program. Structures and validates command line
 * arguments, and requests additional information from the user if necessary.
 * When the user's inputs are valid, acts upon the inputs to output a sorted
 * version of an input CSV file.
 *
 * Program description:
 *
 * This program reads a CSV file and tries to parse it.
 *
 * High-level step break down:
 *
 *
 * STEP 1. Structure the parameters.
 * 
 * Description: Reads the command line arguments and validates them.
 *
 *
 * Imports: Command-line arguments.
 *
 * Exports: a FileConfiguration structure containing some of the data required
 * to parse.
 *
 *
 * STEP 2. Read and parse the input file.
 *
 * Description: Opens the input file obtained from the configuration and reads it
 * sequentially, validating and parsing each chunk as it is read. This step is
 * the most complicated, because it involves good state management.
 * See {parser.c} documentation and code for more information.
 *
 * Imports: a FileConfiguration structure (as obtained from Step 1).
 *
 * Exports: a structured Table containing the parsed data.
 *
 * 
 * Step 3. Perform 'Phase-2' Validation on the table.
 * Description: When parsing the file, we didn't make any assumptions about the
 * number of columns. Before continuing with the most expensive step, we will
 * validate the number of columns in each row to ensure compliance with the
 * specification.
 *
 *
 * Step 4. Further requesting of data.
 *
 * Description: Now that the Table has been parsed and validated, we can start
 * thinking about how to sort the table. In this step, we prompt the user on
 * what to sort by (which Fields, see {fields.c}), and whether to sort ascending
 * or descending. We could not have done this sooner, because the Table had not
 * been parsed; we didn't know what fields were in the Table.
 *
 * Imports: The parsed Table from Step 2.
 *
 * Exports: Sort order, sort column, sort data type.
 *
 *
 *
 * Step 5. Sort the table.
 *
 * Description: Sorts the table's rows based on the configuration (obtained from
 * Step 3). The Table stores rows in linked lists, so a generic linked list
 * insertion sort is used to sort them. See {table.c} for more information about
 * Table, and {linkedlist.c} for more information about the linked list
 * implementation.
 *
 * Imports: a FileConfiguration structure (as obtained from Step 1 & 3), which
 * describes sort order, sort field and sort data type; and a Table structure to
 * sort (as obtained from Step 2).
 *
 * Exports: None. The imported Table is sorted.
 *
 *
 * Step 6. Serialize the table.
 *
 * Description: Converts the table back to a flat CSV string.
 *
 * Imports: a Table structure (as obtained in Step 2).
 *
 * Exports: a string representing the Table in CSV format.
 *
 *
 * Step 7. Write the CSV string to file.
 *
 * Description: Exports the CSV string (as obtained from Step 4) to the file
 * specified by the configuration (as obtained in Step 1 & 3).
 */
#include "main.h"

/*******************************************************************************
 *                                ENTRY POINT                                  *
 *******************************************************************************/

/*
 * Entry point of the program. Reads the command line arguments and
 * parses the CSV file as named within the CSV file.
 */
int main(int argc, char **argv)
{
    /* The error code we will return. */
    int errorCode = 0;

    /* Configurations for the parser and sorter. */
    FileConfig *fileConfig = NULL;
    SortConfig *sortConfig = NULL;

    /* Create the container for the tasks. */
    errorCode = getInitialConfiguration(argc, argv, &fileConfig, &sortConfig);

    /* Process the file based on the configuration. */
    if (!errorCode)
    {
        errorCode = process(fileConfig, sortConfig);
    }

    /* Free all the data stored in the configurations. */
    freeFileConfiguration(fileConfig);
    freeSortConfiguration(sortConfig);

    /* Print an error message, if anything went wrong. This won't catch all
     * things that went wrong, because we have only one errorCode. Our code
     * should be structured such that the program skips the next steps when
     * it encounters errors that cannot be recovered from. */
    if (errorCode)
    {
        if (errorCode == ERROR_UNRECOGNIZED_ARGUMENT)
        {
            printUsageAdvice();
        }
        else
        {
            /* Error reporting. */
            printf("Error: %s\n(Code: %d)\n",
                getErrorMessage(errorCode), errorCode);
        }
    }

    return errorCode;
}

/*
 * Parses, validates and sorts a CSV file as specified by the FileConfig and
 * SortConfig. This function returns an error code, or STATUS_OK on success.
 */
int process(FileConfig *fileConfig, SortConfig *sortConfig)
{
    int errorCode = STATUS_OK;

    /* The Table we've parsed. */
    Table *table = NULL;


    if (!errorCode)
    {
        /* Parse the input file specified by the FileConfig. The error code
         * will tell us if this is a valid CSV file. */
        errorCode = parseInputFile(fileConfig, &table);
    }
    
    if (!errorCode)
    {
        /* We couldn't prompt the user for a sort column before. Do it now. */
        errorCode = promptSortingConfiguration(sortConfig, table);
    }

    if (!errorCode)
    {
        /* We're OK to begin. Output a summary of the configuration. */
        printConfigurationReport(fileConfig, sortConfig);
    }

    if (!errorCode)
    {
        /* Sort the Table that we parsed earlier. This method doesn't return
         * any errors. */
        sortTable(sortConfig, table);
    }

    if (!errorCode)
    {
        /* Serialize and write the Table to a file. */
        errorCode = writeFile(fileConfig, table);
    }

    /* Free the table we used to sort the file. */
    freeTable(table);

    return errorCode;
}

/*******************************************************************************
 *                           INFORMATION FUNCTIONS                             *
 *******************************************************************************/

/*
 * Prints a message to stdout explaining how to use this program.
 */
void printUsageAdvice(void)
{
    /* Explain how to use this program. */
    printf("Usage:\n$ csvsort i INPUT_FILE o OUTPUT_FILE\n");
    printf("Sorts INPUT_FILE and writes to OUTPUT_FILE\n");
}

/*
 * Prints a report of the parsing result.
 */
void printConfigurationReport(FileConfig *fileConfig, SortConfig *sortConfig)
{
    /* Determine the sort order. */
    int sortOrder = getSortOrder(sortConfig);
    printf("########################################################\n");
    printf("#%20s%34s#\n", "SUMMARY", "");
    printf("########################################################\n");
    printf("#%54s#\n", "");
    printf("#%15s : %-36s#\n", "Input File", getInputFile(fileConfig));
    printf("#%15s : %-36s#\n", "Output file", getOutputFile(fileConfig));
    printf("#%15s : %-36s#\n", "Sort Column", getSortColumnName(sortConfig));
    printf("#%15s : %-36s#\n", "Sort Order", getSortOrderName(sortOrder));
    printf("#%54s#\n", "");
    printf("########################################################\n");
    printf("\n");
}


/*******************************************************************************
 *                                   STEP 1                                    *
 *******************************************************************************/
/*
 * Begins step 1 of the program: gets the initial configuration of the program by
 * reading the input command-line arguments and structuring them.
 * 
 * Exports the FileConfig and SortConfig to the addresses specified. Returns the
 * error code,  or STATUS_OK on success.
 */
int getInitialConfiguration(int argc, char **argv, FileConfig **fileConfig,
    SortConfig **sortConfig)
{
    int errorCode = STATUS_OK;

    /* Create the configuration structures that we will be initializing. */
    *fileConfig = createFileConfiguration();
    *sortConfig = createSortConfiguration();
    
    /* Get the configuration from the command line. This function will return
     * an error code (not 0) if something went wrong. This is an internal
     * function, so no error code will need translation. */
    errorCode = readCommandLineArguments(argc, argv, *fileConfig);

    if (!errorCode)
    {
        /* Validate the resulting configurations. */
        if (!hasInputFile(*fileConfig))
        {
            errorCode = ERROR_NO_INPUT_FILE;
        }

        if (!hasOutputFile(*fileConfig))
        {
            errorCode = ERROR_NO_OUTPUT_FILE;
        }
    }
    return errorCode;
}

/*
 * Reads command line arguments and exports the configuration as a
 * FileConfiguration struct to the pointer {config}. Returns an error code
 * if any errors were encountered.
 */
int readCommandLineArguments(int argc, char **argv, FileConfig *config)
{
    int errorCode = 0, arg = 0;

    /* Skip the zeroth argument; we're not concerned with the filename. */
    arg++;

    /* The first argument must be either i or o. */
    while (arg < argc && !errorCode)
    {
        if (!strcmp(argv[arg], "i"))
        {
            arg++;
            /* We need to ensure argv is big enough to retrieve the next value. */
            if (arg < argc)
            {
                /* Set the input filename. */
                setInputFile(config, argv[arg]);
            }
            else
            {
                errorCode = ERROR_NO_INPUT_FILE;
            }
        }
        else if (!strcmp(argv[arg], "o"))
        {
            arg++;
            /* We need to ensure argv is big enough to retrieve the next value. */
            if (arg < argc)
            {
                /* Get the output filename. */
                setOutputFile(config, argv[arg]);
            }
            else
            {
                errorCode = ERROR_NO_OUTPUT_FILE;
            }
        }
        else
        {
            /* Unrecognized parameter. */
            errorCode = ERROR_UNRECOGNIZED_ARGUMENT;
        }
        arg++;
    }
    return errorCode;
}

/*******************************************************************************
 *                                   STEP 2                                    *
 *******************************************************************************/
/*
 * Begins Step 2 of the program: reads, parses and validates the input file.
 * If any errors occur, this function translates them to errors that can be
 * interpreted by main.
 */
int parseInputFile(FileConfig *fileConfig, Table **table)
{
    int errorCode = 0;
    char *inFile = getInputFile(fileConfig);

    /* The read function only needs the filename, and an address to export to. */

    /* Read & parse the file. */
    if (read(inFile, table))
    {
        errorCode = ERROR_CANNOT_READ_FILE;
    }

    /* Validate the table created. */
    if (validate(*table))
    {
        errorCode = ERROR_INVALID_TABLE;
    }

    return errorCode;
}

/*******************************************************************************
 *                                   STEP 3                                    *
 *******************************************************************************/
/*
 * Proxy function for the 'prompt sorting configuration' task. This function
 * handles the task of prompting the user for additional sorting information.
 * The user will be asked by which column they wish to sort, so we need access
 * to the Field data of the table. This should  be stored in the passed
 * ParseContainer.
 */
int promptSortingConfiguration(SortConfig *sortConfig, Table *table)
{
    int errorCode = 0;

    /* Prompt the user for the sort column. */
    menuSortColumn(sortConfig, table);

    /* Prompt the user for the sort order (asc, desc).
     * This function doesn't return any error codes. */
    menuSortOrder(sortConfig);

    return errorCode;
}

/*******************************************************************************
 *                                   STEP 4                                    *
 *******************************************************************************/

/*
 * Proxy function for the 'sort table' task. This function handles the task to
 * sort a table.
 */
void sortTable(SortConfig *sortConfig, Table *table)
{
    /* Sort the Table. This doesn't return any errors. */
    sort(table, sortConfig);
}

/*******************************************************************************
 *                                   STEP 5                                    *
 *******************************************************************************/

/*
 * Proxy function for the 'write file' task. This function handles the task to
 * write a table to a CSV file.
 */
int writeFile(FileConfig *fileConfig, Table *table)
{
    int errorCode = 0;
    char *outFile = getOutputFile(fileConfig);
    /* The Write function only needs the filename, and the Table. */
    if (write(outFile, table))
    {
        errorCode = ERROR_CANNOT_WRITE_FILE;
    }

    return errorCode;
}

