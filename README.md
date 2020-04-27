# My-Unix-Shell
Recreated the Unix shell using hashmaps and my tokenizer.

### Authors: 
Allen West (Me),
Justin Delvecchio (Partner)

MOST WORK DONE IN NUSH.C
This is a Unix shell like "bash" called "nush".

### My shell operates as follows:

    Accepts an optional script file as the first command line argument.
    If there's no script, shows a prompt. The prompt is "nush$ ". Command input is accepted on the same line after the prompt.
    Reads one line of commands from either stdin or the script.
    Executes that line of commands.
    Repeats until EOF or an "exit" command.

### Command lines are made up of:

    Programs to execute.
    Built-in commands.
    Command line arguments to programs / builtins.
    Operators.

### Executeable Programs

west@location:directory$ ./nush 
nush$ head -n 2 /usr/share/dict/words
A
A's
nush$ 

### Given a program to execute, like "head" above, my shell does three things:

    fork(), to create a new process.
    in the child process, exec(), to execute the requested program, passing through the three command line arguments
    in the parent process, wait() or waitpid(), to allow the program to finish before executing another command

### Built-in Commands

nush$ pwd
/home/west/work/3650/nush
nush$ cd tests
nush$ pwd
/home/west/work/3650/nush/tests
nush$ exit
west@location:directory$

### Some commands aren't programs to execute, they're things that the shell should handle itself. This implements two of these:

    The "cd" command changes the current directory. This means calling chdir() to change the state of your shell process.
    The "exit" command exits the shell.

In bash, lots of commands that are available as programs are actually built-in for efficiency, like pwd, echo, etc. 
My shell just runs these as programs.

### Operators

nush$ sort tests/sample.txt | tail -n 3
remorselessly
revolutionized
underplays
nush$ 

Operators either modify the behavior of one command or chain together multiple commands into a single command line.

#### My shell supports seven operators:

    Redirect input: sort < foo.txt
    Redirect output: sort foo.txt > output.txt
    Pipe: sort foo.txt | uniq
    Background: sleep 10 &
    And: true && echo one
    Or: true || echo one
    Semicolon: echo one; echo two
