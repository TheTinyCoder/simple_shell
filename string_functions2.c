#include "main.h"
#include <stdlib.h>

/**
 * _itoa - function entry-point
 *
 * Description: converts int to string.
 * @n: type int number
 * Return: string
 */

char *_itoa(int n)
{
	unsigned int p;
	int len = _getlen(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (n < 0)
	{
		p = n * -1;
		buffer[0] = '-';
	}
	else
	{
		p = n;
	}

	len--;
	do {
		*(buffer + len) = (p % 10) + '0';
		p = p / 10;
		len--;
	}
	while (p > 0)
		;
	return (buffer);
}


/**
 * _isdigit - function entrypoint
 *
 * Description: checks if each charater of string is digit 0 - 9
 * @s: string
 * Return: 1 if all are digits, 0 otherwise
 */

int _isdigit(const char *s)
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
 * strcmp_to_delim - function entry-point
 *
 * Description: compare characters of string to delimeter
 * @str: string.
 * @delim: delimiter.
 * Return: 1 if are equals, 0 if not.
 */

int strcmp_to_delim(char str[], const char *delim)
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
