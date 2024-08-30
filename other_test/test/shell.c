#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
/**
 * struct bin - linked list
 * @dir: directory
 * @next: next
 * Description: linked list
 */
typedef struct bin
{
    char *dir;
    struct bin *next;
} bin;

/* Define buffer size and delimiters */
#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

/* Function declarations for command execution */
void display_prompt(void);
int read_input(char **buffer, size_t *bufsize);
char **split_line(char *line);
void execute_command(char **args);
void exec_command(char *command_path, char **args);
int handle_builtin_commands(char **args);

/* Function prototypes for built-in commands */
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_cd(char **args);
void print_env(void);
void handle_echo(char **args);
void int_to_str(int value, char *str, size_t size);
char *_getenv(char *name);

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
int print_string(char *str);
int _strncmp(char *str1, char *str2, ssize_t n);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void concat_path(char *fp, const char *dir, const char *command);
char *no_whitespace(char *str);

/* Environment variable handling */
extern char **environ;

/**
 * display_prompt - Function to display the prompt
 */
void display_prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_input - Function to read input from stdin
 */
int read_input(char **buf, size_t *bufsize)
{
    ssize_t len = custom_getline(buf, bufsize, stdin);
    size_t len1 = custom_strlen(*buf);
    
    if (len <= 0)
    {
        return (1);
    }
    if (len1 > 0 && (*buf)[len1 - 1] == '\n')
    {
        (*buf)[len1 - 1] = '\0';
    }
    return (0);
}

/**
 * handle_builtin_commands - Function to handle built-in commands
 */
int handle_builtin_commands(char **args)
{
    if (args[0] == NULL)
        return (0);

    if (custom_strcmp(args[0], "exit") == 0)
    {
        free(args);
        exit(EXIT_SUCCESS);
    }
    else if (custom_strcmp(args[0], "env") == 0)
    {
        print_env();
        return (1);
    }
    else if (custom_strcmp(args[0], "setenv") == 0)
    {
        handle_setenv(args);
        return (1);
    }
    else if (custom_strcmp(args[0], "unsetenv") == 0)
    {
        handle_unsetenv(args);
        return (1);
    }
    else if (custom_strcmp(args[0], "cd") == 0)
    {
        handle_cd(args);
        return (1);
    }
    else if (custom_strcmp(args[0], "echo") == 0)
    {
        handle_echo(args);
        return (1);
    }
    return 0;
}

/**
 * _getenv - get the environ value
 * @name: key string to search
 * Return: value string in the key value pair
 */

char *_getenv(char *name)
{
    size_t len = custom_strlen(name);
    int i = 0;

    if (name == NULL)
        return (NULL);
    while (environ[i] != NULL)
    {
        if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
        {
            return (environ[i] + len + 1);
        }
        i++;
    }
    print_string("Not found");
    return (NULL);
}

/**
 * command_node - create a linked list containing the commands
 * Return: head of the linked list
 */
