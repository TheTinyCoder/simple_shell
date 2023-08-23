#include "main.h"
#include <stdlib.h>

/**
 * cmpenv - function entry-point
 *
 * Description: compares env variable name to name passed.
 * @env_name: environment variable name
 * @name: name passed
 * Return: 0 if not equal
 */

int cmpenv(const char *env_name, const char *name)
{
	int i;

	for (i = 0; env_name[i] != '='; i++)
	{
		if (env_name[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}


/**
 * cpyinfo - function entry-point
 *
 * Description: copies info (creates a new env/alias)
 * @name: name (env/alias)
 * @value: value (env/alias)
 * Return: newly created env or alias.
 */
char *cpyinfo(char *name, char *value)
{
	char *new;
	int name_len, value_len, len;

	name_len = _strlen(name);
	value_len = _strlen(value);
	len = name_len + value_len + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}
