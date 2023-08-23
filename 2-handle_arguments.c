#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * char_repetitions - function entry-point
 *
 * Description: counts the repetitions of a char
 * @s: string
 * @idx: index
 * Return: repetitions
 */

int char_repetitions(char *s, int idx)
{
	if (*(s - 1) == *s)
		return (char_repetitions(s - 1, idx + 1));

	return (idx);
}


/**
 * first_char_index - function entry-point
 *
 * Description: finds index of the first char
 * @s: string
 * @idx: index
 * Return: 1 if error, 0 otherwise
 */

int first_char_index(char *s, int *idx)
{

	for (*idx = 0; s[*idx]; *idx += 1)
	{
		if (s[*idx] == ' ' || s[*idx] == '\t')
			continue;

		if (s[*idx] == ';' || s[*idx] == '|' || s[*idx] == '&')
			return (-1);

		break;
	}

	return (0);
}


/**
 * print_syntax_error - function entry-point
 *
 * Description: prints if syntax error is found
 * @data: shell data structure
 * @s: string
 * @idx: index of the error
 * @boolean: control msg error
 * Return: void
 */
void print_syntax_error(data_t *data, char *s, int idx, int boolean)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int len;

	if (s[idx] == ';')
	{
		if (boolean == 0)
			msg = (s[idx + 1] == ';' ? ";;" : ";");
		else
			msg = (s[idx - 1] == ';' ? ";;" : ";");
	}

	if (s[idx] == '|')
		msg = (s[idx + 1] == '|' ? "||" : "|");

	if (s[idx] == '&')
		msg = (s[idx + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(data->counter);
	len = _strlen(data->argv[0]) + _strlen(counter);
	len += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, data->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}


/**
 * check_syntax - function entry-point
 *
 * Description: finds syntax error
 * @data: shell data structure
 * @s: string
 * Return: 1 if error, 0 otherwise
 */

int check_syntax(data_t *data, char *s)
{
	int begin = 0;
	int f_char_idx = 0;
	int i = 0;

	f_char_idx = first_char_index(s, &begin);
	if (f_char_idx == -1)
	{
		print_syntax_error(data, s, begin, 0);
		return (1);
	}

	i = syntax_error(s + begin, 0, *(s + begin));
	if (i != 0)
	{
		print_syntax_error(data, s, begin + i, 1);
		return (1);
	}

	return (0);
}
