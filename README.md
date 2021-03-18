# Minishell - by Tmeizo & bMicheal

<img width="1115" alt="Screenshot 2021-03-17 at 15 48 16" src="https://user-images.githubusercontent.com/73602657/111475658-6066bd00-873e-11eb-9c8c-e5cc834f21c9.png">

## About

It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.

Click here to see full [Subject][1]

## Installation & Usage

### Building the program

1. Download/Clone this repo

        git clone https://github.com/bMicheal42/minishell.git
2. `cd` into the root directory and run `make`

        cd minishell
        make

### Running the program

After building the source, run `./minishell` from the project root.

## Main Project Instructions

### Mandatory

- Can only use C
- Must respect the school imposed coding style [The Norme][2]
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors without using `errno`, by displaying a message adapted
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Handle program interruption (Ctrl + D)

### Resources

* https://www.thegeekstuff.com/2012/03/linux-signals-fundamentals/
* https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
* https://www.geeksforgeeks.org/dup-dup2-linux-system-call/?ref=rp
* https://www.geeksforgeeks.org/pipe-system-call/?ref=rp
* https://www.tutorialspoint.com/unix/unix-signals-traps.htm
* https://www.tutorialspoint.com/unix_system_calls/execve.htm
* http://www.rozmichelle.com/pipes-forks-dups/
* http://tzimmermann.org/2017/08/17/file-descriptors-during-fork-and-exec/
* http://tzimmermann.org/2017/09/01/the-internals-of-unix-pipes-and-fifos/
* https://catonmat.net/ftp/bash-redirections-cheat-sheet.pdf


[1]: https://github.com/bMicheal42/minishell/blob/main/minishell.en.pdf
[2]: https://github.com/bMicheal42/minishell/blob/main/norme.en.pdf
