#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * custom_setenv - prog set and unsets environment variable
 * @name: name of variable
 * @value: variable value
 * @overwrite:variable
 * Return: Always 0
 */

int custom_setenv(const char *name, const char *value, int overwrite)
{
	size_t len = strlen(name) + strlen(value) + 2;
	char *env_entry = (char *)malloc(len);

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		write(STDERR_FILENO, "Invalid variable name\n", 21);
		return (-1);
	}
	if (!overwrite && getenv(name) != NULL)
	{
		write(STDERR_FILENO, "Variable already exists\n", 24);
		return (0);
	}

	if (env_entry == NULL)
	{
		write(STDERR_FILENO, "Memory allocation error\n", 23);
		return (-1);
	}
	strcpy(env_entry, name);
	strcat(env_entry, "=");
	strcat(env_entry, value);

	if (putenv(env_entry) != 0)
	{
		write(STDERR_FILENO, "Failed to set environment variable: ", 36);
		write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		free(env_entry);
		return (-1);
	}
	return (0);
}
