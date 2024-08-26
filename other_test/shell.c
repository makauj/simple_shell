#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

size_t custom_strlen(const char *str);
char *custom_strdup(const char *s);
int custom_strcmp(const char *s1, const char *s2);
int custom_strncmp(const char *s1, const char *s2, size_t n);
char *custom_strtok(char *str, const char *delim);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
char **split_line(char *line);
void set_env(const char *name, const char *value);
void handle_cd(char **args);
int print_string(char *str);
size_t custom_strlen(const char *str);
char *custom_strcpy(char *dest, char *src);


#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;


/**
 * Custom strlen function
 */
size_t custom_strlen(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

/**
 * Custom strdup function
 */
char *custom_strdup(const char *s)
{
    size_t len = custom_strlen(s) + 1;
    char *dup = malloc(len);
    if (dup == NULL)
        return NULL;
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    return dup;
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
    return *(unsigned char *)s1 - *(unsigned char *)s2;
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
    return dest;
}

/**
 * Custom strtok function
 */
char *custom_strtok(char *str, const char *delim)
{
    static char *saved_str;
    if (str)
        saved_str = str;
    if (!saved_str || *saved_str == '\0')
        return NULL;

    char *start = saved_str;
    while (*saved_str)
    {
        const char *d = delim;
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
    return start;
}

/**
 * Custom getline function
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (*lineptr == NULL)
    {
        *n = 128;  // Initial buffer size
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return -1;
    }

    size_t i = 0;
    int c;

    while ((c = fgetc(stream)) != EOF)
    {
        if (i >= *n - 1)
        {
            *n *= 2;
            char *new_lineptr = realloc(*lineptr, *n);
            if (new_lineptr == NULL)
                return -1;
            *lineptr = new_lineptr;
        }

        (*lineptr)[i++] = (char)c;

        if (c == '\n')
            break;
    }

    if (c == EOF && i == 0)
        return -1;

    (*lineptr)[i] = '\0';
    return i;
}

/**
 * Function to split the input line into arguments
 */
char **split_line(char *line)
{
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("simple_shell: allocation error");
        exit(EXIT_FAILURE);
    }

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
    return tokens;
}

/**
 * Function to print all environment variables
 */
void print_env(void)
{
    for (char **env = environ; *env != NULL; env++)
    {
        write(STDOUT_FILENO, *env, custom_strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
    }
}

/**
 * Function to find the full path of a command
 */
char *find_command(const char *command)
{
    char *path = getenv("PATH");
    char *path_dup = custom_strdup(path);  // Duplicate the PATH string
    char *dir = custom_strtok(path_dup, ":");
    char *full_path = malloc(BUFFER_SIZE);

    while (dir != NULL)
    {
        snprintf(full_path, BUFFER_SIZE, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)  // Check if the command is executable
        {
            free(path_dup);
            return full_path;  // Command found in this directory
        }
        dir = custom_strtok(NULL, ":");
    }

    free(full_path);
    free(path_dup);
    return NULL;  // Command not found in any directory in PATH
}

/**
 * Function to set an environment variable
 */
void set_env(const char *name, const char *value)
{
    size_t name_len = custom_strlen(name);
    size_t value_len = custom_strlen(value);
    size_t env_len = name_len + value_len + 2; // +1 for '=' and +1 for '\0'

    char *env_entry = malloc(env_len);
    if (!env_entry)
    {
        perror("simple_shell: allocation error");
        return;
    }

    for (size_t i = 0; i < name_len; i++)
        env_entry[i] = name[i];
    env_entry[name_len] = '=';
    for (size_t i = 0; i < value_len; i++)
        env_entry[name_len + 1 + i] = value[i];
    env_entry[env_len - 1] = '\0';

    for (int i = 0; environ[i] != NULL; i++)
    {
        if (custom_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            environ[i] = env_entry;  // Modify existing variable
            return;
        }
    }

    // If the variable does not exist, add a new one
    int env_count;
    for (env_count = 0; environ[env_count] != NULL; env_count++);

    char **new_environ = malloc((env_count + 2) * sizeof(char *));
    if (!new_environ)
    {
        perror("simple_shell: allocation error");
        free(env_entry);
        return;
    }

    for (int i = 0; i < env_count; i++)
    {
        new_environ[i] = environ[i];
    }
    new_environ[env_count] = env_entry;
    new_environ[env_count + 1] = NULL;
    environ = new_environ;
}

/**
 * Function to handle the setenv built-in command
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
 * Function to handle the unsetenv built-in command
 */
void handle_unsetenv(char **args)
{
    if (args[1] == NULL)
    {
        write(STDERR_FILENO, "unsetenv: usage: unsetenv VARIABLE\n", 35);
        return;
    }

    size_t name_len = custom_strlen(args[1]);

    for (int i = 0; environ[i] != NULL; i++)
    {
        if (custom_strncmp(environ[i], args[1], name_len) == 0 && environ[i][name_len] == '=')
        {
            for (int j = i; environ[j] != NULL; j++)
            {
                environ[j] = environ[j + 1];
            }
            return;
        }
    }
}

/**
 * Function to handle the cd built-in command
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
 * Main function of the shell
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    char **args;
    int status;
    char *command_path;

    while (1)
    {
        // Display prompt
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#C_is_fun $; > ", 14);

        // Read input line
        if (custom_getline(&buffer, &bufsize, stdin) == -1)  // Handle EOF (Ctrl+D)
        {
            if (feof(stdin))
            {
                free(buffer);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        // Remove newline character from the command
        buffer[custom_strlen(buffer) - 1] = '\0';

        // If the command is empty, just prompt again
        if (buffer[0] == '\0')
            continue;

        // Split the input into arguments
        args = split_line(buffer);

        // Check for built-in commands
        if (custom_strcmp(args[0], "exit") == 0)
        {
            free(args);
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        else if (custom_strcmp(args[0], "env") == 0)
        {
            print_env();
        }
        else if (custom_strcmp(args[0], "setenv") == 0)
        {
            handle_setenv(args);
        }
        else if (custom_strcmp(args[0], "unsetenv") == 0)
        {
            handle_unsetenv(args);
        }
        else if (custom_strcmp(args[0], "cd") == 0)
        {
            handle_cd(args);
        }
        else
        {
            // Find the full path of the command
            command_path = find_command(args[0]);

            if (command_path == NULL)
            {
                write(STDOUT_FILENO, "Command not found\n", 18);
            }
            else
            {
                // Execute the command
                if (fork() == 0)  // Child process
                {
                    execve(command_path, args, NULL);
                    // If execve fails, print error and exit child process
                    perror("Error");
                    _exit(EXIT_FAILURE);
                }
                else  // Parent process
                {
                    wait(&status);  // Wait for child to finish
                }

                free(command_path);  // Free the memory allocated for the command path
            }
        }

        free(args);  // Free the memory allocated for arguments
    }

    free(buffer);  // Free the input buffer before exiting
    return 0;
}
