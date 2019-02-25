#################################################################################
#                                 DEFINITIONS                                   #
#################################################################################

# Which C compiler are we using?
CC=gcc



# Object Path Prefixes : Paths to where to find different classes of object
# files. These should correspond to Source Path Prefixes (SPPs) defined below.
OPP=bin
OPP_BASE=    $(OPP)
OPP_GENERIC= $(OPP)/generic
OPP_CSV=     $(OPP)/csv

# Object Path Prefixes for unit tests.
OPP_TEST_BASE=    $(OPP)/test
OPP_TEST_GENERIC= $(OPP_TEST_BASE)/generic
OPP_TEST_CSV=     $(OPP_TEST_BASE)/csv

# List of directories containing object files.
OPP_DIRS=$(OPP_BASE) $(OPP_GENERIC) $(OPP_CSV) $(OPP_TEST_BASE) \
		 $(OPP_TEST_GENERIC) $(OPP_TEST_CSV)



# Source Path Prefixes : Paths to where to find different classes of source
# files. These should correspond to Object Path Prefixes (OPPs) defined above.
SPP=src
SPP_BASE=    $(SPP)
SPP_GENERIC= $(SPP)/generic
SPP_CSV=     $(SPP)/csv

# Source Path Prefixes for unit tests.
SPP_TEST_BASE=    $(SPP)/test
SPP_TEST_GENERIC= $(SPP_TEST_BASE)/generic
SPP_TEST_CSV=  $(SPP_TEST_BASE)/csv

# List of directories containing source files.
SPP_DIRS=$(SPP_BASE) $(SPP_GENERIC) $(SPP_CSV) $(SPP_TEST_BASE) \
		 $(SPP_TEST_GENERIC) $(SPP_TEST_CSV)



# List of required object files to compile to program executable.
OBJ_MAIN= $(addprefix $(OPP_GENERIC)/, dynamicstring.o linkedlist.o stack.o \
              table.o util.o) \
          $(addprefix $(OPP_CSV)/, datatype.o fields.o fileconfig.o \
              parser.o parserstate.o reader.o serializer.o sorter.o validator.o \
              writer.o errors.o) \
          $(addprefix $(OPP_BASE)/, main.o menu.o)

# List of required object files to compile to unit test executable.
OBJ_TEST= $(addprefix $(OPP_TEST_GENERIC)/, testdynamicstring.o testlinkedlist.o \
		      teststack.o testutil.o) \
		  $(addprefix $(OPP_TEST_BASE)/, testhelper.o unittests.o) \
          $(addprefix $(OPP_GENERIC)/, dynamicstring.o linkedlist.o stack.o \
              util.o)

# List of Object files.
OBJ= $(OBJ_MAIN)   $(OBJ_TEST)


# List of debug files (used for cleaning up).
DBG=core vgcore.* massif.out.*


# Names of executables.
EXEC_MAIN=sorter
EXEC_TEST=sorter_test

# List of output executable files (used for cleaning up).
EXEC=$(EXEC_MAIN) $(EXEC_TEST)


# Aliases for "unique" phony rules.
SETUP=.PHONY_1

# List of compiler flags for object file compilation.
CFLAGS=-ansi -pedantic -Wall -g



# The default job : compile everything.
all : $(SETUP) $(EXEC_MAIN) $(EXEC_TEST)



# Sets up the environment by creating directories that don't yet exist.
$(SETUP) : $(OPP_DIRS)


# Compiles the main program.
$(EXEC_MAIN) : $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) -o $(EXEC_MAIN)


# Compiles the test program.
$(EXEC_TEST) : $(OBJ_TEST)
	$(CC) $(OBJ_TEST) -o $(EXEC_TEST)



#################################################################################
#                                 MAIN PROGRAM                                  #
#################################################################################


# main.o
$(addprefix $(OPP_BASE)/, main.o) : \
    $(addprefix $(SPP_BASE)/, main.c main.h menu.h) \
    $(addprefix $(SPP_CSV)/, reader.h validator.h sorter.h writer.h)

	$(CC) $(addprefix $(SPP_BASE)/, main.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_BASE)/, main.o)

# menu.o
$(addprefix $(OPP_BASE)/, menu.o) : \
    $(addprefix $(SPP_BASE)/, menu.c menu.h) \
	$(addprefix $(SPP_CSV)/, fileconfig.h fields.h sorter.h)

	$(CC) $(addprefix $(SPP_BASE)/, menu.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_BASE)/, menu.o)

#################################################################################
#                                   GENERICS                                    #
#################################################################################


