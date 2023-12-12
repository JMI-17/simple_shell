#include <stdio.h>
/**
 * main - Entry point of the program
 * @argc: The number of command-line arguments
 * @argv: An array containing the command-line arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
    /* Pointer to the current argument */
    char **currentArg = argv;

    /* Iterate through arguments until reaching the sentinel value (NULL) */
    while (*currentArg)
    {
        /* Print the current argument */
        printf("%s\n", *currentArg);

        /* Move to the next argument */
        currentArg++;
    }

    return 0;
}
