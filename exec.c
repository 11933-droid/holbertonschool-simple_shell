#include "main.h"

#define MAX_ARGS 100

/**
 * build_argv - tokenize a line into argv array
 * @line: input line (will be modified)
 * @argv: array to fill with tokens
 * @max: maximum number of elements in argv
 *
 * Return: number of arguments stored in argv
 */
static int build_argv(char *line, char **argv, int max)
{
	char *token;
	int i = 0;

	if (line == NULL || argv == NULL || max <= 0)
		return (0);

	token = strtok(line, " \t");
	while (token != NULL && i < max - 1)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (i);
}

/**
 * execute_command - fork and execute a command with arguments
 * @line: full command line (will be modified)
 *
 * Return: nothing
 */
void execute_command(char *line, char *prog_name, int cmd_count)
{
	char *argv[MAX_ARGS];
	char *cmd_path;
	pid_t pid;
	int status, argc;

	argc = build_argv(line, argv, MAX_ARGS);
	if (argc == 0 || argv[0] == NULL)
		return;

	cmd_path = find_path(argv[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, cmd_count, argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd_path, argv, environ) == -1)
		{
			perror("Error");
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}
