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

char *_strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';

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
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';

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
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
	{
		if (*(s + i) == c)
			return (s + i);
	}
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}


/**
 * _strcmp -  function entry-point
 *
 * Description: 'compares two strings'
 * @s1: string
 * @s2: string
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	for (; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
