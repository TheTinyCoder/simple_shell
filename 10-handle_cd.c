#include "main.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * cd_parent - function entry-point
 *
 * Description: changes directory to parent directory
 * @data: shell data structure
 * Return: void
 */
void cd_parent(data_t *data)
{
	char pwd[PATH_MAX];
	char *directory, *dp_pwd, *strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	dp_pwd = _strdup(pwd);
	_setenv("OLDPWD", dp_pwd, data);
	directory = data->tokens[1];
	if (_strcmp(".", directory) == 0)
	{
		_setenv("PWD", dp_pwd, data);
		free(dp_pwd);
		return;
	}
	if (_strcmp("/", dp_pwd) == 0)
	{
		free(dp_pwd);
		return;
	}
	strtok_pwd = dp_pwd;
	rev_string(strtok_pwd);
	strtok_pwd = _strtok(strtok_pwd, "/");
	if (strtok_pwd != NULL)
	{
		strtok_pwd = _strtok(NULL, "\0");

		if (strtok_pwd != NULL)
			rev_string(strtok_pwd);
	}
	if (strtok_pwd != NULL)
	{
		chdir(strtok_pwd);
		_setenv("PWD", strtok_pwd, data);
	}
	else
	{
		chdir("/");
		_setenv("PWD", "/", data);
	}
	data->status = 0;
	free(dp_pwd);
}


/**
 * cd_dir - function entry-point
 *
 * Description: changes to directory specified by user
 * @data: shell data structure
 * Return: void
 */
void cd_dir(data_t *data)
{
	char pwd[PATH_MAX];
	char *directory, *dp_pwd, *dp_dir;

	getcwd(pwd, sizeof(pwd));

	directory = data->tokens[1];
	if (chdir(directory) == -1)
	{
		get_error(data, 2);
		return;
	}

	dp_pwd = _strdup(pwd);
	_setenv("OLDPWD", dp_pwd, data);

	dp_dir = _strdup(directory);
	_setenv("PWD", dp_dir, data);

	free(dp_pwd);
	free(dp_dir);

	data->status = 0;

	chdir(directory);
}


/**
 * cd_back - function entry-point
 *
 * Description: changes directory to previous
 * @data: shell data structure
 * Return: void
 */

void cd_back(data_t *data)
{
	char pwd[PATH_MAX];
	char *_pwd, *oldpwd, *dp_pwd, *dp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	dp_pwd = _strdup(pwd);

	oldpwd = get_env("OLDPWD", data->_environ);

	if (oldpwd == NULL)
		dp_oldpwd = dp_pwd;
	else
		dp_oldpwd = _strdup(oldpwd);

	_setenv("OLDPWD", dp_pwd, data);

	if (chdir(dp_oldpwd) == -1)
		_setenv("PWD", dp_pwd, data);
	else
		_setenv("PWD", dp_oldpwd, data);

	_pwd = get_env("PWD", data->_environ);

	write(STDOUT_FILENO, _pwd, _strlen(_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(dp_pwd);
	if (oldpwd)
		free(dp_oldpwd);

	data->status = 0;

	chdir(_pwd);
}


/**
 * cd_home - function entry-point
 *
 * Description: changes directory to home
 * @data: shell data structure
 * Return: void
 */
void cd_home(data_t *data)
{
	char *_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	_pwd = _strdup(pwd);

	home = get_env("HOME", data->_environ);

	if (home == NULL)
	{
		_setenv("OLDPWD", _pwd, data);
		free(_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data, 2);
		free(_pwd);
		return;
	}

	_setenv("OLDPWD", _pwd, data);
	_setenv("PWD", home, data);
	free(_pwd);
	data->status = 0;
}


/**
 * cd_current - function entry-point
 *
 * Description: changes current dir
 * @data: shell data structure
 * Return: 1 on success
 */

int cd_current(data_t *data)
{
	char *directory;
	int is_home, is_home1, is_dash;

	directory = data->tokens[1];

	if (directory != NULL)
	{
		is_home = _strcmp("$HOME", directory);
		is_home1 = _strcmp("~", directory);
		is_dash = _strcmp("--", directory);
	}

	if (directory == NULL || !is_home || !is_home1 || !is_dash)
	{
		cd_home(data);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_back(data);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_parent(data);
		return (1);
	}

	cd_dir(data);

	return (1);
}
