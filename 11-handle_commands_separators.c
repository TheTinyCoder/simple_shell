#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_sep: double pointer to head of sep_list linked list
 * @head_line: double pointer to head of line_list linked list
 * @s: string
 * Return: void
 */
void add_nodes(sep_list **head_sep, line_list **head_line, char *s)
{
	int i;
	char *line;

	s = swap_non_ops(s, 0);

	for (i = 0; s[i]; i++)
	{
		if (s[i] == ';')
			add_sep_nodeend(head_sep, s[i]);

		if (s[i] == '|' || s[i] == '&')
		{
			add_sep_nodeend(head_sep, s[i]);
			i++;
		}
	}

	line = _strtok(s, ";|&");
	do {
		line = swap_non_ops(line, 1);
		add_line_nodeend(head_line, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}


/**
 * next_line - go to the next command line stored
 *
 * @node_sep: double pointer to node of sep_list linked list
 * @node_line: double pointer to node of line_list linked list
 * @data: shell data structure
 * Return: void
 */

void next_line(sep_list **node_sep, line_list **node_line, data_t *data)
{
	int loop;
	sep_listPtr sepPtr;
	line_listPtr linePtr;

	loop = 1;
	sepPtr = (*node_sep);
	linePtr = (*node_line);

	while (sepPtr != NULL && loop)
	{
		if (data->status == 0)
		{
			if (sepPtr->separator == '&' || sepPtr->separator == ';')
				loop = 0;
			if (sepPtr->separator == '|')
				linePtr = linePtr->next, sepPtr = sepPtr->next;
		}
		else
		{
			if (sepPtr->separator == '|' || sepPtr->separator == ';')
				loop = 0;
			if (sepPtr->separator == '&')
				linePtr = linePtr->next, sepPtr = sepPtr->next;
		}
		if (sepPtr != NULL && !loop)
			sepPtr = sepPtr->next;
	}

	*node_sep = sepPtr;
	*node_line = linePtr;
}


/**
 * split_command_lines - function entry-point
 *
 * Description: splits command lines using the separators ';', '|' and '&'
 *
 * @data: shell data structure
 * @s: string
 * Return: 0 to exit, 1 to continue
 */
int split_command_lines(data_t *data, char *s)
{

	sep_listPtr head_sep, node_sep;
	line_listPtr head_line, node_line;
	int loop;

	head_sep = NULL;
	head_line = NULL;

	add_nodes(&head_sep, &head_line, s);

	node_sep = head_sep;
	node_line = head_line;

	while (node_line != NULL)
	{
		data->user_input = node_line->line_string;
		data->tokens = tokenize_line(data->user_input);
		loop = exec_line(data);
		free(data->tokens);

		if (loop == 0)
			break;

		next_line(&node_sep, &node_line, data);

		if (node_line != NULL)
			node_line = node_line->next;
	}

	free_sep_list(&head_sep);
	free_line_list(&head_line);

	if (loop == 0)
		return (0);
	return (1);
}


/**
 * tokenize_line - function entry-point
 *
 * Description: tokenizes the input string
 * @s: string.
 * Return: split string.
 */

char **tokenize_line(char *s)
{
	size_t size;
	size_t i;
	char **tokens;
	char *token;

	size = TOKEN_BUFSIZE;
	tokens = malloc(sizeof(char *) * (size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(s, TOKEN_DELIMITERS);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == size)
		{
			size += TOKEN_BUFSIZE;
			tokens = (char **)_realloc(tokens, i, sizeof(char *) * size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIMITERS);
		tokens[i] = token;
	}

	return (tokens);
}


/**
 * exec_line - function entry-point
 *
 * Description: finds builtins and executes line commands
 * @data: shell data
 * Return: 1 on success.
 */
int exec_line(data_t *data)
{
	int (*builtin)(data_t *data);

	if (data->tokens[0] == NULL)
		return (1);

	builtin = get_builtin(data->tokens[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (execute(data));
}
