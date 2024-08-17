#include "main.h"

/**
 * read_command - Reads a command from stdin and returns it as a string
 *
 * Return: command
 */

char *read_command(void)
{
	char buffer = NULL;
	size_t bufsize = 0;
	char *command;
	size_t len;

	if (getline(&buffer, &bufsize, stdin) == -1)
	{
		return (NULL); /* Return NULL to indicate EOF or error */
	}

	/* Remove the newline character from the buffer, if present */
	len = strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}

	/* Allocate memory for the command and copy it */
	command = malloc(len);
	if (command == NULL)
	{
		handle_error("malloc");
		exit(EXIT_FAILURE);
	}

	strcpy(command, buffer);
	return (command);
}
