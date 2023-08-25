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
	int x, y, bool;

	for (x = 0; s[x] != '\0'; x++)
	{
		bool = 1;
		for (y = 0; accept[y] != '\0'; y++)
		{
			if (s[x] == accept[y])
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (x);
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
	char *new_str;
	size_t length;

	length = _strlen(str);
	new_str = malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	_memcpy(new_str, str, length + 1);

	return (new_str);
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
	int count = 0, x, y;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (x = 0; x < (count - 1); x++)
	{
		for (y = x + 1; y > 0; y--)
		{
			temp = str[y];
			str[y] = str[y - 1];
			str[y - 1] = temp;
		}
	}
}
