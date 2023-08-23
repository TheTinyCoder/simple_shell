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
 * _getlen - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int _getlen(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}


/**
 * _atoi - function entry-point
 *
 * Description: converts a string to int
 * @s: string.
 * Return: integer.
 */

int _atoi(char *s)
{
	unsigned int count = 0, size = 0, i = 0, j = 1, k = 1, l;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			j *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				k *= 10;
			size++;
		}
		count++;
	}

	for (l = count - size; l < count; l++)
	{
		i = i + ((*(s + l) - 48) * k);
		k /= 10;
	}
	return (i * j);
}
