#include "main.h"
/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		displayPrompt();

		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			printError("Error reading command");
			free(command);
			break;
		}

		/* Remove the newline character at the end */
		command[strcspn(command, "\n")] = '\0';

		/* Handle exit command */
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}

		/* Execute the command */
		executeCommand(command);
	}

	free(command);
	return (EXIT_SUCCESS);
}
