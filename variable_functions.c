#include "main.h"
#include <stdlib.h>

/**
 * add_var_node - function entry-point
 *
 * Description: adds variable at the end of a var_list list.
 * @head: double pointer to head of the linked list.
 * @varLen: variable length.
 * @value: value of the variable.
 * @valueLen: value length.
 * Return: head of linked list.
 */

var_list *add_var_node(var_list **head, int varLen, char *value, int valueLen)
{
	var_listPtr new, temp;

	new = malloc(sizeof(var_list));
	if (new == NULL)
		return (NULL);

	new->var_len = varLen;
	new->value = value;
	new->value_len = valueLen;

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
 * free_var_list - function entry-point
 *
 * Description: frees a var_list linked list
 * @head: double pointer to head of the linked list.
 * Return: void
 */

void free_var_list(var_list **head)
{
	var_listPtr temp1, temp2;

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
