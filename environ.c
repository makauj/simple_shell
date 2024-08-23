#include "main.h"
/**
  * print_environ - print the current environment
  * Return: 0
  */
void print_environ()
{
	int i = 0;
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		handle_error("fork");
		return;
	}
	if (pid == 0)
	{
		while (environ[i] != NULL)
		{
			print_string(environ[i]);
			print_string("\n");
			i++;
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) > 0)
		{
			perror("waitpid");
			return;
		}
	}
	return;
}
