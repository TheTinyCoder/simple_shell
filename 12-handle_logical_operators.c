#include "main.h"

/**
 * swap_non_ops - function entry-point
 *
 * Description: swaps non-logical | and & for non-printed chars
 * @s: string
 * @bool: integer for swap type (0 or otherwise)
 * Return: swapped string
 */

char *swap_non_ops(char *s, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; s[i]; i++)
		{
			if (s[i] == '|')
			{
				if (s[i + 1] != '|')
					s[i] = 16;
				else
					i++;
			}

			if (s[i] == '&')
			{
				if (s[i + 1] != '&')
					s[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; s[i]; i++)
		{
			s[i] = (s[i] == 16 ? '|' : s[i]);
			s[i] = (s[i] == 12 ? '&' : s[i]);
		}
	}
	return (s);
}

