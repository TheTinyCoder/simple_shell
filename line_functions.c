#include "main.h"
#include <stdlib.h>

/**
 * add_line_nodeend - function entry-point
 *
 * Description: adds a command line string at end of line_list linked list
 * @head: double pointer to head of the linked list
 * @line_string: command line string
 * Return: head of linked list
 */
line_list *add_line_nodeend(line_list **head, char *line_string)
{
	line_listPtr new, temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line_string = line_string;
	new->next = NULL;
	temp = (*head);

	if (temp == NULL)
	{
		(*head) = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_line_list - function entry-point
 *
 * Description: frees a line_list linked list
 * @head: double pointer to head of the linked list.
 * Return: void
 */
void free_line_list(line_list **head)
{
	line_listPtr temp1, temp2;

	if (head != NULL)
	{
		temp2 = (*head);
		while ((temp1 = temp2) != NULL)
		{
			temp2 = temp2->next;
			free(temp1);
		}
		*head = NULL;
	}
}
