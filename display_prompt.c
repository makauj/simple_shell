#include "main.h"
#include <unistd.h>
#include <stdio.h>

/**
 * display_prompt - print shell prompt only for interactive sessions
 */
void display_prompt(void)
{
    /* print prompt only when stdin is a terminal */
    if (!isatty(STDIN_FILENO))
        return;

    printf("($) ");
    fflush(stdout);
}
