#include "main.h"

/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(void)
{
	char *const envp[] = {NULL};
	char *command = NULL; /* Declare as pointer */
	size_t len = 0;       /* Length of the line read */
	ssize_t read;

	pid_t pid;
	char *args[3];
	args[2] = NULL; /* Ensure the third element is NULL initially */

	while (1)
	{
		displayPrompt();

		/* Read a command from the user */
		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			/* Handle end of file (Ctrl+D) or error */
			perror("Error reading command");
			free(command); /* Free allocated memory */
			break;
		}

		/* Remove the newline character at the end */
		command[strcspn(command, "\n")] = '\0';

		/* Fork a new process */
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free(command); /* Free allocated memory */
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			/* Child process */
			/* Execute the command */
			args[0] = command;
			args[1] = command; /* Additional argument for execve */
			if (execve("/bin/sh", args, envp) == -1)
			{
				perror("execve");
				free(command); /* Free allocated memory */
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
				free(command); /* Free allocated memory */
				exit(EXIT_FAILURE);
			}

			/* Check if the child process terminated successfully */
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				fprintf(stderr, "Error: Command not found\n");
			}
		}
	}

	free(command); /* Free allocated memory */
	return 0;
}
