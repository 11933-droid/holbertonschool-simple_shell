#include "main.h"

/**
 * check_access - check if command path is valid
 * @full_path: full path to check
 * Return: 1 if valid, 0 otherwise
 */
int check_access(char *full_path)
{
	if (access(full_path, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * find_path - search for a command in PATH or as given
 * @cmd: command name (e.g. "ls" or "/bin/ls")
 *
 * Return: malloc'ed string with full path if found, or NULL if not found
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir;
	char *full_path;
	int len;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	if (*path_env == '\0')
	{
		if (access(cmd, X_OK) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + 1 + strlen(cmd) + 1;
		full_path = malloc(len);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
