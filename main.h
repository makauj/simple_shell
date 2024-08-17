#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
void handle_error(const char *msg);

#define PROMPT "#C is fun$ "
#define BUFFER_SIZE 1024
#define MAX_ARGS 100

#endif /* __MAIN_H__ */
