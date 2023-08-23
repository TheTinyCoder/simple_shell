#include "main.h"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute - function entry-point
 *
 * Description: executes command lines
 * @data: shell data structure
 * Return: 1 on success.
 */

int execute(data_t *data)
{
	pid_t pd, wpd;
	int state, exec;
	char *dir;
	(void) wpd;

	exec = is_executable(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(data->tokens[0], data->_environ);
		if (check_permissions(dir, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(data->tokens[0], data->_environ);
		else
			dir = data->tokens[0];
		execve(dir + exec, data->tokens, data->_environ);
	}
	else if (pd < 0)
	{
		perror(data->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	return (1);
}


/**
 * is_executable - function entry-point
 *
 * Description: checks if executable
 * @data: shell data structure
 * Return: 0 if not executable
 */

int is_executable(data_t *data)
{
	struct stat st;
	int i;
	char *s;

	s = data->tokens[0];
	for (i = 0; s[i]; i++)
	{
		if (s[i] == '.')
		{
			if (s[i + 1] == '.')
				return (0);
			if (s[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (s[i] == '/' && i != 0)
		{
			if (s[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(s + i, &st) == 0)
	{
		return (i);
	}
	get_error(data, 127);
	return (-1);
}
