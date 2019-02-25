/* dynamicstring.h
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Contains functions for creating and adding to dynamic strings.
 */
#include "dynamicstring.h"

/********************************************************************************
 *                           CONSTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Creates a dynamic string and initializes the fields of it.
 */
DynamicString *createDynamicString(void)
{
    DynamicString *dStr = NULL;

    /* Allocate memory for the structure. */
    dStr = (DynamicString *)malloc(sizeof(DynamicString));

    /* Create a LinkedList to add to. */
    dStr->substrings = createLinkedList();
    dStr->length = 0;

    return dStr;
}


/********************************************************************************
 *                             ACCESSOR FUNCTIONS                               *
 ********************************************************************************/

/*
 * Gets the length of the DynamicString. That is, how many characters it contains.
 */
int getDynamicStringLength(DynamicString *dStr)
{
    int length = 0;
    if (dStr != NULL)
    {
        length = dStr->length;
    }

    return length;
}

/*
 * Gets the last, and hence current buffer that is being used to store substrings
 * of the larger, dynamic string.
 */
static char *getDynamicStringBufferTail(DynamicString *dStr)
{
    char *buffer = NULL;

    /* Get the last value in the linked list. */
    buffer = getLinkedListValueAt(dStr->substrings, -1);

    return buffer;
}

/*
 * Converts a dynamic string to a single, large string.
 */
char *serializeDynamicString(DynamicString *dStr)
{
    char *str = NULL;
    LinkedListNode *node = NULL;
    if (dStr != NULL)
    {
        int offset, length;

        offset = 0;
        length = getDynamicStringLength(dStr);
        node = getLinkedListHead(dStr->substrings);
        str = (char *)malloc((length + 1) * sizeof(char));

        while (node != NULL)
        {
            char *value = getNodeValue(node);
            int bufOffset = 0;
            while (bufOffset < SIZE_DYNAMIC_STRING_BLOCK && offset < length)
            {
                str[offset] = value[bufOffset];
                bufOffset++;
                offset++;
            }

            node = getNextNode(node);
        }

        /* Append the null-terminator to avoid potential over-running of
         * string boundaries by string functions. */
        str[length] = '\0';
    }

    return str;
}


/********************************************************************************
 *                             MUTATOR FUNCTIONS                                *
 ********************************************************************************/

/*
 * Adds a node to the dynamic string - a buffer of a constant size that can be
 * used to add additional space to a dynamic string.
 */
static void addDynamicStringNode(DynamicString *dStr)
{
    char *substring = NULL;
    if (dStr != NULL)
    {
        /* Allocate space for the string, and add it to the LinkedList. */
        substring = (char *)malloc(SIZE_DYNAMIC_STRING_BLOCK * sizeof(char));
        addValue(dStr->substrings, substring);
    }
}

/*
 * Clears the dynamic string's buffer. This function frees all memory
 * associated with the string so that the string can be replaced with
 * something else.
 */
static void clearDynamicStringBuffer(DynamicString *dStr)
{
    if (dStr != NULL)
    {
        /* The LinkedList has its own freeing function. */
        freeLinkedList(dStr->substrings);

        /* Replace the LinkedList with a new, empty one. */
        dStr->substrings = createLinkedList();
    }
}

/*
 * Appends a string to a dynamic string.
 */
void appendStringToDynamicString(DynamicString *dStr, char *str)
{
    char *buf = NULL;
    /* Append to the char block contained in the tail node of the list.
     * If this block is not big enough to store the whole string str, then
     * add nodes as needed. */
    while (*str != '\0')
    {
        /* If we've reached the end of the string buffer, then create a new
         * string buffer. */
        if ((dStr->length % SIZE_DYNAMIC_STRING_BLOCK) == 0)
        {
            /* Add a new substring to the LinkedList. */
            addDynamicStringNode(dStr);
        }

        /* Get the current string buffer being appended to. */
        buf = getDynamicStringBufferTail(dStr);

        /* Append the character to the string buffer at the current offset. */
        buf[dStr->length % SIZE_DYNAMIC_STRING_BLOCK] = *str;

        /* Increment the dynamic string length. */
        (dStr->length)++;

        /* Repeat the process for the next character. */
        str++;
    }
}

/*
 * Appends a single character to a dynamic string.
 */
void appendCharToDynamicString(DynamicString *dStr, char chr)
{
    char arr[2];
    /* Create a string with just one character in it. This will be two array
     * elements long - including arr[1] for the null-terminator. */
    arr[0] = chr;
    arr[1] = '\0';

    /* Let the append string function handle the logic behind appending. */
    appendStringToDynamicString(dStr, arr);
}

/*
 * Replaces the entire contents of a dynamic string with the specified string.
 */
void setDynamicStringValue(DynamicString *dStr, char *str)
{
    /* Clear the buffer and then append the new string. */
    clearDynamicStringBuffer(dStr);
    appendStringToDynamicString(dStr, str);
}


/********************************************************************************
 *                            DESTRUCTOR FUNCTIONS                              *
 ********************************************************************************/

/*
 * Frees all memory associated with a DynamicString.
 */
void freeDynamicString(DynamicString *dStr)
{
    if (dStr != NULL)
    {
        LinkedListNode *node = getLinkedListHead(dStr->substrings);
        while (node != NULL)
        {
            char *substring = (char *)getNodeValue(node);
            if (substring != NULL)
            {
                free(substring);
            }
            node = getNextNode(node);
        }
        freeLinkedList(dStr->substrings);
        free(dStr);
    }

}

