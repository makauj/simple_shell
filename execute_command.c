#include "main.h"

/**
 * execute_command - function to execute command
 * @command: command to execute
 */

void execute_command(char *command)
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
	argv[argc] = NULL; /*NULL terminate argument list*/
	if (argv == NULL)
		return;

	command1 = argv[0];
	if (_strcmp(command1, "env") == 0)
	{
		print_environ();
		return;
	}
	else if (_strcmp(command1, "setenv") == 0)
	{
		_setenv(argv[1], argv[2]);
		return;
	}
	if (_strcmp(command1, "unsetenv") == 0)
	{
		_unsetenv(argv[1]);
		return;
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
			return;
		}
	}
	run_command(path, argv, envp);
	free (path);
	return;
}
