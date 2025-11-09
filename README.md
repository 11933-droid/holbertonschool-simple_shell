#  Simple Shell

##  Overview
The **Simple Shell** project is a UNIX command-line interpreter written in C.  
It replicates core Bash functionalities such as reading commands, parsing them, creating new processes, and executing programs.  
Developed as part of the **Holberton School low-level programming curriculum**, it demonstrates mastery of process management, system calls, and memory handling.

---

##  Features
- Execute UNIX commands (`/bin/ls`, `/bin/pwd`, `/bin/date`, etc.)
- Handle command-line arguments (`/bin/ls -l /tmp`)
- Search executables in the system PATH
- Implement built-in commands:
  - `exit` — terminates the shell
  - `env` — prints all environment variables
- Works in both **interactive** and **non-interactive** modes
- Proper **error handling** for missing or invalid commands
- Follows **Betty coding style** and best practices

---

##  Compilation
To compile the shell:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

 Usage

Run the shell interactively:

./hsh


Or through a non-interactive pipe:

echo "/bin/ls" | ./hsh

Example Session
$ /bin/ls -l
$ ls -l /var
$ env
$ exit

 Learning Objectives

Understand how a shell parses and executes commands.

Learn process creation and synchronization using fork(), execve(), and wait().

Explore PATH resolution, environment variables, and system calls.

Practice structured programming, error handling, and memory management in C.

 Task Explanations
Task 0 – Betty would be proud

Ensure all C files follow the Betty coding style.
No warnings, no errors, clean formatting, and proper documentation.

Task 1 – Simple shell 0.1

Create a basic shell that executes commands using their full paths.
Use fork(), execve(), and wait() to manage child processes.
Support both interactive and non-interactive input.

Task 2 – Simple shell 0.2

Add support for command-line arguments.
Use strtok() to split input strings into tokens (program + arguments).
Allow commands like /bin/ls -l /tmp to execute properly.

Task 3 – Simple shell 0.3

Implement PATH handling.
When a command doesn’t include /, search each directory in $PATH.
Execute the first valid executable found, or print an error if none.
Do not call fork() if the command does not exist.

Task 4 – Simple shell 0.4

Add the built-in exit command.
When the user types exit, terminate the program gracefully.
No arguments are required for this built-in.

Task 5 – Simple shell 1.0

Implement the built-in env command.
When the user types env, print all current environment variables.
Ensure each variable is displayed on a new line.
