#include "main.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * is_current_dir - function entry-point
 *
 * Description: checks if path is in current directory.
 * @path: pointer to path.
 * @i: integer
 * Return: 1 if path is in current dir, 0 otherwise.
 */

int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
		*i += 1;

	if (path[*i])
		*i += 1;

	return (0);
}


/**
 * _which - function entry-point
 *
 * Description: finds a command
 * @command: command name
 * @_environ: environment variable
 * Return: location of the command.
 */

char *_which(char *command, char **_environ)
{
	char *path, *pathPtr, *token_path, *dir;
	int dir_len, command_len, i;
	struct stat st;

	path = get_env("PATH", _environ);
	if (path)
	{
		pathPtr = _strdup(path);
		command_len = _strlen(command);
		token_path = _strtok(pathPtr, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(command, &st) == 0)
					return (command);
			dir_len = _strlen(token_path);
			dir = malloc(dir_len + command_len + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, command);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(pathPtr);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(pathPtr);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}


/**
 * check_permissions - function entry-point
 *
 * Description: checks if user has permissions to access directory
 * @directory: directory to check
 * @data: shell data structure
 * Return: 1 if error, 0 if success
 */

int check_permissions(char *directory, data_t *data)
{
	if (directory == NULL)
	{
		get_error(data, 127);
		return (1);
	}

	if (_strcmp(data->tokens[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			get_error(data, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(data->tokens[0], X_OK) == -1)
		{
			get_error(data, 126);
			return (1);
		}
	}

	return (0);
}

