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
    char *dup_token;

    if (command == NULL)
        return (NULL);

    command_copy = _strdup(command);
    if (command_copy == NULL)
        return (NULL);

    token = strtok(command_copy, ";|&");
    while (token != NULL)
    {
        new_node = malloc(sizeof(bin));
        if (new_node == NULL)
        {
            /* cleanup on malloc failure */
            if (head)
                free_node(head);
            free(command_copy);
            return (NULL);
        }

        dup_token = _strdup(token);
        if (dup_token == NULL)
        {
            free(new_node);
            if (head)
                free_node(head);
            free(command_copy);
            return (NULL);
        }

        new_node->dir = dup_token;
        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
            temp = head;
        }
        else
        {
            temp->next = new_node;
            temp = temp->next;
        }

        token = strtok(NULL, ";|&");
    }

    /* tokens were duplicated; free the temporary copy buffer */
    free(command_copy);
    return (head);
}
