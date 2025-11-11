#include "main.h"

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
