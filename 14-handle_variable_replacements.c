#include "main.h"
#include <stdio.h>

/**
 * check_for_vars - function entry-point
 *
 * Description: checks for variable replacements ($$ or $?)
 * @head: double pointer to head of data_t linked list
 * @s: string
 * @status: last status of the shell
 * @shell_data: shell data structure
 * Return: no return
 */

int check_for_vars(var_list **head, char *s, char *status, data_t *shell_data)
{
	int i, status_len, pid_len;

	status_len = _strlen(status);
	pid_len = _strlen(shell_data->pid);

	for (i = 0; s[i]; i++)
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				add_var_node(head, 2, status, status_len), i++;
			else if (s[i + 1] == '$')
				add_var_node(head, 2, shell_data->pid, pid_len), i++;
			else if (s[i + 1] == '\n')
				add_var_node(head, 0, NULL, 0);
			else if (s[i + 1] == '\0')
				add_var_node(head, 0, NULL, 0);
			else if (s[i + 1] == ' ')
				add_var_node(head, 0, NULL, 0);
			else if (s[i + 1] == '\t')
				add_var_node(head, 0, NULL, 0);
			else if (s[i + 1] == ';')
				add_var_node(head, 0, NULL, 0);
			else
				check_for_env(head, s + i, shell_data);
		}
	}

	return (i);
}


/**
 * check_for_env - function entry-point
 *
 * Description: checks if the typed variable is an env variable
 *
 * @head: double pointer to head of data_t linked list
 * @s: string
 * @shell_data: shell data structure
 * Return: no return
 */
void check_for_env(var_list **head, char *s, data_t *shell_data)
{
	int row, c, j, val_len;
	char **_environ;

	_environ = shell_data->_environ;
	for (row = 0; _environ[row]; row++)
	{
		for (j = 1, c = 0; _environ[row][c]; c++)
		{
			if (_environ[row][c] == '=')
			{
				val_len = _strlen(_environ[row] + c + 1);
				add_var_node(head, j, _environ[row] + c + 1, val_len);
				return;
			}

			if (s[j] == _environ[row][c])
				j++;
			else
				break;
		}
	}

	for (j = 0; s[j]; j++)
	{
		if (s[j] == ' ' || s[j] == '\t' || s[j] == ';' || s[j] == '\n')
			break;
	}

	add_var_node(head, j, NULL, 0);
}

