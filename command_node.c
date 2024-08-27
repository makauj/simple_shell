#include "main.h"
/**
  * command_node - create a linked list containing the commands
  * Return: head of the linked list
  */
bin *command_node(char *command)
{
	bin *head = NULL;
	bin *new_node;
	char *token;
	bin *temp = NULL;
	char *command_copy;

	if (command == NULL)
		return(NULL);
	command_copy = _strdup(command);
	if (command_copy == NULL)
		return (NULL);
	token = strtok(command_copy, ";|&");
	while (token != NULL)
	{
		new_node = (bin *) malloc(sizeof(bin));
		if (new_node == NULL)
			return (NULL);
		new_node->dir = token;
		if (new_node->dir == NULL)
			return (NULL);
		new_node->next = NULL;
		if (head == NULL)
		{
			head = new_node;
			temp = head;
		}
		else
		{
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = new_node;
		}
		token = strtok(NULL, ";|&");

	}
	return (head);
	free(command_copy);
}
