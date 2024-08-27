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
	char path[1024];

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
		path[0] = '\0';/* ensure the buffer is empty*/
		_strcpy(path, temp->dir);/*copy data in the node to the buffer*/
		if (path[_strlen(path) - 1] != '/')
			strcat(path, "/");
		_strcat(path, command);
		if (access(path, X_OK) == 0)/* check if the file exists and is executable*/
		{
			return (_strdup(path));
		}
		else
			temp = temp->next;
	}
	free_node(head);
	return (NULL);
}
