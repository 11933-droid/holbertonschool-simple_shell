#include "main.h"
#include <unistd.h>
#include <stdlib.h>

#define READ_SIZE 1024

/**
 * _getline - read one line from STDIN using a static buffer
 * @lineptr: pointer to allocated buffer
 * @n: current capacity of *lineptr (will grow)
 *
 * Return: number of bytes read (including '\n' if present), or -1 on EOF/error
 */

ssize_t _getline(char **lineptr, size_t *n)
{
	static char buf[READ_SIZE];
	static ssize_t start = 0, end = 0;

	ssize_t out_len = 0;
	char *line;

	if (!lineptr || !n)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}
	line = *lineptr;

	while (1)
	{
		if (start >= end)
		{
			ssize_t r = read(STDIN_FILENO, buf, READ_SIZE);
			if (r <= 0)
			{
				if (out_len == 0)
					return (-1);
				line[out_len] = '\0';
				return (out_len);
			}
			start = 0;
			end = r;
		}
		while (start < end)
		{
			char c = buf[start++];
			if ((size_t)(out_len + 1) >= *n)
			{
				size_t new_cap = (*n) * 2;
				char *tmp = realloc(line, new_cap);
				if (!tmp)
					return (-1);
				line = tmp;
				*lineptr = line;
				*n = new_cap;
			}
			line[out_len++] = c;

			if (c == '\n')
			{
				line[out_len] = '\0';
				return (out_len);
			}
		}
	}
}
