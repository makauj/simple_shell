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
		free(buffer);
		return (NULL);
	}
	if (len > 0 && buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}

	while (buffer[i] != '#' && buffer[i] != '\0')
	{
		len1++;
		i++;
	}

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
