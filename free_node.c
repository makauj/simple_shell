#include "main.h"
/**
  *free_node - free nodes
  * @head: Head of the node
  * Return: 0 on success, non zero on failure
  */
int free_node(bin *head)
{
	bin *temp;

	if (head == NULL)
		return (-1);
	temp = head;
	while (temp != NULL)
	{
		head = temp->next;
		free(temp);
		temp = head;
	}
	return (0);
}
