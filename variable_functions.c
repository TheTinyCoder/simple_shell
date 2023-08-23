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


/**
 * replace - function entry-point
 *
 * Description: replaces string into variables
 * @head: double pointer to head of the linked list
 * @s: string
 * @new: new string (replaced)
 * @len: new length
 * Return: replaced string
 */

char *replace(var_list **head, char *s, char *new, int len)
{
	var_listPtr idx;
	int i, j, k;

	idx = *head;
	for (j = i = 0; i < len; i++)
	{
		if (s[j] == '$')
		{
			if (!(idx->var_len) && !(idx->value_len))
			{
				new[i] = s[j];
				j++;
			}
			else if (idx->var_len && !(idx->value_len))
			{
				for (k = 0; k < idx->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < idx->value_len; k++)
				{
					new[i] = idx->value[k];
					i++;
				}
				j += (idx->var_len);
				i--;
			}
			idx = idx->next;
		}
		else
		{
			new[i] = s[j];
			j++;
		}
	}

	return (new);
}


/**
 * replace_var - function entry-point
 *
 * Description: calls functions to replace string into var
 * @s: string
 * @data: shell data structure
 * Return: replaced string
 */
char *replace_var(char *s, data_t *data)
{
	var_listPtr head, idx;
	char *status, *new;
	int olen, nlen;

	status = _itoa(data->status);
	head = NULL;

	olen = check_for_vars(&head, s, status, data);

	if (head == NULL)
	{
		free(status);
		return (s);
	}

	idx = head;
	nlen = 0;

	while (idx != NULL)
	{
		nlen += (idx->value_len - idx->var_len);
		idx = idx->next;
	}

	nlen += olen;

	new = malloc(sizeof(char) * (nlen + 1));
	new[nlen] = '\0';

	new = replace(&head, s, new, nlen);

	free(s);
	free(status);
	free_var_list(&head);

	return (new);
}
