#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * env_error - function entry-point
 *
 * Description: error message for env
 * @data: shell data structure
 * Return: error message
 */

char *env_error(data_t *data)
{
	int len;
	char *error;
	char *lines;
	char *msg;

	lines = _itoa(data->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(data->argv[0]) + _strlen(lines);
	len += _strlen(data->tokens[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(lines);
		return (NULL);
	}

	_strcpy(error, data->argv[0]);
	_strcat(error, ": ");
	_strcat(error, lines);
	_strcat(error, ": ");
	_strcat(error, data->tokens[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(lines);

	return (error);
}


/**
 * path_error - function entry-point
 *
 * Description: error message for path and failure denied permission.
 * @data: shell data structure
 *
 * Return: The error string.
 */

char *path_error(data_t *data)
{
	int len;
	char *lines;
	char *error;

	lines = _itoa(data->counter);
	len = _strlen(data->argv[0]) + _strlen(lines);
	len += _strlen(data->tokens[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(lines);
		return (NULL);
	}
	_strcpy(error, data->argv[0]);
	_strcat(error, ": ");
	_strcat(error, lines);
	_strcat(error, ": ");
	_strcat(error, data->tokens[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(lines);
	return (error);
}


/**
 * syntax_error - function entry-point
 *
 * Description: finds syntax errors
 * @s: string
 * @idx: index
 * @last: last char read
 * Return: index of error, or 0
 */

int syntax_error(char *s, int idx, char last)
{
	int count;

	if (*s == '\0')
		return (0);

	if (*s == ' ' || *s == '\t')
		return (syntax_error(s + 1, idx + 1, last));

	if (*s == ';')
		if (last == '|' || last == '&' || last == ';')
			return (idx);

	if (*s == '|')
	{
		if (last == ';' || last == '&')
			return (idx);

		if (last == '|')
		{
			count = char_repetitions(s, 0);
			if (count == 0 || count > 1)
				return (idx);
		}
	}

	if (*s == '&')
	{
		if (last == ';' || last == '|')
			return (idx);

		if (last == '&')
		{
			count = char_repetitions(s, 0);
			if (count == 0 || count > 1)
				return (idx);
		}
	}

	return (syntax_error(s + 1, idx + 1, *s));

}


/**
 * get_error - function entry-point
 *
 * Description: calls the error
 * @data: shell data structure
 * @error_val: error value
 * Return: error
 */

int get_error(data_t *data, int error_val)
{
	char *error;

	switch (error_val)
	{
	case -1:
		error = env_error(data);
		break;
	case 126:
		error = path_error(data);
		break;
	case 127:
		error = error_404(data);
		break;
	case 2:
		if (_strcmp("exit", data->tokens[0]) == 0)
			error = exit_error(data);
		else if (_strcmp("cd", data->tokens[0]) == 0)
			error = cd_error(data);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data->status = error_val;
	return (error_val);
}
