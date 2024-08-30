#include "main.h"
/**
 * handle_cd - Function to handle the cd built-in command
 * @args: arguments
 */
void handle_cd(char **args)
{
    static char prev_dir[BUFFER_SIZE];
    char *dir = args[1];
    char curr_dir[BUFFER_SIZE];

    if (dir == NULL || _strcmp(dir, "~") == 0)
    {
        dir = _getenv("HOME");
    }
    else if (_strcmp(dir, "-") == 0)
    {
        if (prev_dir[0] == '\0')
        {
            write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
            return;
        }
        dir = prev_dir;
        write(STDOUT_FILENO, dir, _strlen(dir));
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
        _setenv("OLDPWD", curr_dir);
        if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
        {
            _setenv("PWD", curr_dir);
            _strncpy(prev_dir, curr_dir, sizeof(prev_dir) - 1);
            prev_dir[sizeof(prev_dir) - 1] = '\0';
        }
    }
}
