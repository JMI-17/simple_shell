#include "main.h"

#define SUCCESS 0
#define COMMAND_NOT_FOUND 127

/**
 * executeCommand - Executes the given command using fork and execve.
 * @command: The command to execute.
 */
void executeCommand(const char *command)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1)
    {
        printError("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Child process */
        if (execlp("/bin/sh", "sh", "-c", command, NULL) == -1)
        {
            perror("execve");
            _exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        if (waitpid(pid, &status, 0) == -1)
        {
            printError("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status) && WEXITSTATUS(status) != SUCCESS)
        {
            write(STDERR_FILENO, "Error: Command not found\n", 26);
        }
    }
}
