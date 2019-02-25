/* util.c
 *
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines utility functions for the CSV sorter.
 * 
 * These functions are designed to be generic, i.e. not fit for one purpose.
 * As such, they do not belong in any single C file. Functions that pertain
 * to the workings of a particular type or group of functions should not be
 * included in this file.
 */
#include "util.h"

/********************************************************************************
 *                             UTILITY FUNCTIONS                                *
 ********************************************************************************/

/*
 * Determines if a character is in a set of characters.
 */
bool charMatches(char ch, const char *arr, const int length)
{
    int c = 0;
    bool found = false;
    while (c < length && !found)
    {
        found = (ch == arr[c]);
        c++;
    }

    return found;
}

/*
 * Converts an uppercase character to lowercase. Returns the lowercase
 * variant of the input character, which may or may not be the same as
 * the original character.
 */
char charToLowerCase(char upperChar)
{
    char lowerChar = upperChar;
    if ('A' <= upperChar && upperChar <= 'Z')
    {
        lowerChar = 'a' + (lowerChar - 'A');
    }
    return lowerChar;
}

/*
 * Determines if a specified character is a printable character,
 * i.e. is not a control character and is within the ASCII interval [0, 126].
 *
 * This function is only to be used internally by functions that need it.
 */
static bool isPrintable(unsigned char ch)
{
    bool printable = true;
    if (0x00 <= ch && ch <= 0x1F)
    {
        /* Control characters. Includes \0, \r, \n, \t, etc. */
        printable = false;
    }
    else if (ch >= 0x7F)
    {
        printable = false;
    }
    return printable;
}

/*
 * Determines if a character can appear in a text file.
 */
bool isValidTextFileCharacter(char ch)
{
    bool isValid = true;
    static const unsigned int CONTROL_CHAR_COUNT = 4;
    static const char validControlChars[] = { '\r', '\n', '\t', '\f' };
    isValid = isPrintable((unsigned char)ch) || charMatches(ch,
        validControlChars, CONTROL_CHAR_COUNT);
    return isValid;
}

/*
 * Determines if a character is whitespace. This function does not consider
 * line or carriage feed characters to be whitespace.
 */
bool isWhitespace(char ch)
{
    bool whitespace = (ch == ' ' || ch == '\t');
    return whitespace;
}

/*
 * Clears the input buffer to avoid future prompts to be pre-filled.
 * Use with great care and avoid if you can.
 */
void clearInputBuffer(void)
{
    char c;
    while ((c = getchar()) != '\n')
    {
        /* Explicitly: do nothing. */
    }
}

/*
 * Checks the sign of a float. Returns -1 if the value is negative, or +1 if
 * it is positive. Returns 0 if it is neither positive nor negative.
 */
int floatSign(float value)
{
    int result = 0;
    if (value > 0.0)
    {
        result = 1;
    }
    else if (value < 0.0)
    {
        result = -1;
    }
    return result;
}

/*
 * Trims the specified characters from the front and end of a string. Returns
 * the resulting string.
 *
 * This function does not modify the original string.
 */
char *trim(char *str, const char *chars, const int NUM_CHARS)
{
    /* The start of the string, excluding whitespace. */
    char *start = NULL;

    /* The end of the string, excluding whitespace. */
    char *end = NULL;

    /* The copied trimmed string. */
    char *trimmedStr = NULL;

    int size = 0;

    /* Skip all the leading whitespace. */
    start = str;
    while (charMatches(*start, chars, NUM_CHARS))
    {
        start++;
    }

    /* We know where the string (excluding whitespace) starts. Now find where it
     * ends. We'll do this by traversing to the end, and then backtracking.
     * Thus: traverse until we find a null-terminator. */
    end = start;
    while (*end != '\0')
    {
        end++;
    }

    /* We're at the end of the string. Go back one to get the last character. */
    end--;

    /* Continue traversing backwards until:
     * (a) we find a non-whitespace character; OR
     * (b) we reach start.
     */
    while (charMatches(*end, chars, NUM_CHARS))
    {
        end--;
    }
    /* We're at the last character of the string. Add one to get the length. */
    end++;

    size = (int)(end - start);
    /* Allocate the member for the reduced string. */
    trimmedStr = (char *)malloc((size + 1) * sizeof(char));

    /* Copy from the original string to our new block of memory. */
    strncpy(trimmedStr, start, size + 1);

    /* Append a null-terminator so that string functions don't fail. */
    trimmedStr[size] = '\0';

    return trimmedStr;
}

/*
 * Creates a copy of the input string and trims whitespace from the start and end.
 *
 * Whitespace characters are defined as:
 *   '\t' tab
 *   '\r' carriage return
 *   '\n' line feed
 *   '\f' form feed
 *   ' ' space
 */
char *trimWhitespace(char *str)
{
    /* The characters (and number of) characters considered to be whitespace. */
    const int NUM_CHARS = 5;
    const char wsChars[] = { '\t', '\r', '\n', ' ', '\f' };
    char *out = trim(str, wsChars, NUM_CHARS);
    return out;
}

/*
 * Converts a string to lower-case. This function creates a new string and copies
 * the lower-case variant of all characters from one to the other. This function
 * assumes the input string is terminated with a null-terminator.
 */
char *toLowerCase(char *str)
{
    int len = strlen(str), i = 0;
    char *outStr = malloc((len + 1) * sizeof(char));
    while (i < len)
    {
        outStr[i] = charToLowerCase(str[i]);
        i++;
    }
    outStr[len] = '\0';

    return outStr;
}
