#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - Forks and executes a command
 * @line: Command to execute (full path)
 *
 * Return: Nothing
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		if (execve(line, argv, NULL) == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}
}

/**
 * main - Simple UNIX command interpreter
 *
 * Description: Displays a prompt, waits for the user to enter a command,
 * executes it, and repeats the process until EOF (Ctrl+D) or "exit".
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
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		if (strcmp(line, "exit") == 0)
			break;

		execute_command(line);
	}

	free(line);
	return (0);
}
