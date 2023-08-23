#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * _env - function entry-point
 *
 * Description: prints an evironment variable
 * @data: shell data structure
 * Return: 1 on success.
 */

int _env(data_t *data)
{
	int i, j;

	for (i = 0; data->_environ[i]; i++)
	{

		for (j = 0; data->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, data->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;

	return (1);
}


/**
 * get_env - function entry-point
 *
 * Description: gets an environment variable
 * @env_name: environment variable name
 * @_environ: environment variable
 * Return: environment variable or NULL
 */

char *get_env(const char *env_name, char **_environ)
{
	char *envPtr;
	int i, j;

	envPtr = NULL;
	j = 0;
	for (i = 0; _environ[i]; i++)
	{
		j = cmpenv(_environ[i], env_name);
		if (j)
		{
			envPtr = _environ[i];
			break;
		}
	}

	return (envPtr + j);
}
