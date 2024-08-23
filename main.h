#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
typedef struct bin
{
	char *dir;
	struct bin *next;
} bin;
char *_strdup(char *str);
char *_getenv(char *name);
void free_node(bin *head);
void print_environ();
 int _strcmp(char *s1, char *s2);
int _unsetenv(char *name);
int _setenv(char *name, char *value);
int _strncmp(char *str1, char *str2, ssize_t n);
char *search_command(char *command);
bin *create_node(void);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int print_string(char *str);
int _putchar(char c);
int _strlen(char *s);
void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
void handle_error(const char *msg);
char *command_path(const char *command);
int run_command(char *path, char **argv, char **envp);
#define PROMPT "#C is fun$ "
#define BUFFER_SIZE 1024
#define MAX_ARGS 100

extern char **environ; /* pass environment variables to execve */

#endif /* __MAIN_H__ */
