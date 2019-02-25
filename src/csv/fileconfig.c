/* fileconfig.c
 * 
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Contains functions for interacting with FileConfig structures,
 * thereby creating an abstraction layer for consistent behavior and modularity.
 * 
 * This file contains the following groups of functions:
 * 
 * Constructor functions. Use the createFileConfiguration function to
 * safely create and initialize an instance of the FileConfig
 * structure.
 * 
 * Accessor and Mutator functions. Use the getter and setter functions
 * instead of accessing these fields directly.
 * 
 * Field validation. Use the hasInputFile and hasOutputFile functions to
 * determine if the configuration has an input and/or output file.
 * 
 * Memory Management functions. Use the freeFileConfiguration function to
 * easily free a configuration structure and all data it contains. Use with
 * care: never free if information stored within may still be used.
 */
#include "fileconfig.h"

/********************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Create and initialises a parser configuration.
 */
FileConfig *createFileConfiguration(void)
{
    FileConfig *config = (FileConfig *)
        malloc(sizeof(FileConfig));

    FileConfig conf;
    *config = conf;

    /* Initialise the struct's fields. */
    config->inputFile = NULL;
    config->outputFile = NULL;

    config->inputFileIsDynamic = false;
    config->outputFileIsDynamic = false;

    return config;
}


/********************************************************************************
 *                             MUTATOR FUNCTIONS                                *
 ********************************************************************************/

/*
 * Sets a configuration's input file.
 */
void setInputFile(FileConfig *config, char *outFile)
{
    config->inputFile = outFile;
}

/*
 * Sets the configuration's output file.
 */
void setOutputFile(FileConfig *config, char *inFile)
{
    config->outputFile = inFile;
}

/********************************************************************************
 *                             ACCESSOR FUNCTIONS                               *
 ********************************************************************************/

/*
 * Gets the configuration's input file.
 */
char *getInputFile(FileConfig *config)
{
    char *file = NULL;
    if (config != NULL)
    {
        file = config->inputFile;
    }
    return file;
}

/*
 * Sets the configuration's output file.
 */
char *getOutputFile(FileConfig *config)
{
    char *file = NULL;
    if (config != NULL)
    {
        file = config->outputFile;
    }
    return file;
}

/*
 * Determines if a configuration stores an input file.
 */
bool hasInputFile(FileConfig *config)
{
    bool hasInFile = (config->inputFile != NULL);
    return hasInFile;
}

/*
 * Determines if a configuration stores an output file.
 */
bool hasOutputFile(FileConfig *config)
{
    bool hasOutFile = (config->outputFile != NULL);
    return hasOutFile;
}

/********************************************************************************
 *                           DESTRUCTION FUNCTIONS                              *
 ********************************************************************************/

/*
 * Frees all data associated with a configuration.
 */
void freeFileConfiguration(FileConfig *config)
{
    if (config != NULL)
    {
        /* It's possible that the input file is dynamically allocated.
         * If it is, a flag should be set so that we can free it.
         * Note: this typically happens when the program prompts the user
         * for input, i.e. NOT from the command line. */
        if (config->inputFileIsDynamic)
        {
            free(config->inputFile);
        }

        if (config->outputFileIsDynamic)
        {
            free(config->outputFile);
        }
        free(config);
    }
}

