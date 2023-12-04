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
	fflush(stdout); /* This ensures the prompt is displayed immediately */
}

/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

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

		/* Fork a new process */
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			/* Child process */
			/* Execute the command */
			if (execve(command, NULL, NULL) == -1)
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

	return {0};
}
