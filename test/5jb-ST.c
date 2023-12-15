#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "main.h"


/**
 * main - the main function
 * Return: Always 0
 */

int main(void)
{
	int i = 0;
	char *env_var;

	while ((env_var = environ[i++]) != NULL)
	{
		write(STDOUT_FILENO, env_var, strlen(env_var));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
