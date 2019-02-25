#ifndef FILECONFIG_H
#define FILECONFIG_H
/* fileconfig.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines a structure for conveying input and output files.
 */

/********************************************************************************
 *                            LIBRARY DEPENDENCIES                              *
 ********************************************************************************/

/* Standard. */
#include <stdbool.h>

/* Local. */
#include "errors.h"

/********************************************************************************
 *                       TYPE AND STRUCTURE DEFINITIONS                         *
 ********************************************************************************/

/*
 * Structure for the file configuration. This structure represents a container
 * of an input and output file.
 */
typedef struct FileConfig
{
    /* File to read from. */
    char *inputFile;
    /* Whether or not the input file is dynamic,
     * i.e. must be freed manually. */
    bool inputFileIsDynamic;

    /* File to write to. */
    char *outputFile;
    /* Whether or not the output file is dynamic,
     * i.e. must be freed manually. */
    bool outputFileIsDynamic;

} FileConfig;


/********************************************************************************
 *                            FORWARD DECLARATIONS                              *
 ********************************************************************************/


/* Field validation functions. */
bool hasInputFile(FileConfig *);
bool hasOutputFile(FileConfig *);

/* Accessor & mutator functions. */
void setInputFile(FileConfig *, char *);
void setOutputFile(FileConfig *, char *);
char *getInputFile(FileConfig *);
char *getOutputFile(FileConfig *);

/* Constructor functions. */
FileConfig *createFileConfiguration(void);

/* Memory management functions. */
void freeFileConfiguration(FileConfig *);

#endif

