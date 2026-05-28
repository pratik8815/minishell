# MiniShell - Custom Unix Shell in C

## Overview

MiniShell is a custom Unix-like shell developed in C for Linux systems.
The project demonstrates concepts of process management, signal handling, command execution, and job control similar to a real Linux shell.

The shell supports both internal and external commands, foreground/background process handling, and custom shell prompt modification.

---

# Features

* Internal command execution

  * `cd`
  * `pwd`
  * `echo`
  * `exit`
  * `jobs`
  * `fg`
  * `bg`

* External command execution using:

  * `fork()`
  * `execvp()`
  * `waitpid()`

* Signal handling

  * `Ctrl + C` → Interrupt running process
  * `Ctrl + Z` → Stop process and move to background

* Job control

  * Background process tracking
  * Resume jobs using `fg` and `bg`

* Dynamic shell prompt customization

  * `PS1=<prompt_name>`

* Linked-list based job management

* Colored terminal interface

---

# Technologies Used

* C Programming
* Linux System Calls
* Signals
* Process Management
* Linked Lists
* GCC Compiler

---

# Project Structure

```bash
.
├── main.c
├── minishell.c
├── minishell.h
├── minishell_list_opr.c
├── extCommand.txt
└── Makefile
```

---

# How It Works

1. Shell waits for user input.
2. Input command is parsed into arguments.
3. Internal commands are executed directly.
4. External commands are executed using child processes.
5. Signals are handled for process interruption and suspension.
6. Suspended jobs are stored in a linked list.

---

# Compilation

```bash
gcc main.c minishell.c minishell_list_opr.c -o minishell
```

---

# Run

```bash
./minishell
```

---

# Example Commands

```bash
pwd
cd Documents
echo Hello
ls
sleep 20
Ctrl + Z
jobs
fg
```

---

# Concepts Covered

* Process Creation
* Process Control
* Signal Handling
* System Calls
* Job Scheduling
* Linked Lists
* Command Parsing

---

# Future Improvements

* Pipe support (`|`)
* Input/Output redirection (`>`, `<`)
* Command history
* Auto-completion
* Environment variable expansion
* Multiple background jobs handling

---

# Author

Pratik Satsure

Embedded Systems & Linux Enthusiast
