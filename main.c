#include "main.h"

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
 * trim_spaces - removes leading and trailing spaces/tabs from a string
 * @s: string to trim
 *
 * Return: pointer to the trimmed string
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
 * execute_command - forks and executes a command with arguments
 * @line: full command line string
 *
 * Return: Nothing
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *argv[100];
	char *token;
	int i = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		token = strtok(line, " \t");
		while (token != NULL && i < 99)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;

		if (execve(argv[0], argv, environ) == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main - simple UNIX command interpreter (simple shell 0.2)
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *cmd;

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
		cmd = trim_spaces(line);

		if (is_blank(cmd))
			continue;

		if (strcmp(cmd, "exit") == 0)
			break;

		execute_command(cmd);
	}

	free(line);
	return (0);
}
