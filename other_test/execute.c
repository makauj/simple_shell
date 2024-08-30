#include "main.h"

/**
 * execute_command - function that finds and executes commands
 * @args: argumnents
 * 
 */
void execute_command(char **args)
{
	char *command_path;
	
	command_path = find_command(args[0]);

	if (command_path == NULL)
	{
		write(STDOUT_FILENO, "Command not found\n", 18);
		return;
	}
	else
	{
		exec_command(command_path, args);
		free(command_path);
	}
}
/**
 * exec_command - function that forks commands
 * @command_path: command path
 * @args: arguments
 */
void exec_command(char *command_path, char **args)
{
	int status;

	if (fork() == 0)
	{
		execve(command_path, args, NULL);
		perror("Error");
		_exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}

}
