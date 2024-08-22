#include "main.h"

/**
 * read_command - Reads a command from stdin and returns it as a string
 *
 * Return: command
 */

char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	char *command;
	ssize_t len;

	len = getline(&buffer, &bufsize, stdin);
	if (len == -1)
	{
		free(buffer);/* Free memory allocated to buffer on failure */
		return (NULL); /* Return NULL to indicate EOF or error */
	}

	/* Remove the newline character from the buffer, if present */
	if (len > 0 && buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}

	/* Allocate memory for the command and copy it */
	command = malloc(len);
	if (command == NULL)
	{
		free(buffer);
		handle_error("Memory allocation failed\n");
		_exit(EXIT_FAILURE);
	}

	_strcpy(command, buffer);

	free(buffer);
	return (command);
}
