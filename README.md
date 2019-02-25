# CSV-Sorter-Academia
(Academia project) C program to sort CSV files of an arbitrary length and format.


# Introduction
This README file has been prepared to assist in marking the assignment submission.
This file summarizes the submission and is provided in addition to the extensive
documentation within the .c and .h files, as well as the Makefile.

# Files and their purposes

/Makefile<br />
   Makefile for the program. Contains commands to build the project executable.

/src/main.c
/src/main.h<br />
    Entry point for the program. Calls all the appropriate functions to:<br />
    (1) determine the input and output data<br />
    (2) parse the input file<br />
    (3) sort the CSV table<br />
    (4) write the CSV table to a file

/src/menu.c<br />
/src/menu.h<br />
    Handles all user interaction.

/src/csv/* handles parsing CSV files, and writing CSV tables to files

    /src/csv/datatype.c<br />
    /src/csv/datatype.h<br />
        Defines the data types accepted by the CSV parser. That is, the strings
        that appear after the field name in the header row; as: "name (string)"

    /src/csv/errors.c<br />
    /src/csv/errors.h<br />
        Defines errors that the parser can encounter.

    /src/csv/fields.c<br />
    /src/csv/fields.h<br />
        Defines a Field structure which stores meta-data about a column (data type,
        field name, sort name)

    /src/csv/fileconfig.c<br />
    /src/csv/fileconfig.h<br />
        Defines a container structure for the input and output file names.

    /src/csv/parser.c<br />
    /src/csv/parser.h<br />
        Defines the functions required to parse a CSV file and output the result as
        a (generic) table.

    /src/csv/parserstate.c<br />
    /src/csv/parserstate.h<br />
        Defines a state mechanism for the parser. Determines what the parser is
        currently doing. This is used to facilitate "partial parsing".

    /src/csv/reader.c<br />
    /src/csv/reader.h<br />
        Defines the functions required to read a CSV file, and outputs the result
        as a generic Table. Uses parser.c to do the parsing work.

    /src/csv/serializer.c<br />
    /src/csv/serializer.h<br />
        Defines the functions required to serialize a Table in CSV format. This is
        independent of Table, as a Table can be represented in many different
        formats.

    /src/csv/sorter.c<br />
    /src/csv/sorter.h<br />
        Defines the functions required to sort a Table.

    /src/csv/validator.c<br />
    /src/csv/validator.h<br />
        Defines the functions to validate a Table for CSV compatibility.

    /src/csv/writer.c<br />
    /src/csv/writer.h<br />
        Defines the functions required to write a Table to CSV format. Uses the
        serializer to achieve this.

/src/generic/*<br />
    Defines generic functions which can be used for many different purposes.<br />

    /src/generic/dynamicstring.c<br />
    /src/generic/dynamicstring.h<br />
        Defines a structure that allows dynamic strings. Implements the linked list
        structure.

    /src/generic/linkedlist.c<br />
    /src/generic/linkedlist.h<br />
        Defines a structure that allows for dynamic (linked) lists.

    /src/generic/stack.c<br />
    /src/generic/stack.h<br />
        Defines a structure that permits 'last in/first out' mechanics. Implements
        the linked list structure.

    /src/generic/table.c<br />
    /src/generic/table.h<br />
        Defines a structure for the construction of a dynamic N x M list.

    /src/generic/util.c<br />
    /src/generic/util.h<br />
        Defines generic functions that don't belong to any one particular file.


# Additional information
My submission is organised according to the structure of the program. I designed
my components to work independently of each other, i.e. tried to avoid coupling
wherever possible. The decision was made to group them in logical subdirectories
of the 'src' directory. As a result of this organisation, the Makefile in
particular became a lot more complicated. For cleanliness, the object files
created by the compiler will not be stored in /src/, but in /bin/, which will
mirror the directory structure of /src/.


STATEMENT OF PROGRESS:<br />
[X] DONE<br />
[?] PARTIALLY DONE<br />
[ ] NOT DONE

[X] Your program must be thoroughly documented using C comments.<br />
[X] Take in two command-line parameters - the names of the input and output files.<br />
    Description: Done. If the user does not enter both the input and output files,
    the program will exit and warn the user that no input or output file was
    specified.
[X] Reads the command-line parameters in any order.<br />
    Description: To read the command-line parameters, my program loops across all
    command-line arguments except for the first (file name) and checks if they
    are supported. for the 'o' and 'i' switches, my program consumes the next
    token (argument) and uses it as the output and input files respectively.<br />
[X] Invalid command-line parameters cause the program to output a usage message.
    Description: Done. The program loops across all arguments and finds any that
    are invalid. Even if the user enters all information required, the program
    will still output a usage hint.<br />
[X] Read the input file and store its contents in a generic linked list.
    Description: Done. I have decided to keep my CSV parser generic; it stores
    all data as strings, even if the header says "(integer)". Instead, the main.c
    and menu.c files are responsible for determining the sort order. That is, I
    delegated the responsibility of interpreting the CSV file to whoever uses
    the sorter.c functionality.<br />
[X] Output a menu to the user requesting how the user would like the contents of
    the file to be sorted.
    Description: Done. My program parses the input file and then requests how
    the user wants the data stored. When the user is asked, the Table has been
    created and we know exactly what header columns exist as well as their data
    types.<br />
[X] The user must be able to sort on any of the columns, in ascending or
    descending order.
    Description: Done. My program uses a generic linked list sorting algorithm
    which allows the caller to pass a single parameter - a void pointer to any
    data type - to the comparator function. This was the biggest challenge in
    writing this program, because of the no global variables restriction. Without
    global variables, I believe the only solution is to pass the configuration to
    the sorting function, which I have done.<br />
[X] Sort the rows of the input file using generic insertion sort (in-place).
    Description: Done.<br />
[?] It must import a generic linked list and a compare function, export the
    sorted linked list
    Description: Partially done. Insertion sort is generic and takes a generic
    linked list, but the sorting function does NOT export the linked list. Because
    the algorithm is designed to be in-place, the caller already has access to the
    (now-sorted) list.<br />
[X] Write the sorted data to the specified output file, using the same format as
    the input file.
    Description: Done.

Miscellaneous checklist:<br />
[X] Makefile.<br />
    Description: Done. Because my program is logically separated into different
    project subdirectories, my Makefile became very complex very fast.<br />
[X] Testing on the lab machines.<br />
    Description: Tested on lab machine identified by service tag FR56HZ1.<br />
[X] Testing user input (sanity-checking).<br />
    Description: Done.<br />
[X] Testing for memory leaks.<br />
    Description: Done. Valgrind finds no potential memory leaks.

# Known bugs / defects
[1] [DEFECT] The program takes a really long time for larger files when being
    analysed by Valgrind.

