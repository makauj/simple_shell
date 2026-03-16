#include "main.h"
/**
  * search_command - searches through path in the environ variable to return path 
  *		affiliated with the command
  * @head: head of a linked list
  * @command: command retrieved from the user
  * Return: path
  */
char *search_command(char *command)
{
	bin *head;
	bin *temp;
	char *path;
	char *result;
	int dir_len;
	int cmd_len;

	head = create_node();
	if (head == NULL)
	{
		return (NULL);
	}
	if (command == NULL)
	{
		free_node(head);
		return (NULL);
	}
	temp = head;
	while (temp != NULL)
	{
		dir_len = _strlen(temp->dir);
		cmd_len = _strlen(command);
		path = malloc(dir_len + cmd_len + 2);
		if (path == NULL)
		{
			free_node(head);
			return (NULL);
		}

		path[0] = '\0';
		_strcpy(path, temp->dir);
		if (path[dir_len - 1] != '/')
			_strcat(path, "/");
		_strcat(path, command);
		if (access(path, X_OK) == 0)/* check if the file exists and is executable*/
		{
			result = _strdup(path);
			free(path);
			free_node(head);
			return (result);
		}
		free(path);
		temp = temp->next;
	}
	free_node(head);
	return (NULL);
}
