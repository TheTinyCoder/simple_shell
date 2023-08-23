#include "main.h"
#include <unistd.h>

/**
 * help - function entry-point
 *
 * Description: help information for the builtin help
 * Return: void
 */

void help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * help_alias - function entry-point
 *
 * Description: help information for 'alias'
 * Return: void
 */

void help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * help_cd - function entry-point
 *
 * Description: help information for 'cd'
 * Return: void
 */

void help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * get_help - function entry-point
 *
 * Description: retrieves help messages according builtin
 * @data: shell data structure
 * Return: 0
*/

int get_help(data_t *data)
{

	if (data->tokens[1] == 0)
		help_general();
	else if (_strcmp(data->tokens[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(data->tokens[1], "env") == 0)
		help_env();
	else if (_strcmp(data->tokens[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(data->tokens[1], "help") == 0)
		help();
	else if (_strcmp(data->tokens[1], "exit") == 0)
		help_exit();
	else if (_strcmp(data->tokens[1], "cd") == 0)
		help_cd();
	else if (_strcmp(data->tokens[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, data->tokens[0],
		      _strlen(data->tokens[0]));

	data->status = 0;
	return (1);
}
