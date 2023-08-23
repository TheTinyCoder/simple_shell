#include "main.h"
#include <stdlib.h>

/**
 * add_sep_nodeend - function entry-point
 *
 * Description: adds a separator to node end of a sep_list.
 * @head: double pointer to head of sep_list linked list.
 * @separator: separator found (';', '|', or '&').
 * Return: head of linked list.
 */

sep_list *add_sep_nodeend(sep_list **head, char separator)
{
	sep_listPtr new, temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = separator;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
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
 * free_sep_list - function entry-point
 *
 * Description: frees a sep_list linked list
 * @head: double pointer to head of the linked list.
 * Return: void
 */

void free_sep_list(sep_list **head)
{
	sep_listPtr temp1, temp2;

	if (head != NULL)
	{
		temp2 = (*head);
		while ((temp1 = temp2) != NULL)
		{
			temp2 = temp2->next;
			free(temp1);
		}
		(*head) = NULL;
	}
}

