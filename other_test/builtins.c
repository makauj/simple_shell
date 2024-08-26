#include "main.h"

/**
 * 
 */
int handle_builtin_commands(char **args)
{
    if (custom_strcmp(args[0], "exit") == 0)
    {
        free(args);
        exit(EXIT_SUCCESS);
    }
    else if (custom_strcmp(args[0], "env") == 0)
    {
        print_env();
        return 1;
    }
    else if (custom_strcmp(args[0], "setenv") == 0)
    {
        handle_setenv(args);
        return 1;
    }
    else if (custom_strcmp(args[0], "unsetenv") == 0)
    {
        handle_unsetenv(args);
        return 1;
    }
    else if (custom_strcmp(args[0], "cd") == 0)
    {
        handle_cd(args);
        return 1;
    }
    return 0;
}

/**
 * 
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
 * 
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
