#include "main.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * get_sigint - function entry-point
 *
 * Description: handle 'crtl + c' call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * get_builtin - function entry-point
 *
 * Description: pairs builtin commands with functions
 * @command: command
 * Return: pointer to function for the builtin command
 */

int (*get_builtin(char *command))(data_t *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", _exitsh },
		{ "setenv", cmp_setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_current },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, command) == 0)
			break;
	}

	return (builtin[i].f);
}


/**
 * loop_shell_prompt - function entry-point
 *
 * Description: displays prompt after command execution or if argc is 1
 * @data: shell data structure
 * Return: void
 */

void loop_shell_prompt(data_t *data)
{
	int loop, i;
	char *s;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		s = _readline(&i);
		if (i != -1)
		{
			s = handle_comment(s);
			if (s == NULL)
				continue;

			if (check_syntax(data, s) == 1)
			{
				data->status = 2;
				free(s);
				continue;
			}
			s = replace_var(s, data);
			loop = split_command_lines(data, s);
			data->counter += 1;
			free(s);
		}
		else
		{
			loop = 0;
			free(s);
		}
	}
}


/**
 * main - Entry point
 *
 * Description: runs simple shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success.
 */

int main(int argc, char **argv)
{
	data_t data;
	(void) argc;

	signal(SIGINT, get_sigint);
	set_data(&data, argv);
	loop_shell_prompt(&data);
	free_data(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
}
