#include "main.h"
#include <stdlib.h>

/**
 * _strlen - function entry-point
 *
 * Description: returns the length of a string
 * @s: pointer to array
 * Return: int
 */

int _strlen(char *s)
{
	int x = 0;

	while (*(s + x) != '\0')
	{
		x++;
	}

	return (x);
}


/**
 * _strspn -  function entry-point
 *
 * Description: 'gets the length of a prefix substring'
 * @s: pointer to string
 * @accept: pointer to string
 * Return: number of bytes in s which consist of bytes from accept
 */

int _strspn(char *s, char *accept)
{
	unsigned int i, j, k, l = 0, m = 0;

	for (k = 0; accept[k] != '\0'; k++)
		;
	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0;; j++)
		{
			if (s[i] == accept[j])
				break;
			if (s[i] != accept[j] && j == k - 1)
			{
				l = 1;
				m = i;
			}
		}
		if (l > 0)
			break;
	}
	return (m);
}


/**
 * *_strdup - function entry-point
 *
 * Description:  returns a pointer to a new mem allocation with copy of str
 * @str: pointer to string
 * Return: NULL if size is 0, pointer to array otherwise
 */

char *_strdup(char *str)
{
	unsigned int i = 0, j;
	char *a;

	if (str == NULL)
		return (NULL);

	for (; str[i] != '\0'; i++)
		;
	i++;
	a = (char *)malloc(sizeof(char) * i);

	if (a == NULL)
		return (NULL);
	for (j = 0; j < i; j++)
	{
		a[j] = str[j];
	}
	return (a);
}


/**
 * rev_string - function entry-point
 *
 * Description: reverses a string
 * @s: pointer to string (char array)
 * Return: void
 */

void rev_string(char *s)
{
	int x = 0, y = 0;
	char temp;

	while (*(s + x) != '\0')
	{
		x++;
	}

	for (x--; x > y; x--)
	{
		temp = *(s + y);
		*(s + y) = *(s + x);
		*(s + x) = temp;
		y++;
	}
}
