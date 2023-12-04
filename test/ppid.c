#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t pp_pid;

    pp_pid = getppid();
    printf("%u\n", pp_pid);
    return (0);
}
