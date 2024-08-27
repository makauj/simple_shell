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
	ssize_t len1 = 0;
	int i = 0;

	len = getline(&buffer, &bufsize, stdin);
	if (len == -1)
	{
		/**
		 * We should consider changing 'buffer'to
		 * something else. It may cause confusion later on.
		 */
		free(buffer);/* Free memory allocated to buffer on failure */
		return (NULL); /* Return NULL to indicate EOF or error */
	}
	/* Remove the newline character from the buffer, if present */
	if (len > 0 && buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}


	while (buffer[i] != '#' && buffer[i] != '\0')
	{
		len1++;
		i++;
	}

	/* Allocate memory for the command and copy it */
	command = malloc(len1 + 1);
	if (command == NULL)
	{
		free(buffer);
		handle_error("malloc");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < len1; i++)
	{
		command[i] = buffer[i];
	}
	command[i] = '\0';
	free(buffer);
	return (command);
}
/**
 * I noticed I had not properly handled memory allocation
 * so I added free buffer where relevant.
 * Also noticed that len was not properly initiated. This helped remove
 * strlen so we only need to handle strcpy.
 *
 */
