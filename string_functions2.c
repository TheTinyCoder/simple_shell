#include "main.h"
#include <stdio.h>

/**
 * _strtok - function entry-point
 *
 * Description: splits a string by delimiter.
 * @str: string.
 * @delim: delimiter.
 * Return: split string.
 */
char *_strtok(char *str, char *delim)
{
	char *start;
	unsigned int i, bool;
	static char *split_string, *end;


	if (str != NULL)
	{
		if (strcmp_to_delim(str, delim))
			return (NULL);
		split_string = str;
		i = _strlen(str);
		end = &str[i];
	}
	start = split_string;
	if (start == end)
		return (NULL);

	for (bool = 0; *split_string; split_string++)
	{
		if (split_string != start)
			if (*split_string && *(split_string - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*split_string == delim[i])
			{
				*split_string = '\0';
				if (split_string == start)
					start++;
				break;
			}
		}
		if (bool == 0 && *split_string)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (start);
}


/**
 * _isdigit - function entrypoint
 *
 * Description: checks if each charater of string is digit 0 - 9
 * @s: string
 * Return: 1 if all are digits, 0 otherwise
 */

int _isdigit(char *s)
{
	int i = 0;

	for (; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}


/**
 * strcmp_to_delim - compare characters of string to delimeter
 * @str: string.
 * @delim: delimiter.
 * Return: 1 if are equals, 0 if not.
 */
int strcmp_to_delim(char *str, char *delim)
{
	int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