bin *command_node(char *command)
{
    bin *head = NULL;
    bin *new_node;
    char *token;
    bin *temp = NULL;
    char *command_copy;

    if (command == NULL)
        return (NULL);
    command_copy = custom_strdup(command);
    if (command_copy == NULL)
        return (NULL);
    token = strtok(command_copy, ";|&");
    while (token != NULL)
    {
        new_node = (bin *)malloc(sizeof(bin));
        if (new_node == NULL)
            return (NULL);
        new_node->dir = token;
        if (new_node->dir == NULL)
            return (NULL);
        new_node->next = NULL;
        if (head == NULL)
        {
            head = new_node;
            temp = head;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        token = strtok(NULL, ";|&");
    }
    return (head);
    free(command_copy);
}

/**
 * create_node - create a linked list with directories from
 *      "path"in the environ variable
 * Return: the head of the linked list
 */
bin *create_node(void)
{
    bin *head = NULL;
    bin *temp;
    bin *new_node;
    char *token;
    char *path;
    char *pathcopy;

    path = _getenv("PATH");
    if (path == NULL)
        return (NULL);
    pathcopy = custom_strdup(path);
    if (pathcopy == NULL)
        return (NULL);
    token = strtok(pathcopy, ":");
    while (token != NULL)
    {
        new_node = (bin *)malloc(sizeof(bin));
        if (new_node == NULL)
        {
            free(pathcopy);
            return (NULL);
        }
        new_node->dir = custom_strdup(token);
        if (new_node->dir == NULL)
        {
            free(new_node);
            free(pathcopy);
            return (NULL);
        }
        new_node->next = NULL;
        if (head == NULL)
            head = new_node;
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        token = strtok(NULL, ":");
    }
    free(pathcopy);
    return (head);
}

/**
 *free_node - free nodes
 * @head: Head of the node
 * Return: 0 on success, non zero on failure
 */
int free_node(bin *head)
{
    bin *temp;

    if (head == NULL)
        return (-1);
    temp = head;
    while (temp != NULL)
    {
        temp = head;
        head = temp->next;
        free(temp);
    }
    return (0);
}

/**
 * handle_echo - function to handle ech command
 * @args: arguments
 */

void handle_echo(char **args)
{
    int i = 1;
    char *var_name;
    char *value;
    char pid_str[25];
    int_to_str(getpid(), pid_str, sizeof(pid_str));

    while (args[i] != NULL)
    {
        if (custom_strcmp(args[i], "$$") == 0)
        {
            write(STDOUT_FILENO, pid_str, custom_strlen(pid_str));
        }
        if (args[i][0] == '$')
        {
            var_name = args[i] + 1;
            value = getenv(var_name);
            if (value != NULL)
            {
                write(STDOUT_FILENO, value, custom_strlen(value));
            }
            else
            {
                write(STDOUT_FILENO, "", 1);
            }
        }
        else
        {
            write(STDOUT_FILENO, args[i], custom_strlen(args[i]));
        }
        if (args[i + 1] != NULL)
        {
            write(STDOUT_FILENO, " ", 1);
        }
        i++;
    }
    write(STDOUT_FILENO, "\n", 1);
}

/**
 * handle_setenv - Function to handle the setenv command
 */
void handle_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL)
    {
        write(STDERR_FILENO, "setenv: usage: setenv VARIABLE VALUE\n", 36);
        return;
    }
    set_env(args[1], args[2]);
}

/**
 * handle_unsetenv - Function to handle the unsetenv command
 */
void handle_unsetenv(char **args)
{
    if (args[1] == NULL)
    {
        write(STDERR_FILENO, "unsetenv: usage: unsetenv VARIABLE\n", 35);
        return;
    }
    unset_env(args[1]);
}

/**
 * handle_cd - Function to handle the cd command
 */
void handle_cd(char **args)
{
    static char prev_dir[BUFFER_SIZE];
    char *dir = args[1];
    char curr_dir[BUFFER_SIZE];

    if (dir == NULL || custom_strcmp(dir, "~") == 0)
    {
        dir = getenv("HOME");
    }
    else if (custom_strcmp(dir, "-") == 0)
    {
        if (prev_dir[0] == '\0')
        {
            write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
            return;
        }
        dir = prev_dir;
        write(STDOUT_FILENO, dir, custom_strlen(dir));
        write(STDOUT_FILENO, "\n", 1);
    }

    if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
    {
        perror("getcwd");
        return;
    }

    if (chdir(dir) != 0)
    {
        perror("cd");
    }
    else
    {
        set_env("OLDPWD", curr_dir);
        if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
        {
            set_env("PWD", curr_dir);
            custom_strncpy(prev_dir, curr_dir, sizeof(prev_dir) - 1);
            prev_dir[sizeof(prev_dir) - 1] = '\0';
        }
    }
}

/**
 * print_env - Function to print all environment variables
 */
void print_env(void)
{
    char **env;

    for (env = environ; *env != NULL; env++)
    {
        write(STDOUT_FILENO, *env, custom_strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
    }
}

/**
 * find_command - Function to find the full path of a command
 */
char *find_command(const char *command)
{
    char *path = getenv("PATH");
    char *path_dup = custom_strdup(path);
    char *dir = custom_strtok(path_dup, ":");
    char *full_path = malloc(BUFFER_SIZE);

    if (path == NULL)
    {
        return (NULL);
    }
    if (path_dup == NULL)
    {
        perror("simple_shell: allocation error");
        free(path_dup);
        return (NULL);
    }
    if (full_path == NULL)
    {
        perror("simple_shell: allocation error");
        free(full_path);
        return (NULL);
    }

    while (dir != NULL)
    {
        concat_path(full_path, dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_dup);
            return full_path;
        }
        dir = custom_strtok(NULL, ":");
    }

    free(full_path);
    free(path_dup);
    return NULL;
}

