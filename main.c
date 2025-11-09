#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * is_blank - checks if a line is empty or only spaces/tabs
 * @s: string to check
 *
 * Return: 1 if blank, 0 otherwise
 */
int is_blank(const char *s)
{
	int i;

	if (s == NULL)
		return (1);

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
	}
	return (1);
}

/**
 * execute_command - forks and executes a command
 * @line: command to execute (full path)
 *
 * Return: Nothing
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		if (execve(line, argv, NULL) == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main - simple UNIX command interpreter (simple shell 0.1)
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (is_blank(line))
			continue;

		if (strcmp(line, "exit") == 0)
			break;

		execute_command(line);
	}

	free(line);
	return (0);
}
