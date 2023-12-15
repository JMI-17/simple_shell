#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

#define BUFFER_SIZE 128


/**
 * custom_getline - prog prints a line
 * Return: Always 0
 */

char *custom_getline()
{
	char *line = NULL;
	int size = 0, capacity = BUFFER_SIZE;
	char c;
	int bytes_read = read(STDIN_FILENO, &c, 1);
	int lineNotNull = line != NULL;
	int sizeLessCapacity = size < capacity - 1;

	while (1)
	{
		if (bytes_read <= 0)
		{
			if (lineNotNull && sizeLessCapacity)
			{
				line[size++] = '\0';
				return (line);
			}
			if (line != NULL)
			{
				return (NULL);
			}
			return (NULL);
		}
		if (!lineNotNull || !sizeLessCapacity || !(line[size++] = c))
		{
			int lineNotNull = line != NULL;
			if (!lineNotNull)
			{
				return (NULL);
			}
			capacity *= 2;
			char *temp = realloc(line, capacity);
			
			if (temp == NULL)
			{
				free(line);
				return (NULL);
			}
			line = temp;
		}
	}
}
