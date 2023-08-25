#include "main.h"
#include <stdlib.h>

/**
 * _strlen - function entry-point
 *
 * Description: returns the length of a string
 * @s: pointer to array
 * Return: int
 */

int _strlen(const char *s)
{
	int x = 0;

	while (*(s + x) != '\0')
		x++;

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
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}


/**
 * *_strdup - function entry-point
 *
 * Description:  returns a pointer to a new mem allocation with copy of str
 * @str: pointer to string
 * Return: NULL if size is 0, pointer to array otherwise
 */

char *_strdup(const char *str)
{
	char *new;
	size_t len;

	len = _strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, str, len + 1);
	
	return (new);
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
		x++;

	for (x--; x > y; x--)
	{
		temp = *(s + y);
		*(s + y) = *(s + x);
		*(s + x) = temp;
		y++;
	}
}
