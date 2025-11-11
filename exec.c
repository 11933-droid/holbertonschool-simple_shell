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
 * @prog_name: name of our shell program (argv[0])
 * @cmd_count: command number (for error messages)
 *
 * Return: exit status of the executed command
 */
int execute_command(char *line, char *prog_name, int cmd_count)
{
	char *argv[MAX_ARGS];
	char *cmd_path;
	pid_t pid;
	int status = 0, argc;

	argc = build_argv(line, argv, MAX_ARGS);
	if (argc == 0 || argv[0] == NULL)
		return (0);

	cmd_path = find_path(argv[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_count, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
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
		if (waitpid(pid, &status, 0) == -1)
		{
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
