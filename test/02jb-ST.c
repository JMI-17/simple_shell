#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/**
 * displayPrompt - Displays the shell prompt.
 */
void displayPrompt(void)
{
    printf("$\t");
    fflush(stdout); /* Ensure the prompt is displayed immediately */
}

/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    char *args[MAX_ARGUMENTS + 1];  /* +1 for the NULL at the end */
    int i;

    /* Display a greeting message */
    char *message = "Hello, Betty!";
    printf("%s\n", message);

    while (1)
    {
        char *token;

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

        /* Tokenize the command into arguments */
        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGUMENTS)
        {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;  /* Set the last element to NULL to terminate the args array */

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
            /* Execute the command with arguments */
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
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
                fprintf(stderr, "Error: Command '%s' not found\n", args[0]);
            }
        }
    }

    return 0;
}

