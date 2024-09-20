# Simple Shell

### Key Concepts to Learn

1. **Basic Shell Functionality**:
   - **Initialization**: Loading configuration files (if any).
   - **Command Loop**: Reading, parsing, and executing commands.
   - **Termination**: Cleaning up resources before exiting.

2. **System Calls**:
   - **Fork**: Creating a new process.
   - **Exec**: Replacing the current process image with a new one.
   - **Wait**: Waiting for a process to change state.
   - **Pipe**: Creating a unidirectional data channel.

3. **Input/Output Handling**:
   - **Standard Input/Output**: Reading from stdin and writing to stdout.
   - **Redirection**: Redirecting input/output to/from files.
   - **Pipes**: Connecting the output of one command to the input of another.

4. **Signal Handling**:
   - **Signals**: Handling interrupts and other signals.

5. **Memory Management**:
   - **Dynamic Memory Allocation**: Using `malloc` and `free`.

### Step-by-Step Guide to Building a Shell

1. **Setup Your Environment**:
   - Ensure you have a C compiler (like `gcc`) and a text editor (like `vim` or `VSCode`).

2. **Basic Shell Structure**:
   - Create a main loop that reads commands from the user, parses them, and executes them.
   ```c
   int main() {
       char *line;
       char **args;
       int status;

       do {
           printf("> ");
           line = read_line();
           args = split_line(line);
           status = execute(args);

           free(line);
           free(args);
       } while (status);

       return 0;
   }
   ```

3. **Reading Input**:
   - Implement a function to read a line of input from the user.
   ```c
   char *read_line(void) {
       char *line = NULL;
       ssize_t bufsize = 0; // getline will allocate a buffer for us
       getline(&line, &bufsize, stdin);
       return line;
   }
   ```

4. **Parsing Input**:
   - Split the input line into arguments.
   ```c
   #define LSH_TOK_BUFSIZE 64
   #define LSH_TOK_DELIM " \t\r\n\a"
   char **split_line(char *line) {
       int bufsize = LSH_TOK_BUFSIZE, position = 0;
       char **tokens = malloc(bufsize * sizeof(char*));
       char *token;

       if (!tokens) {
           fprintf(stderr, "lsh: allocation error\n");
           exit(EXIT_FAILURE);
       }

       token = strtok(line, LSH_TOK_DELIM);
       while (token != NULL) {
           tokens[position] = token;
           position++;

           if (position >= bufsize) {
               bufsize += LSH_TOK_BUFSIZE;
               tokens = realloc(tokens, bufsize * sizeof(char*));
               if (!tokens) {
                   fprintf(stderr, "lsh: allocation error\n");
                   exit(EXIT_FAILURE);
               }
           }

           token = strtok(NULL, LSH_TOK_DELIM);
       }
       tokens[position] = NULL;
       return tokens;
   }
   ```

5. **Executing Commands**:
   - Implement a function to execute the parsed commands.
   ```c
   int execute(char **args) {
       pid_t pid, wpid;
       int status;

       pid = fork();
       if (pid == 0) {
           // Child process
           if (execvp(args[0], args) == -1) {
               perror("lsh");
           }
           exit(EXIT_FAILURE);
       } else if (pid < 0) {
           // Error forking
           perror("lsh");
       } else {
           // Parent process
           do {
               wpid = waitpid(pid, &status, WUNTRACED);
           } while (!WIFEXITED(status) && !WIFSIGNALED(status));
       }

       return 1;
   }
   ```

6. **Adding Built-in Commands**:
   - Implement built-in commands like `cd`, `exit`, etc.
   ```c
   int lsh_cd(char **args) {
       if (args[1] == NULL) {
           fprintf(stderr, "lsh: expected argument to \"cd\"\n");
       } else {
           if (chdir(args[1]) != 0) {
               perror("lsh");
           }
       }
       return 1;
   }

   int lsh_exit(char **args) {
       return 0;
   }
   ```

7. **Handling Signals**:
   - Implement signal handling to manage interrupts.
   ```c
   void sigintHandler(int sig_num) {
       signal(SIGINT, sigintHandler);
       printf("\nCannot be terminated using Ctrl+C\n");
       fflush(stdout);
   }
   ```

### Additional Resources

- [Stephen Brennan's Tutorial on Writing a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)¹
- [Guru99 Shell Scripting Tutorial](https://www.guru99.com/introduction-to-shell-scripting.html)²

Feel free to ask if you need more details on any specific part of the process! Happy coding! 😊

¹: https://brennan.io/2015/01/16/write-a-shell-in-c/
²: https://www.guru99.com/introduction-to-shell-scripting.html

Source: Conversation with Copilot, 20/09/2024
(1) Tutorial - Write a Shell in C • Stephen Brennan. https://brennan.io/2015/01/16/write-a-shell-in-c/.
(2) Shell Scripting Tutorial: How to Create Shell Script in Linux/Unix - Guru99. https://www.guru99.com/introduction-to-shell-scripting.html.
(3) How to Create a Shell Script in Linux. https://www.linuxjournal.com/content/how-create-shell-script-linux.
(4) Shell Scripting for Beginners – How to Write Bash Scripts in Linux. https://www.freecodecamp.org/news/shell-scripting-crash-course-how-to-write-bash-scripts-in-linux/.
(5) github.com. https://github.com/bogdanponomarenko/network-traffic-daemon/tree/944d7760d933d97d774160545e9621f388bb160c/shell.c.
(6) github.com. https://github.com/TomKouk/Linux-shell-scripting/tree/ecab53fd32ffb908c2f70843b33aad28b34b6024/mysh2%20%281%29.c.
(7) github.com. https://github.com/cyprx/learning/tree/5be90594d8a508e6d7e0cbadb55593f18f9f90e7/cshell%2Flsh.c.
(8) github.com. https://github.com/pankaj0812/BasicShell_in_C/tree/0d365b091f2f56c918573410f997bda4c5f8ffdb/main.c.
(9) github.com. https://github.com/MaelRouxel/SGF-2/tree/fb81831a3dff836cb8decc7091c1ff7d802b2f3c/shellTerminal.c.
(10) github.com. https://github.com/odaiodd/concurrency-shell/tree/4b0f1f8dc22556de13606b4771168fb416c9ad17/cmd.c.
(11) github.com. https://github.com/JamesSab1/my_shell/tree/da121c060ff403dbafe046d2c825242f9f8b9e07/my_shell.c.
(12) github.com. https://github.com/redtree0/Learning-C/tree/610f42d6ab384bc621fd762539a2c305f74edb58/Shell%2FREADME.md.
(13) github.com. https://github.com/ycortes94/CMPE-142-Unix-Shell/tree/42b6540074b11b207e0d6df10246b6c1b2f61920/MyShell.c.
(14) github.com. https://github.com/anseromar/simple-shell-c-/tree/e7d63c471d5d63b522c0f2ff70ad7ac6647ba4d9/main.c.
(15) github.com. https://github.com/parth18356/Basic-Linux-Shell/tree/ea8efc5e06ec6775ed31259f78a22d86a4b0d11f/final.c.
(16) en.wikipedia.org. https://en.wikipedia.org/wiki/Unix_shell.

