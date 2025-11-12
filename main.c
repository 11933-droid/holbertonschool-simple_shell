#include "main.h"

/**
 * print_env - prints current environment variables
 */
static void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_builtin - run builtin if any
 * @cmd: trimmed command string
 * @last_status: pointer to last status (unused here, just for symmetry)
 *
 * Return: 1 if builtin handled and continue loop,
 *         -1 if should exit shell,
 *         0 if not a builtin.
 */
static int handle_builtin(char *cmd, int *last_status)
{
	(void)last_status;

	if (strcmp(cmd, "exit") == 0)
		return (-1);

	if (strcmp(cmd, "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}

/**
 * main - simple UNIX command interpreter
 * @ac: argument count
 * @av: argument vector
 *
 * Return: last command exit status
 */
int main(int ac, char **av)
{
	char *line = NULL, *cmd;
	size_t cap = 0;
	ssize_t nread;
	int count = 0, last = 0, bi;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		nread = _getline(&line, &cap);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		cmd = trim_spaces(line);
		if (is_blank(cmd))
			continue;

		count++;
		bi = handle_builtin(cmd, &last);
		if (bi == -1)
			break;
		if (bi == 1)
			continue;

		last = execute_command(cmd, av[0], count);
	}

	free(line);
	return (last);
}
