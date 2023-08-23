#include "main.h"
#include <limits.h>
#include <stdlib.h>

/**
 * _exitsh - function entry-point
 *
 * Description: exits the shell
 * @data: shell data structure
 * Return: 0 on success.
 */

int _exitsh(data_t *data)
{
	unsigned int status;
	int is_digit, str_len, z;

	if (data->tokens[1] != NULL)
	{
		status = _atoi(data->tokens[1]);
		is_digit = _isdigit(data->tokens[1]);
		str_len = _strlen(data->tokens[1]);
		z = status > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || z)
		{
			get_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (status % 256);
	}
	return (0);
}
