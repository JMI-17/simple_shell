#include "main.h"

/* Function definitions */
void displayPrompt(void)
{
    write(1, "$\t", 2);
    fflush(stdout); /* Ensure the prompt is displayed immediately */
}