/**
 * set_env - Function to set an environment variable
 */
void set_env(const char *name, const char *value)
{
    if (setenv(name, value, 1) != 0)
    {
        perror("setenv");
    }
}

/**
 * unset_env - Function to unset an environment variable
 */
void unset_env(const char *name)
{
    if (unsetenv(name) != 0)
    {
        perror("unsetenv");
    }
}

/**
 * execute_command - Function to find and execute commands
 * @args: arguments
 */
void execute_command(char **args)
{
    char *command_path;

    if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
    {
        command_path = custom_strdup(args[0]);
    }
    else
    {
        command_path = find_command(args[0]);
    }

    if (command_path == NULL)
    {
        write(STDOUT_FILENO, "Command not found\n", 18);
        return;
    }

    exec_command(command_path, args);
    free(command_path);
}

/**
 * exec_command - Function to fork and execute a command
 * @command_path: command path
 * @args: arguments
 */
void exec_command(char *command_path, char **args)
{
    int status;
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        if (execve(command_path, args, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (waitpid(pid, &status, WNOHANG) == -1)
        {
            perror("waitpid");
        }
    }
}

/**
 * main - Entry point of the shell
 * Return: 0
 */
int main(void)
{
    char *input = NULL;
    size_t bufsize = 0;
    char **args;
    int status;
    bin *head;
    bin *temp;

    do
    {
        display_prompt();

        status = read_input(&input, &bufsize);
        if (status == -1)
        {
            perror("read_input");
            free(input);
            exit(EXIT_FAILURE);
        }
        if (input == NULL || custom_strlen(input) == 0 || custom_strcmp(input, '\n') == 0)
        {
            free(input);
            input = NULL;
            continue;
        }

        head = command_node(input);
        if (head == NULL)
        {
            perror("command_node");
            free(input);
            exit(EXIT_FAILURE);
        }

        temp = head;
        while (temp != NULL)
        {
            args = split_line(temp->dir);
            if (args == NULL)
            {
                perror("split_line");
                free_node(head);
                free(input);
                exit(EXIT_FAILURE);
            }
            if (!handle_builtin_commands(args))
            {
                execute_command(args);
            }
            temp = temp->next;
        }
        free_node(input);
    } while (1);

    return (0);
}
/**
 * custom_strlen - Custom strlen function
 * @str: string
 * 
 * Return: length
 */
size_t custom_strlen(const char *str)
{
    size_t length = 0;

    while (str[length] != '\0')
    {
        length++;
    }
    return (length);
}

/**
 * custom_strdup - Custom strdup function
 * @s: string
 * 
 * Retunr: duplicated string
 */
char *custom_strdup(const char *s)
{
    size_t len = custom_strlen(s) + 1;
    size_t i;

    char *dup = malloc(len);

    if (dup == NULL)
        return NULL;
    for (i = 0; i < len; i++)
        dup[i] = s[i];
    return (dup);
}

/**
 * _strncmp - compare n no of characters in a string
 * @n: Number of characetrs to be compared
 * @str1: first string
 * @str2: second string
 * Return: 0 if the match
 */
int _strncmp(char *str1, char *str2, ssize_t n)
{
    ssize_t i;

    for (i = 0; i < n && str1[i] != '\0' && str2[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
    }
    if (i < n && (str1[i] == '\0' || str2[i] == '\0'))
        return (str1[i] - str2[i]);
    return (0);
}

/**
 * Custom strcmp function
 */

int custom_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * Custom strncmp function
 */
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
        n--;
    }
    if (n == 0)
        return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
/**
 * Custom strncpy function
 */
char *custom_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return (dest);
}

/**
 * Custom strtok function
 */
