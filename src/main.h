#ifndef MAIN_H
#define MAIN_H
/* main.h
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Header file for main.h.
 */
/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Local. */
#include "menu.h"
#include "csv/reader.h"
#include "csv/validator.h"
#include "csv/sorter.h"
#include "csv/writer.h"

/********************************************************************************
 *                             MACRO DEFINITIONS                                *
 ********************************************************************************/

#define MAIN_TASK_COUNT 4

/* Errors Numbers. */
#define ERROR_NO_INPUT_FILE 1
#define ERROR_NO_OUTPUT_FILE 2

#define ERROR_CANNOT_READ_FILE 3
#define ERROR_INVALID_FILE 4
#define ERROR_INVALID_TABLE 5
#define ERROR_CANNOT_WRITE_FILE 6

/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/

/* Entry Point */
int main(int, char **);
int process(FileConfig *, SortConfig *);

/* Information Functions */
void printUsageAdvice(void);
void printConfigurationReport(FileConfig *, SortConfig *);

/* Step 1 Functions */
int getInitialConfiguration(int, char **, FileConfig **, SortConfig **);
int readCommandLineArguments(int, char **, FileConfig *);

/* Step 2 Functions */
int parseInputFile(FileConfig *, Table **);

/* Step 3 Functions */
int promptSortingConfiguration(SortConfig *, Table *);

/* Step 4 Functions */
void sortTable(SortConfig *, Table *);

/* Step 5 Functions */
int writeFile(FileConfig *, Table *);


#endif
