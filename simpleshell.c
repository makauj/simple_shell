#include "main.h"
/**
 * main - main to the function
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *command;
	bin *head, *temp;
	if (argc > 2)
	{
		write(2, "Usage: simple_shell [filename]\n", 30);
		return (1);
	}

	if (argc == 2)
	{
		FILE *fp;
		char *buffer = NULL;
		size_t bufsize = 0;
		ssize_t len;

		fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			perror("fopen");
			return (1);
		}

		while ((len = _getline(&buffer, &bufsize, fp)) != -1)
		{
			ssize_t len1 = 0;
			int i = 0;

			if (len > 0 && buffer[len - 1] == '\n')
				buffer[len - 1] = '\0';

			while (buffer[i] != '#' && buffer[i] != '\0')
			{
				len1++;
				i++;
			}

			command = malloc(len1 + 1);
			if (command == NULL)
			{
				free(buffer);
				fclose(fp);
				handle_error("malloc");
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < len1; i++)
				command[i] = buffer[i];
			command[i] = '\0';

			if (_strlen(command) == 0)
			{
				free(command);
				continue;
			}
			execute_command(command);
			free(command);
		}
		free(buffer);
		fclose(fp);
		return (0);
	}

	/* interactive mode */
	while (1)
	{
		display_prompt();
		command = read_command();

		if (command == NULL)
			break;
		if (_strlen(command) == 0 || _strcmp(command, "\n") == 0)
		{
			free(command);
			continue;
		}
		head = command_node(command);
		if (head == NULL)
		{
			perror("head");
			free(command);
			return (-1);
		}
		temp = head;
		while (temp != NULL)
		{
			execute_command(temp->dir);
			temp = temp->next;
		}
		free(command);
		free_node(head); /* Free the allocated memory */
	}
	return (0);
}
