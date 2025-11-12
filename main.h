#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define READ_SIZE 1024

int is_blank(const char *s);
char *trim_spaces(char *s);
char *_strdup(const char *s);
char *_getenv(const char *name);
int execute_command(char *line, char *prog_name, int cmd_count);
char *find_path(char *command);
char *get_line(int fd);

extern char **environ;

#endif /* MAIN_H */
