#include "main.h"

/**
 * main - main to the function
 *
 * Return: 0
 */

int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();
		command = read_command();

		if (command == NULL)
		{
			/* Handle end-of-file (Ctrl+D) */
			print_string("\n");
			_exit(EXIT_SUCCESS);
		}
		/* Ignore empty commands */
		if (_strlen(command) > 0)
		{
			execute_command(command);
		}

		free(command); /* Free the allocated memory */
	}

	return (0);
}
