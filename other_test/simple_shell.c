#include "main.h"

/**
 * 
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    char **args;

    while (1)
    {
        display_prompt();
        if (read_input(&buffer, &bufsize) == -1)
        {
            if (feof(stdin))
            {
                free(buffer);
                exit(EXIT_SUCCESS);
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (buffer[0] == '\0')
            continue;

        buffer[custom_strlen(buffer) - 1] = '\0'; // Remove newline character
        args = split_line(buffer);

        if (handle_builtin_commands(args))
        {
            free(args);
            continue;
        }

        execute_command(args);
        free(args);
    }

    free(buffer);
    return 0;
}
