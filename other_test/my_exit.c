#include "main.h"

/**
 * my_exit - function to handle exit command
 * @args: arguments
 */

void my_exit(char **args)
{
	free(args);
	exit(EXIT_SUCCESS);
}
