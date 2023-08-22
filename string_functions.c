#include "main.h"
#include <stdio.h>

/**
 * *_strcat -  function entry-point
 *
 * Description: 'concatenates two strings'
 * @dest: string
 * @src: string
 * Return: pointer to concatenated string
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (i >= 0)
	{
		if (dest[i] == '\0')
			break;
		i++;
	}

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	return (dest);
}


/**
 * _strcpy - function entry-point
 *
 * Description: copies 'src' string to 'dest'
 * @src: string; char array
 * @dest: string; char array
 * Return: pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int x = 0;

	while (x >= 0)
	{
		dest[x] = src[x];
		if (src[x] == '\0')
			break;
		x++;
	}

	return (dest);
}


/**
 * *_strchr -  function entry-point
 *
 * Description: 'locates a character in a string'
 * @s: pointer to string
 * @c: character
 * Return: pointer to first occurrence or null
 */

char *_strchr(char *s, char c)
{
	unsigned int i = 0, j = 0;

	for (;; i++)
	{
		if (s[i] == c)
		{
			j = i;
			break;
		}
		if (s[i] == '\0')
		{
			break;
		}
	}
	if (j == 0)
		return (NULL);
	return ((s + j));
}


/**
 * _strcmp -  function entry-point
 *
 * Description: 'compares two strings'
 * @s1: string
 * @s2: string
 * Return: integer
 */

int _strcmp(char *s1, char *s2)
{
	int i, j = 0;

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			j = s1[i] - s2[i];
			break;
		}
	}

	return (j);
}



