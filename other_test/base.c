#include "main.h"

/**
 * 
 */

void display_prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "#C is fun$ ", 14);
}

/**
 * 
 */

int read_input(char **buffer, size_t *bufsize)
{
    return custom_getline(buffer, bufsize, stdin);
}