# util.o
$(addprefix $(OPP_GENERIC)/, util.o) : \
    $(addprefix $(SPP_GENERIC)/, util.c util.h)

	$(CC) $(addprefix $(SPP_GENERIC)/, util.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_GENERIC)/, util.o)

# table.o
$(addprefix $(OPP_GENERIC)/, table.o) : \
    $(addprefix $(SPP_GENERIC)/, table.c table.h linkedlist.h dynamicstring.h)

	$(CC) $(addprefix $(SPP_GENERIC)/, table.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_GENERIC)/, table.o)

# stack.o
$(addprefix $(OPP_GENERIC)/, stack.o) : \
    $(addprefix $(SPP_GENERIC)/, stack.c stack.h linkedlist.h)

	$(CC) $(addprefix $(SPP_GENERIC)/, stack.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_GENERIC)/, stack.o)

# linkedlist.o
$(addprefix $(OPP_GENERIC)/,linkedlist.o) : \
    $(addprefix $(SPP_GENERIC)/, linkedlist.c linkedlist.h)

	$(CC) $(addprefix $(SPP_GENERIC)/, linkedlist.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_GENERIC)/, linkedlist.o)

# dynamicstring.o
$(addprefix $(OPP_GENERIC)/, dynamicstring.o) : \
    $(addprefix $(SPP_GENERIC)/, dynamicstring.c dynamicstring.h linkedlist.h)

	$(CC) $(addprefix $(SPP_GENERIC)/, dynamicstring.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_GENERIC)/, dynamicstring.o)


#################################################################################
#                                     CSV                                       #
#################################################################################

# reader.o
$(addprefix $(OPP_CSV)/, reader.o) : \
    $(addprefix $(SPP_CSV)/, reader.c reader.h parser.h) \
    $(addprefix $(SPP_GENERIC)/, table.h)

	$(CC) $(addprefix $(SPP_CSV)/, reader.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, reader.o)


# validator.o
$(addprefix $(OPP_CSV)/, validator.o) : \
    $(addprefix $(SPP_CSV)/, validator.c validator.h) \
    $(addprefix $(SPP_GENERIC)/, table.h linkedlist.h)

	$(CC) $(addprefix $(SPP_CSV)/, validator.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, validator.o)


# writer.o
$(addprefix $(OPP_CSV)/, writer.o) : \
    $(addprefix $(SPP_CSV)/, writer.c writer.h parser.h serializer.h errors.h)

	$(CC) $(addprefix $(SPP_CSV)/, writer.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, writer.o)


# fileconfig.o
$(addprefix $(OPP_CSV)/, fileconfig.o) : \
    $(addprefix $(SPP_CSV)/, fileconfig.c fileconfig.h errors.h)

	$(CC) $(addprefix $(SPP_CSV)/, fileconfig.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_CSV)/, fileconfig.o)


# parser.o
$(addprefix $(OPP_CSV)/, parser.o) : \
    $(addprefix $(SPP_CSV)/, parser.c parser.h parserstate.h) \
    $(addprefix $(SPP_GENERIC)/, linkedlist.h dynamicstring.h stack.h util.h \
        table.h)

	$(CC) $(addprefix $(SPP_CSV)/, parser.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_CSV)/, parser.o)


# parserstate.o
$(addprefix $(OPP_CSV)/, parserstate.o) : \
    $(addprefix $(SPP_CSV)/, parserstate.c parserstate.h) \
    $(addprefix $(SPP_GENERIC)/, stack.h table.h linkedlist.h)

	$(CC) $(addprefix $(SPP_CSV)/, parserstate.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_CSV)/, parserstate.o)


# fields.o
$(addprefix $(OPP_CSV)/, fields.o) : \
    $(addprefix $(SPP_CSV)/, fields.c fields.h datatype.h) \
    $(addprefix $(SPP_GENERIC)/, table.h util.h)

	$(CC) $(addprefix $(SPP_CSV)/, fields.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, fields.o)


# sorter.o
$(addprefix $(OPP_CSV)/, sorter.o) : \
    $(addprefix $(SPP_CSV)/, sorter.c sorter.h datatype.h) \
    $(addprefix $(SPP_GENERIC)/, linkedlist.h table.h util.h)

	$(CC) $(addprefix $(SPP_CSV)/, sorter.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, sorter.o)


# datatype.o
$(addprefix $(OPP_CSV)/, datatype.o) : \
    $(addprefix $(SPP_CSV)/, datatype.c datatype.h)

	$(CC) $(addprefix $(SPP_CSV)/, datatype.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, datatype.o)


