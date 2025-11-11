#include "main.h"

/**
 * is_blank - check if string is only spaces or tabs
 * @s: string to check
 *
 * Return: 1 if blank, 0 otherwise
 */
int is_blank(const char *s)
{
	int i = 0;

	if (s == NULL)
		return (1);

	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}

	return (1);
}

/**
 * trim_spaces - remove leading and trailing spaces/tabs
 * @s: string to trim
 *
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *s)
{
	char *end;

	if (s == NULL)
		return (NULL);

	while (*s == ' ' || *s == '\t')
		s++;

	if (*s == '\0')
		return (s);

	end = s + strlen(s) - 1;
	while (end > s && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';

	return (s);
}

