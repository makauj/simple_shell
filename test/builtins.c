#include "main.h"

/**
 * _exit - function to exit
 * @args: arguments
 */

struct builtin
{
	char *name;
	void (*func)(char **args);
};

struct builtin builtins[] = {
	{"exit", _exit},
	{"cd", _cd}
};

int _builtins()
{
	return (sizeof(builtins) / sizeof(struct builtin))
}
/**
 * _exit - function to exit
 * @args: arguments
 */
void _exit(char **args)
{
	exit(0);
}

/**
 * _cd - change directory
 * @args: arguments
 */

void _cd(char **args)
{
	const char *msg;

	msg = "cd: missing argument\n"
	if (args[1] == NULL)
		write(STDERR_FILENO, error_message, sizeof(msg) - 1);
	else
	{
		if (chdir(args[1]) != 0)
			{
				perror("cd");
			}
	}
}
