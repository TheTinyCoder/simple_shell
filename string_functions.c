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
	int x, y;

	for (x = 0; dest[x] != '\0'; x++)
		;

	for (y = 0; src[y] != '\0'; y++)
		dest[x] = src[y], x++;
	dest[x] = '\0';

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
	size_t x;

	for (x = 0; src[x] != '\0'; x++)
		dest[x] = src[x];
	dest[x] = '\0';

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
	unsigned int x = 0;

	for (; s[x] != '\0'; x++)
	{
		if (s[x] == c)
			return (s + x);
	}
	if (s[x] == c)
		return (s + x);
	return (NULL);
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
	int x = 0;

	for (; s1[x] == s2[x] && s1[x]; x++)
		;

	if (s1[x] > s2[x])
		return (1);
	if (s1[x] < s2[x])
		return (-1);
	return (0);
}