char *custom_strtok(char *str, const char *delim)
{
    static char *saved_str;
    char *start;
    const char *d;

    if (str)
        saved_str = str;
    if (!saved_str || *saved_str == '\0')
        return NULL;

    start = saved_str;
    while (*saved_str)
    {
        d = delim;
        while (*d)
        {
            if (*saved_str == *d)
            {
                *saved_str++ = '\0';
                if (saved_str == start)
                {
                    start++;
                    continue;
                }
                return start;
            }
            d++;
        }
        saved_str++;
    }
    return (start);
}
/**
 * Custom getline function
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t i = 0;
    int c;
    char *new_lineptr;

    if (*lineptr == NULL)
    {
        *n = 128; /* Initial buffer size */
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return (-1);
    }

    while ((c = fgetc(stream)) != EOF)
    {
        if (i >= *n - 1)
        {
            *n *= 2;
            new_lineptr = realloc(*lineptr, *n);
            if (new_lineptr == NULL)
                return (-1);
            *lineptr = new_lineptr;
        }

        (*lineptr)[i++] = (char)c;

        if (c == '\n')
            break;
    }

    if (c == EOF && i == 0)
        return (-1);

    (*lineptr)[i] = '\0';
    return (i);
}

/**
 * Function to split the input line into arguments
 */
char **split_line(char *line)
{
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;
    int i = 0, j = 0;

    if (!tokens)
    {
        perror("simple_shell: allocation error");
        exit(EXIT_FAILURE);
    }

    line = no_whitespace(line);

    token = custom_strtok(line, DELIMITERS);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("simple_shell: allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = custom_strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;

    while (tokens[i] != NULL)
    {
        if (custom_strlen(tokens[i]) == 0)
        {
            free(tokens[i]);
            for (j = i; tokens[j] != NULL; j++)
            {
                tokens[j] = tokens[j + 1];
            }
        }
        else
        {
            i++;
        }
    }
    return (tokens);
}

/**
 * print_string - prints a string
 * @str: string to be printed
 * Return: Number of characters
 */
int print_string(char *str)
{
    if (str != NULL)
    {
        write(1, str, custom_strlen(str));
        return (custom_strlen(str));
    }
    else
    {
        perror("print string");
        return (0);
    }
}

/**
 * concat_path - function to mimic snprintf
 * @fp: full path
 * @dir: directory location
 * @command: command
 */

void concat_path(char *fp, const char *dir, const char *command)
{
    while (*dir != '\0')
    {
        *fp++ = *dir++;
    }

    if (*(fp - 1) != '/')
    {
        *fp++ = '/';
    }

    while (*command != '\0')
    {
        *fp++ = *command++;
    }

    *fp = '\0';
}
/**
 * int_to_str - function that converts an int to a string
 * @value: value
 * @str: string
 * @size: size
 * 
 * Return: nothing
 */
void int_to_str(int value, char *str, size_t size)
{
    char buf[10];
    size_t i = 0;
    size_t len;

    if (size == 0)
    {
        return;
    }

    if (value == 0)
    {
        if (size > 0)
        {
            str[0] = '0';
            str[1] = '\0';
        }
        return;
    }
    while (value > 0 && 1 < sizeof(buf) - 1)
    {
        buf[i++] = '0' +(value % 10);
        value /= 10;
    }
    buf[i] = '\0';

    len = i;
    if (len >= size)
    {
        len = size - 1;
    }
    for (i = 0; i < len; i++)
    {
        str[i] = buf[len - i - 1];
    }
    str[len] = '\0';
}

/**
 * no_whitespace - function to remove trailing and leading spaces
 * @str: string
 * Return: string
 */

char *no_whitespace(char *str)
{
    char *src = str;
    char *dst = str;

    while (isspace((unsigned char)*src))
    {
        src++;
    }
    if (*src == '\0')
    {
        *dst = '\0';
        return (str);
    }
    while (*src)
    {
        *dst++ = *src;

        if (isspace((unsigned char)*src))
        {
            while (isspace((unsigned char)*src))
            {
                src++;
            }
            if (*src)
            {
                *dst++ = ' ';
            }
        }
        else
        {
            src++;
        }
    }
    *dst = '\0';

    if (dst != str && isspace((unsigned char)*(dst - 1)))
    {
        *(dst - 1) = '\0';
    }
    return (str);
}
