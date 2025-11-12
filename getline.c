#include "main.h"

/* static buffer for _getline */
static char g_buf[READ_SIZE];
static ssize_t g_start;
static ssize_t g_end;

/**
 * grow_line - ensure capacity for line buffer
 * @lineptr: pointer to string buffer
 * @n: pointer to capacity
 * @need: number of bytes that need to fit (including '\0')
 *
 * Return: 0 on success, -1 on failure
 */
static int grow_line(char **lineptr, size_t *n, size_t need)
{
	char *tmp;
	size_t new_cap;

	if (*lineptr == NULL || *n == 0)
	{
		*n = (*n == 0) ? 128 : *n;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}

	while (need > *n)
	{
		new_cap = (*n) * 2;
		tmp = realloc(*lineptr, new_cap);
		if (!tmp)
			return (-1);
		*lineptr = tmp;
		*n = new_cap;
	}
	return (0);
}

/**
 * refill_buf - refill static buffer from STDIN
 *
 * Return: number of bytes refilled (>0) or 0/negative on EOF/error
 */
static ssize_t refill_buf(void)
{
	ssize_t r;

	r = read(STDIN_FILENO, g_buf, READ_SIZE);
	if (r > 0)
	{
		g_start = 0;
		g_end = r;
	}
	return (r);
}

/**
 * pull_char - get next char from static buffer, refilling if needed
 * @pc: out param for char
 *
 * Return: 1 if a char was produced, 0 on EOF, -1 on error
 */
static int pull_char(char *pc)
{
	if (g_start >= g_end)
	{
		ssize_t r = refill_buf();

		if (r <= 0)
			return (r == 0 ? 0 : -1);
	}

	*pc = g_buf[g_start++];
	return (1);
}

/**
 * _getline - read one line from STDIN using a static buffer
 * @lineptr: pointer to allocated buffer (will grow as needed)
 * @n: current capacity of *lineptr (in/out)
 *
 * Return: number of bytes read (including '\n' if present), or -1 on EOF/error
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	ssize_t out = 0;
	char *line;
	char c;
	int got;

	if (!lineptr || !n)
		return (-1);

	if (grow_line(lineptr, n, 1) == -1)
		return (-1);

	line = *lineptr;

	while (1)
	{
		got = pull_char(&c);
		if (got == 0 && out == 0)
			return (-1);
		if (got == 0) /* EOF after some bytes */
		{
			if (grow_line(&line, n, (size_t)out + 1) == -1)
				return (-1);
			*lineptr = line;
			line[out] = '\0';
			return (out);
		}
		if (got == -1)
			return (-1);

		if (grow_line(&line, n, (size_t)out + 2) == -1)
			return (-1);

		line[out++] = c;
		if (c == '\n')
		{
			line[out] = '\0';
			*lineptr = line;
			return (out);
		}
	}
}
