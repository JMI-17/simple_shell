# 0x16. C - Simple Shell

- The Aim of this project is to create a Custom unix/linux Terminal that can both take and execute Linux Commands and Bash Scripts


## TASK

### Mandatory
- 0. Betty would be proud
Write a beautiful code that passes the Betty checks

- 1. Simple shell 0.1
Write a UNIX command line interpreter.</br>

Usage: simple_shell</br>
Your Shell should:</br>

Display a prompt and wait for the user to type a command. A command line always ends with a new line.</br>
The prompt is displayed again each time a command has been executed.</br>
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.</br>
The command lines are made only of one word. No arguments will be passed to programs.</br>
If an executable cannot be found, print an error message and display the prompt again.</br>
Handle errors.</br>
You have to handle the “end of file” condition (Ctrl+D)</br>
You don’t have to:</br>

use the PATH</br>
implement built-ins</br>
handle special characters : ", ', `, \, *, &, #</br>
be able to move the cursor</br>
handle commands with arguments</br>
execve will be the core part of your Shell, don’t forget to pass the environ to it…</br>

- 2. Simple shell 0.2
Simple shell 0.1 + </br>

Handle command lines with arguments</br>

- 3. Simple shell 0.3
Simple shell 0.2 + </br>

Handle the PATH</br>
fork must not be called if the command doesn’t exist</br>

- 4. Simple shell 0.4
Simple shell 0.3 +

Implement the exit built-in, that exits the shell</br>
Usage: exit</br>
You don’t have to handle any argument to the built-in exit</br>

- 5. Simple shell 1.0
Simple shell 0.4 +

Implement the env built-in, that prints the current environment</br>

### Advanced
- 6. Simple shell 0.1.1
Simple shell 0.1 +</br>

Write your own getline function</br>
Use a buffer to read many chars at once and call the least possible the read system call</br>
You will need to use static variables</br>
You are not allowed to use getline</br>
You don’t have to:</br>

be able to move the cursor</br>

- 7. Simple shell 0.2.1
Simple shell 0.2 +

You are not allowed to use strtok</br>

- 8. Simple shell 0.4.1
Simple shell 0.4 +

handle arguments for the built-in exit</br>
Usage: exit status, where status is an integer used to exit the shell</br>

- 9. setenv, unsetenv
Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands</br>

setenv</br>
Initialize a new environment variable, or modify an existing one</br>
Command syntax: setenv VARIABLE VALUE</br>
Should print something on stderr on failure</br>
unsetenv</br>
Remove an environment variable</br>
Command syntax: unsetenv VARIABLE</br>
Should print something on stderr on failure</br>

- 10. cd
Simple shell 1.0 +</br>

Implement the builtin command cd:

Changes the current directory of the process.</br>
Command syntax: cd [DIRECTORY]</br>
If no argument is given to cd the command must be interpreted like cd $HOME</br>
You have to handle the command cd -</br>
You have to update the environment variable PWD when you change directory</br>
man chdir, man getcwd</br>

- 11. ;
Simple shell 1.0 +

Handle the commands separator;</br>


- 12. && and ||
Simple shell 1.0 +</br>

Handle the && and || shell logical operators

- 13. alias
Simple shell 1.0 +</br>

Implement the alias builtin command</br>
Usage: alias [name[='value'] ...]</br>
alias: Prints a list of all aliases, one per line, in the form name='value'</br>
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'</br>
alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value</br>


-14. Variables
Simple shell 1.0 +

Handle variables replacement</br>
Handle the $? variable</br>
Handle the $$ variable</br>


- 15. Comments
Simple shell 1.0 +

Handle comments (#)</br>


- 16. File as input
Simple shell 1.0 +</br>

Usage: simple_shell [filename]</br>
Your shell can take a file as a command line argument</br>
The file contains all the commands that your shell should run before exiting</br>
The file should contain one command per line</br>
In this mode, the shell should not print a prompt and should not read from stdin


