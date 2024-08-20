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


void free_node(bin *head);
char *search_command(char *command);
bin *create_node(void);
char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);
char *get_command(void);
int print_string(char *str);
int _putchar(char c);
int _strlen(char *s);
void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
void handle_error(const char *msg);
char *command_path(const char *command);

#define PROMPT "#C is fun$ "
#define BUFFER_SIZE 1024
#define MAX_ARGS 100

extern char **environ; /* pass environment variables to execve */

#endif /* __MAIN_H__ */
