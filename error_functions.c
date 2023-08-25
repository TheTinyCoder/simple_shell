#include "main.h"
#include <stdlib.h>

/**
 * cd_error - function entry-point
 *
 * Description: error message for cd command
 * @data: shell data structure
 * Return: error message
 */

char *cd_error(data_t *data)
{
	int len, len_id;
	char *error, *line, *msg;

	line = _itoa(data->counter);
	if (data->tokens[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(data->tokens[1]);
	}

	len = _strlen(data->argv[0]) + _strlen(data->tokens[0]);
	len += _strlen(line) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(line);
		return (NULL);
	}

	error = strcat_cd_error(data, msg, error, line);

	free(line);

	return (error);
}


/**
 * strcat_cd_error - function entry-point
 *
 * Description: concatenates message for cd_error
 * @data: shell data structure
 * @msg: message to print
 * @error: error message
 * @lines: counter lines
 * Return: error message
 */

char *strcat_cd_error(data_t *data, char *msg, char *error, char *lines)
{
	char *flag;

	_strcpy(error, data->argv[0]);
	_strcat(error, ": ");
	_strcat(error, lines);
	_strcat(error, ": ");
	_strcat(error, data->tokens[0]);
	_strcat(error, msg);
	if (data->tokens[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = data->tokens[1][1];
		flag[2] = '\0';
		_strcat(error, flag);
		free(flag);
	}
	else
	{
		_strcat(error, data->tokens[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}


/**
 * error_404 - function entry-point
 *
 * Description: generic error message (command not found)
 * @data: shell data structure
 * Return: error message
 */

char *error_404(data_t *data)
{
	int len;
	char *error;
	char *lines;

	lines = _itoa(data->counter);
	len = _strlen(data->argv[0]) + _strlen(lines);
	len += _strlen(data->tokens[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(lines);
	return (error);
}


/**
 * exit_error - function entry-point
 *
 * Description: generic error message for exit
 * @data: shell data structure
 * Return: error message
 */

char *exit_error(data_t *data)
{
	int len;
	char *error;
	char *str;

	str = _itoa(data->counter);
	len = _strlen(data->argv[0]) + _strlen(str);
	len += _strlen(data->tokens[0]) + _strlen(data->tokens[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(error, data->argv[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, data->tokens[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, data->tokens[1]);
	_strcat(error, "\n\0");
	free(str);

	return (error);
}
