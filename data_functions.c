#include "main.h"
#include <stdlib.h>
#include <unistd.h>
/**
 * set_data - function entry-point
 *
 * Description: initializes shell data structure
 * @data: shell data structure
 * @argv: argument vector
 * Return: void
 */

void set_data(data_t *data, char **argv)
{
	unsigned int i;

	data->argv = argv;
	data->user_input = NULL;
	data->tokens = NULL;
	data->status = 0;
	data->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->_environ[i] = _strdup(environ[i]);
	}

	data->_environ[i] = NULL;
	data->pid = _itoa(getpid());
}


/**
 * free_data - function entry-point
 *
 * Descritpion: frees data structure
 * @data: shell data structure
 * Return: void
 */

void free_data(data_t *data)
{
	unsigned int i;

	for (i = 0; data->_environ[i]; i++)
	{
		free(data->_environ[i]);
	}

	free(data->_environ);
	free(data->pid);
}

