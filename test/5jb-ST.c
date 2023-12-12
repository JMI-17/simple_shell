#include <stdio.h>
#include <unistd.h>

/**
 * main - function gets environment built-in
 *
 * Return: Always 0.
 */

extern char **environ;

int main(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