# serializer.o
$(addprefix $(OPP_CSV)/, serializer.o) : \
    $(addprefix $(SPP_CSV)/, serializer.c serializer.h errors.h) \
    $(addprefix $(SPP_GENERIC)/, table.h)

	$(CC) $(addprefix $(SPP_CSV)/, serializer.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, serializer.o)


# errors.o
$(addprefix $(OPP_CSV)/, errors.o) : \
    $(addprefix $(SPP_CSV)/, errors.c errors.h)

	$(CC) $(addprefix $(SPP_CSV)/, errors.c) -c $(CFLAGS) \
		-o $(addprefix $(OPP_CSV)/, errors.o)



#################################################################################
#                              	TESTING GENERICS                                #
#################################################################################

# testlinkedlist.o
$(addprefix $(OPP_TEST_GENERIC)/, testlinkedlist.o) : \
    $(addprefix $(SPP_TEST_GENERIC)/, testlinkedlist.c testlinkedlist.h) \
    $(addprefix $(SPP_TEST_BASE)/, testhelper.h) \
    $(addprefix $(SPP_GENERIC)/, linkedlist.h) \

	$(CC) $(addprefix $(SPP_TEST_GENERIC)/, testlinkedlist.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST_GENERIC)/, testlinkedlist.o)


# testutil.o
$(addprefix $(OPP_TEST_GENERIC)/, testutil.o) : \
    $(addprefix $(SPP_TEST_BASE)/, testhelper.h) \
    $(addprefix $(SPP_GENERIC)/, util.h) \
    $(addprefix $(SPP_TEST_GENERIC)/, testutil.c testutil.h) \

	$(CC) $(addprefix $(SPP_TEST_GENERIC)/, testutil.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST_GENERIC)/, testutil.o)


# testtable.o
$(addprefix $(OPP_GENERIC)/, testtable.o) : \
    $(addprefix $(SPP_TEST_BASE)/, testtable.h) \
    $(addprefix $(SPP_TEST_BASE)/, testhelper.h)

	$(CC) $(addprefix $(SPP_TEST)/, testtable.c testtable.h) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST)/, testtable.o)


# teststack.o
$(addprefix $(OPP_TEST_GENERIC)/, teststack.o) : \
    $(addprefix $(SPP_TEST_GENERIC)/, teststack.c teststack.h) \
    $(addprefix $(SPP_TEST_BASE)/, testhelper.h) \
    $(addprefix $(SPP_GENERIC)/, stack.h)

	$(CC) $(addprefix $(SPP_TEST_GENERIC)/, teststack.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST_GENERIC)/, teststack.o)


# testdynamicstring.o
$(addprefix $(OPP_TEST_GENERIC)/, testdynamicstring.o) : \
    $(addprefix $(SPP_TEST_GENERIC)/, testdynamicstring.c testdynamicstring.h) \
    $(addprefix $(SPP_GENERIC)/, dynamicstring.h linkedlist.h) \
    $(addprefix $(SPP_TEST_BASE)/, testhelper.h)

	$(CC) $(addprefix $(SPP_TEST_GENERIC)/, testdynamicstring.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST_GENERIC)/, testdynamicstring.o)


# testhelper.o
$(addprefix $(OPP_TEST_BASE)/, testhelper.o) : \
    $(addprefix $(SPP_TEST_BASE)/, testhelper.c testhelper.h)

	$(CC) $(addprefix $(SPP_TEST_BASE)/, testhelper.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST_BASE)/, testhelper.o)


# unittests.o
$(addprefix $(OPP_TEST_BASE)/, unittests.o) : \
    $(addprefix $(SPP_TEST_BASE)/, unittests.c unittests.c) \
    $(addprefix $(SPP_TEST_GENERIC)/, teststack.h testlinkedlist.h \
        testdynamicstring.h)

	$(CC) $(addprefix $(SPP_TEST_BASE)/, unittests.c) -c $(CFLAGS) \
        -o $(addprefix $(OPP_TEST_BASE)/, unittests.o)



#################################################################################
#                                 TESTING CSV                                   #
#################################################################################



#################################################################################
#         THIS IS WHERE I STORE MY ACCOUNT-KEEPING & JANITORIAL ELVES           #
#################################################################################

# Creates the directory structure required for the binary files.
$(OPP_DIRS) : 
	mkdir -p $(OPP_DIRS)

# Cleans the project directory, including the removal of /bin/
clean : 
	-rm -f $(OBJ) $(EXEC) $(DBG)
	-rm -rf $(OPP_DIRS)

