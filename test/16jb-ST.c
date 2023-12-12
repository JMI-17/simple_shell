#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

/**
 * displayPrompt - Displays the shell prompt.
 */
void displayPrompt(void)
{
    printf("$\t");
    fflush(stdout); /* Ensure the prompt is displayed immediately */
}

/**
 * executeCommand - Executes a command and waits for its completion.
 */
void executeCommand(const char *command)
{
    char *const envp[] = {NULL};
    pid_t pid;
    char *args[2];
    args[1] = NULL; /* Ensure the second element is NULL initially */

    /* Fork a new process */
    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Child process */
        /* Execute the command */
        args[0] = (char *)command;
        if (execve(command, args, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        /* Wait for the child process to complete */
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        /* Check if the child process terminated successfully */
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            fprintf(stderr, "Error: Command '%s' not found\n", command);
        }
    }
}

/**
 * executeCommandsFromFile - Executes commands from a file.
 */
void executeCommandsFromFile(const char *filename)
{
    char line[MAX_COMMAND_LENGTH];
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /* Read a command from the file */
        if (fgets(line, sizeof(line), file) == NULL)
        {
            /* Handle end of file */
            break;
        }

        /* Remove the newline character at the end */
        line[strcspn(line, "\n")] = '\0';

        /* Check if the command is empty */
        if (line[0] == '\0')
        {
            continue;
        }

        /* Execute the command */
        executeCommand(line);
    }

    fclose(file);
}

/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(int argc, char *argv[])
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    char *args[2];
    args[1] = NULL; /* Ensure the second element is NULL initially */

    if (argc == 2)
    {
        executeCommandsFromFile(argv[1]);
        return 0;
    }

    while (1)
    {
        displayPrompt();

        /* Read a command from the user */
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the newline character at the end */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the command is empty */
        if (command[0] == '\0')
        {
            continue;
        }

        /* Fork a new process */
        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child process */
            /* Execute the command */
            args[0] = command;
            if (execve(command, args, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            /* Wait for the child process to complete */
            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            /* Check if the child process terminated successfully */
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                fprintf(stderr, "Error: Command '%s' not found\n", command);
            }
        }
    }

    return 0;
}
