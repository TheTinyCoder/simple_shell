#include "main.h"
#include <stdlib.h>

/**
 * _setenv - function entry-point
 *
 * Description: sets an environment variable
 * @env_name: environment variable name
 * @env_value: environment variable value
 * @data: data structure (environ)
 * Return: void
 */

void _setenv(char *env_name, char *env_value, data_t *data)
{
	int i;
	char *env, *name;

	for (i = 0; data->_environ[i]; i++)
	{
		env = _strdup(data->_environ[i]);
		name = _strtok(env, "=");
		if (_strcmp(name, env_name) == 0)
		{
			free(data->_environ[i]);
			data->_environ[i] = cpyinfo(name, env_value);
			free(env);
			return;
		}
		free(env);
	}

	data->_environ = _reallocdp(data->_environ, i, sizeof(char *) * (i + 2));
	data->_environ[i] = cpyinfo(env_name, env_value);
	data->_environ[i + 1] = NULL;
}


/**
 * cmp_setenv - function entry-point
 *
 * Description: compares env var name to name passed.
 * @data: shell data structure
 * Return: 1 on success.
 */

int cmp_setenv(data_t *data)
{

	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
	{
		get_error(data, -1);
		return (1);
	}

	_setenv(data->tokens[1], data->tokens[2], data);

	return (1);
}


/**
 * _unsetenv - function entry-point
 *
 * Description: removes an environment variable
 * @data: shell data structure
 * Return: 1 on success.
 */
int _unsetenv(data_t *data)
{
	char **realloc_env;
	char *env, *name;
	int i, j, k;

	if (data->tokens[1] == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->_environ[i]; i++)
	{
		env = _strdup(data->_environ[i]);
		name = _strtok(env, "=");
		if (_strcmp(name, data->tokens[1]) == 0)
		{
			k = i;
		}
		free(env);
	}
	if (k == -1)
	{
		get_error(data, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = data->_environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(data->_environ[k]);
	free(data->_environ);
	data->_environ = realloc_env;
	return (1);
}
