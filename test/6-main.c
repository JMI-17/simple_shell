#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int main()
{
	char *line;

	while ((line = custom_getline()) != NULL)
	{
		int i = 0;
		while (line[i] != '\0')
		{
			write(STDOUT_FILENO, &line[i], 1);
			++i;
		}
		write(STDOUT_FILENO, "\n", 1);
		free(line);
	}
	return (0);
}
