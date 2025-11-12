#include "get_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define READ_CHUNK 1024

/**
 * grow - Safely grow a dynamic buffer
 * @buf: address of pointer to current buffer (may be NULL)
 * @cap: address of current capacity in bytes
 * @need: minimum required capacity
 *
 * Return: 0 on success, -1 on failure.
 */
static int grow(char **buf, size_t *cap, size_t need)
{
	size_t ncap;
	char *tmp;

	if (*cap >= need)
		return (0);

	ncap = (*cap == 0) ? 64 : *cap;
	while (ncap < need)
		ncap *= 2;

	tmp = realloc(*buf, ncap);
	if (tmp == NULL)
		return (-1);

	*buf = tmp;
	*cap = ncap;
	return (0);
}

/**
 * get_line - Read one line from fd using a static read buffer
 * @fd: file descriptor to read from
 *
 * Description:
 * Uses a static buffer to minimize read(2) calls. Each call returns the next
 * line without the trailing newline. On EOF (and no characters read), returns
 * NULL. The caller must free the returned pointer.
 *
 * Return: malloc'ed string on success, or NULL on EOF/error.
 */
char *get_line(int fd)
{
	static char sbuf[READ_CHUNK];
	static ssize_t sidx;
	static ssize_t slen;

	char *line = NULL;
	size_t llen = 0, lcap = 0;

	for (;;)
	{
		char c;

		/* Refill the static buffer if empty */
		if (sidx >= slen)
		{
			slen = read(fd, sbuf, READ_CHUNK);
			if (slen <= 0)
			{
				if (llen > 0) /* return last partial line */
				{
					if (grow(&line, &lcap, llen + 1) == -1)
					{ free(line); return (NULL); }
					line[llen] = '\0';
					return (line);
				}
				free(line);
				return (NULL); /* EOF or error with no data */
			}
			sidx = 0;
		}

		/* Consume from the static buffer */
		c = sbuf[sidx++];

		/* Ensure space for next char + terminator */
		if (grow(&line, &lcap, llen + 2) == -1)
		{ free(line); return (NULL); }

		if (c == '\n')
		{
			line[llen] = '\0';
			return (line);
		}

		line[llen++] = c;
	}
}
