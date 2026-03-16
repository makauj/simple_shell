# Simple Shell Project

## Overview

This project is a small UNIX-style command interpreter written in C. It reads user input, parses commands, runs built-in shell operations directly, and executes external programs by resolving them through the PATH environment variable.

The codebase is structured as a learning implementation of a shell rather than a full replacement for bash or sh. It focuses on the core pieces of shell behavior:

- reading commands from standard input
- tokenizing input into commands and arguments
- handling a small set of built-in commands
- resolving executables from PATH
- forking and executing child processes
- preserving shell state for operations like cd and environment updates

## Supported Behavior

The shell currently supports:

- interactive prompt display when running in a terminal
- non-interactive execution through standard input redirection or piping
- command execution with arguments
- absolute-path execution such as /bin/ls
- PATH lookup for commands such as ls, pwd, env, and echo
- sequential command execution separated by semicolons
- comment trimming for lines containing #
- graceful exit on end-of-file with Ctrl+D

## Built-in Commands

The shell implements the following built-ins:

- env: prints the current environment
- echo: prints simple values and supports variable-style input such as $$ and $NAME
- cd: changes the current working directory
- exit: exits the shell
- setenv: sets or updates an environment variable
- unsetenv: removes an environment variable

## Current Limitations

This is not a full POSIX shell. The current implementation does not aim to support advanced shell grammar or job control. In particular:

- pipelines are not implemented
- background execution with & is not implemented
- quoting and escaping behavior is limited
- variable expansion is minimal compared with standard shells
- command chaining is limited to semicolon-separated commands

## Build Requirements

This project targets a POSIX environment such as Linux or WSL. It depends on headers and system calls such as fork, execve, waitpid, access, and chdir.

Building on native Windows without a POSIX compatibility layer will fail because headers like sys/wait.h are not available there.

## Compilation

Compile the shell with:

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -o hsh \
simpleshell.c command_node.c create_node.c custom_cd.c \
display_prompt.c echo.c environ.c execute_command.c \
free_node.c getenv.c handle_error.c read_command.c \
run_command.c search_path.c setenv.c standard.c \
standard2.c standard3.c unsetenv.c
```

If you prefer to use the existing source list in the repository, see compile_list.txt.

## Usage

Run the compiled shell:

```sh
./hsh
```

Example interactive session:

```sh
($) pwd
/home/user/simple_shell
($) ls
README.md  main.h  simpleshell.c
($) env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
($) echo $$
12345
($) cd /tmp
($) pwd
/tmp
($) exit
```

Example non-interactive usage:

```sh
echo "pwd; ls; /bin/echo done" | ./hsh
```

## How It Works

At a high level, the shell runs through this flow:

1. Display a prompt when input is interactive.
2. Read a full line from standard input.
3. Remove the trailing newline and ignore comment text after #.
4. Split the line into semicolon-separated commands.
5. Tokenize each command into arguments.
6. Execute built-ins directly in the shell process.
7. Resolve external commands from PATH or use an absolute path.
8. Fork a child process and run the executable with execve.
9. Wait for the child process to finish before continuing.

## Important Source Files

- simpleshell.c: main shell loop
- read_command.c: line input and comment trimming
- command_node.c: splitting input into command nodes
- execute_command.c: command dispatch and builtin selection
- run_command.c: fork, execve, and waitpid handling
- search_path.c: PATH lookup for executables
- custom_cd.c: cd implementation
- setenv.c and unsetenv.c: environment variable updates
- standard.c, standard2.c, standard3.c: custom string and utility helpers

## Project Goal

The main purpose of this project is to demonstrate how a shell works internally using C and standard UNIX process-management primitives. It is useful for understanding:

- process creation with fork
- program replacement with execve
- synchronous process control with waitpid
- environment handling through environ, setenv, and unsetenv
- basic command parsing and dispatch

## Notes

- The repository contains test and alternate implementation files that appear to be used for development and experimentation.
- The main executable path described here is based on the top-level implementation.
- For best results, validate behavior in Linux or WSL.
