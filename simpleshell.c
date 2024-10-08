#include "main.h"

/**
 * main - main to the function
 *
 * Return: 0
 */

int main(void)
{
	char *command;
	bin *head;
	bin *temp;

	while (1)
	{
		display_prompt();
		command = read_command();

		if (command == NULL || _strlen(command) == 0 || _strcmp(command, "\n") == 0)
		{
			free(command);
			continue;
		}

		/* call a linked list with commands seperated by ;*/
		head = command_node(command);
		if (head == NULL)
		{
			perror("head");
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
