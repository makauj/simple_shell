#include "main.h"
/**
  *free_node - free nodes
  * @head: Head of the node
  * Return: 0
  */
void free_node(bin *head)
{
	bin *temp;
	bin *next;

	temp = head;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}
