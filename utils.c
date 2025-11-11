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

/**
 * _strdup - duplicate a string using malloc
 * @s: string to copy
 *
 * Return: pointer to new string, or NULL on failure
 */
char *_strdup(const char *s)
{
	char *copy;
	size_t len;

	if (s == NULL)
		return (NULL);
	len = strlen(s) + 1;
	copy = malloc(len);
	if (copy == NULL)
		return (NULL);

	strcpy(copy, s);
	return (copy);
}

/**
 * _getenv - get the value of an environment variable
 * @name: variable name (e.g. "PATH")
 *
 * Return: pointer to value (inside environ) or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	if (name == NULL || *name == '\0')
		return (NULL);

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

