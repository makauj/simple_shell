#include "main.h"

/**
 * execute_command - function to execute command
 * @command: command to execute
 * Return: 0 if succesfull and _1 if failed
 */

int execute_command(char *command)
{
	char *command1;
	char *envp[] = {NULL};
	char *argv[MAX_ARGS];
	int argc = 0;
	char *path;
	char *pathcopy;

	argv[argc] = strtok(command, " ");
	while (argv[argc] != NULL && argc < MAX_ARGS - 1)
	{
		argc++;
		argv[argc] = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	if (argv == NULL)
		return(-1);

	command1 = argv[0];
	if (_strcmp(command1, "env") == 0)
	{
		print_environ();
		return(0);
	}
	else if(_strcmp(command1, "echo") == 0)
	{
		echo(argv[1]);
		return (0);
	}
	else if (_strcmp(command1, "cd") == 0)
	{
		handle_cd(argv);
		return;
	}
	else if (_strcmp(command1, "exit") == 0)
	{
		exit(0);
	}
	else if (_strcmp(command1, "setenv") == 0)
	{
		_setenv(argv[1], argv[2]);
		return(0);
	}
	else if (_strcmp(command1, "unsetenv") == 0)
	{
		_unsetenv(argv[1]);
		return(0);
	}
	else if (command1[0] == '/')
	{
		pathcopy = command1;
		path = _strdup(pathcopy);
	}
	else
	{
		path = search_command(command1);
		if (path == NULL)
		{
			perror("path");
			return(-1);
		}
	}
	run_command(path, argv, envp);
	free (path);
	return(0);
}
