#include "main.h"

/**
 * main - simple UNIX command interpreter (simple shell 0.2)
 *
 * Return: Always 0 (Success)
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *cmd;
	int cmd_count = 0;
	int last_status = 0;

	(void)ac;

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

		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		cmd = trim_spaces(line);

		if (is_blank(cmd))
			continue;

		cmd_count++;

		if (strcmp(cmd, "exit") == 0)
			break;
		if (strcmp(cmd, "env") == 0)
		{
			int i;
			for (i = 0; environ[i] != NULL; i++)
				printf("%s\n", environ[i]);
			continue;
		}

		last_status = execute_command(cmd, av[0], cmd_count);
	}

	free(line);
	return (last_status);
}
