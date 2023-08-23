#include "main.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * _line - function entry-point
 *
 * Description: assigns the line var for get_line
 * @line: input string
 * @buffer: str that has been called to line
 * @line_size: size of line
 * @buf_size: size of buffer
 */

void _line(char **line, size_t *line_size, char *buffer, size_t buf_size)
{

	if (*line == NULL)
	{
		if  (buf_size > BUFSIZE)
			*line_size = buf_size;

		else
			*line_size = BUFSIZE;
		*line = buffer;
	}
	else if (*line_size < buf_size)
	{
		if (buf_size > BUFSIZE)
			*line_size = buf_size;
		else
			*line_size = BUFSIZE;
		*line = buffer;
	}
	else
	{
		_strcpy(*line, buffer);
		free(buffer);
	}
}


/**
 * _getline - function entry-point
 *
 * Description: reads input from stream
 * @line: input string
 * @line_size: size of line
 * @stream: stream to read from
 * Return: number of bytes
 */

ssize_t _getline(char **line, size_t *line_size, FILE *stream)
{
	int i;
	static ssize_t buf_size;
	ssize_t bufSize;
	char *buffer;
	char t = 'z';

	if (buf_size == 0)
		fflush(stream);
	else
		return (-1);
	buf_size = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && buf_size == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && buf_size != 0)
		{
			buf_size++;
			break;
		}
		if (buf_size >= BUFSIZE)
			buffer = _realloc(buffer, buf_size, buf_size + 1);
		buffer[buf_size] = t;
		buf_size++;
	}
	buffer[buf_size] = '\0';
	_line(line, line_size, buffer, buf_size);
	bufSize = buf_size;
	if (i != 0)
		buf_size = 0;
	return (bufSize);
}


/**
 * read_line - function entry-point
 *
 * Description: reads input
 * @i: return value of getline()
 * Return: string
 */
char *read_line(int *i)
{
	char *input = NULL;
	size_t buf_size = 0;

	*i = _getline(&input, &buf_size, stdin);

	return (input);
}
