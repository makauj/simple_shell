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
#include <ctype.h>
#include <limits.h>
/**
 * struct bin - definition of bin
 * @dir: directory
 * @next: next
 *
 * Description: something about bin
 */
typedef struct bin
{
	char *dir;
	struct bin *next;
} bin;


void free_node(bin *head);
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
char *_strtok(char *str, const char *delim);
int _strtol(const char *str, int *value);
char *_strchr(const char *str, int c);
int _builtins(void);
void my_exit(char **args);
void my_cd(char **args);


#define PROMPT "#C is fun$ "
#define BUFFER_SIZE 1024
#define MAX_ARGS 100
#define PATH_MAX 4096
extern char **environ; /* pass environment variables to execve */
/**
 * struct builtin - builtin
 * @name: name
 * @func: function
 *
 * Description: get builtins initiated
 */
struct builtin
{
	char *name;
	void (*func)(char **args);
};

/**
 * struct builtin - builtin
 * builtins - name builtin functions
 * @exit: custom name for my_exit function
 * @cd: custom name for my_cd function
 *
 * Description: Initializes an array of builtin structures
 */
struct builtin builtins[] = {
	{"exit", my_exit},
	{"cd", my_cd}
};

const size_t num_builtins = sizeof(builtins) / sizeof(builtins[0]);

#endif /* __MAIN_H__ */
