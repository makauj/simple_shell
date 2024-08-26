#include "main.h"
/**
 * Custom strtok function
 */
char *_strtok(char *str, const char *delim)
{
    static char *saved_str;
    if (str)
        saved_str = str;
    if (!saved_str || *saved_str == '\0')
        return NULL;

    char *start = saved_str;
    while (*saved_str)
    {
        const char *d = delim;
        while (*d)
        {
            if (*saved_str == *d)
            {
                *saved_str++ = '\0';
                if (saved_str == start)
                {
                    start++;
                    continue;
                }
                return start;
            }
            d++;
        }
        saved_str++;
    }
    return start;
}
