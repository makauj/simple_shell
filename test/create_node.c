#include "main.h"
/**
  * create_node - create a linked list with directories from "path"in the environ variable
  * Return: the head of the linked list
  */
bin *create_node(void)
{
	bin *head = NULL;
	bin *temp;
	bin *new_node;
	char *token;
	char *path;
	char *pathcopy;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	pathcopy = strdup(path);
	if (pathcopy == NULL)
		return (NULL);
	token = strtok(pathcopy, ":");
	while (token != NULL)
	{
		new_node = (bin *)malloc(sizeof(bin));
		if (new_node == NULL)
		{
			free(pathcopy);
			return (NULL);
		}
		new_node->dir = strdup(token);
		if (new_node->dir == NULL)
		{
			free(new_node);
			free(pathcopy);
			return (NULL);
		}
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
		{
			temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = new_node;
		}
		token = strtok(NULL, ":");
	}
	free(pathcopy);
	return (head);
}
