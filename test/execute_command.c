#include "main.h"

/**
 * execute_command - function to execute command
 * @command: command to execute
 */

void execute_command(char *command)
{
	pid_t pid = fork();
	int status;
	char *envp[] = {NULL};
	char *argv[MAX_ARGS];
	int argc = 0;
	char *path;

	argv[argc] = strtok(command, " ");
	while (argv[argc] != NULL && argc < MAX_ARGS - 1)
	{
		argc++;
		argv[argc] = strtok(NULL, " ");
	}
	argv[argc] = NULL; /*NULL terminate argument list*/

	path = search_command(argv[0]);
	if (path == NULL)
	{
		perror("path");
		return;
	}
	if (argv[0] == NULL)
	{
		return;
	}
	if (pid < 0)
	{
		handle_error("fork");
		return;
	}
	else if (pid == 0)
	{
		/* Child process */
		execve(path, argv, envp);
		/* If execvp returns, there was an error */
		handle_error("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		if (waitpid(pid, &status, 0) < 0)
		{
			handle_error("waitpid");
		}
	}
	free(path);
}
