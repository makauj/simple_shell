#include "main.h"

/**
 * execute_command - function to execute command
 * @command: command to execute
 * Return: 0 if successful and -1 if failed
 */
int execute_command(char *command)
{
    char *command1;
    char **argv;
    int argc = 0;
    int status;
    char *path = NULL;
    char *token;

    if (command == NULL)
        return (-1);

    argv = malloc(sizeof(char *) * MAX_ARGS);
    if (argv == NULL)
        return (-1);

    token = _strtok(command, " \t");
    while (token != NULL && argc < MAX_ARGS - 1)
    {
        argv[argc++] = token;
        token = _strtok(NULL, " \t");
    }
    argv[argc] = NULL;

    /* nothing to do */
    if (argc == 0)
    {
        free(argv);
        return (0);
    }

    command1 = argv[0];

    if (_strcmp(command1, "env") == 0)
    {
        print_environ();
        free(argv);
        return (0);
    }
    else if (_strcmp(command1, "echo") == 0)
    {
        echo(argv[1]);
        free(argv);
        return (0);
    }
    else if (_strcmp(command1, "cd") == 0)
    {
        handle_cd(argv);
        free(argv);
        return (0);
    }
    else if (_strcmp(command1, "exit") == 0)
    {
        free(argv);
        exit(0);
    }
    else if (_strcmp(command1, "setenv") == 0)
    {
        _setenv(argv[1], argv[2]);
        free(argv);
        return (0);
    }
    else if (_strcmp(command1, "unsetenv") == 0)
    {
        _unsetenv(argv[1]);
        free(argv);
        return (0);
    }
    else if (command1[0] == '/')
    {
        path = _strdup(command1);
        if (path == NULL)
        {
            free(argv);
            return (-1);
        }
    }
    else
    {
        path = search_command(command1);
        if (path == NULL)
        {
            print_string(command1);
            print_string(": command not found\n");
            free(argv);
            return (-1);
        }
    }

    status = run_command(path, argv, environ);

    free(path);
    free(argv);
    return (status);
}
