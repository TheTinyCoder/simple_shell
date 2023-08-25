#include "main.h"
#include <stdlib.h>

/**
 * handle_comment - function entry-point
 *
 * Description: removes comments from the input
 * @s: string
 * Return: string with no comments
 */

char *handle_comment(char *s)
{
	int i, j;

	j = 0;
	for (i = 0; s[i]; i++)
	{
		if (s[i] == '#')
		{
			if (i == 0)
			{
				free(s);
				return (NULL);
			}

			if (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == ';')
				j = i;
		}
	}

	if (j != 0)
	{
		s = _realloc(s, i, j + 1);
		s[j] = '\0';
	}

	return (s);
}
