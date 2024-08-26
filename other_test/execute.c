#include "main.h"

void execute_command(char **args)
{
    char *command_path = find_command(args[0]);
    if (command_path == NULL)
    {
        write(STDOUT_FILENO, "Command not found\n", 18);
        return;
    }

    int status;
    if (fork() == 0)  // Child process
    {
        execve(command_path, args, NULL);
        perror("Error");
        _exit(EXIT_FAILURE);
    }
    else  // Parent process
    {
        wait(&status);  // Wait for child to finish
    }

    free(command_path);  // Free the memory allocated for the command path
}
