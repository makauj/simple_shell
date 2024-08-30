#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Define buffer size and delimiters */
#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

/* Function declarations for command execution*/
void display_prompt(void);
int read_input(char **buffer, size_t *bufsize);
char **split_line(char *line);
void execute_command(char **args);
void exec_command(char *command_path, char **args);
int handle_builtin_commands(char **args);

/* function prototypes for built_in commands */
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_cd(char **args);
void print_env(void);

/* Function prototype for path handling */
char *find_command(const char *command);

/* Function prototypes for env management */
void set_env(const char *name, const char *value);
void unset_env(const char *name);

/* Custom utility functions */
size_t custom_strlen(const char *str);
char *custom_strdup(const char *s);
int custom_strcmp(const char *s1, const char *s2);
int custom_strncmp(const char *s1, const char *s2, size_t n);
char *custom_strncpy(char *dest, const char *src, size_t n);
char *custom_strtok(char *str, const char *delim);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void concat_path(char *fp, const char *dir, const char *command);

extern char **environ;

#endif /* MAIN_H */
