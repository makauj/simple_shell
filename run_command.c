#include "main.h"
/**
  * run_command - execute a command in a child process
  * @argv: arguments
  * @path: path
  * @envp: environment
  * Return: 0 on success, -1 on failure
  */
int run_command(char *path, char **argv, char **envp)
{
	int st = 0;
	pid_t pid;

	if (path == NULL && argv ==NULL && envp == NULL)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		execve(path, argv, envp);
	}
	else
	{
		if (waitpid(pid, &st, 0) < 0)
		{
			perror("waitpid");
			return (-1);
		}
	}
	return (0);
}
