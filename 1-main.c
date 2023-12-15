#include "main.h"
/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
        char buffer[BUFFER_SIZE];
        char *args[2];
        pid_t child_pid;
        int status;

        while (1)
        {
                display_prompt();

                if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
                {
                        write(STDOUT_FILENO, "\n", 1);
                        break;
                }

                buffer[strcspn(buffer, "\n")] = '\0';

                child_pid = fork();

                if (child_pid == -1)
                {
                        perror("Error forking");
                        exit(EXIT_FAILURE);
                }

                if (child_pid == 0)
                {
                        args[0] = buffer;
                        args[1] = NULL;

                        if (execve(args[0], args, NULL) == -1)
                        {
                                char error_message[] = "Error executing command\n";
                                write(STDOUT_FILENO, error_message, sizeof(error_message) - 1);
                                _exit(EXIT_FAILURE);
                        }
                }
                else
                {
                        if (waitpid(child_pid, &status, 0) == -1)
                        {
                                char error_message[] = "Error waiting for child process\n";
                                write(STDOUT_FILENO, error_message, sizeof(error_message) - 1);
                                exit(EXIT_FAILURE);
                        }

                        if (WIFEXITED(status))
                        {
                                write_exit_status(WEXITSTATUS(status));
                        }
                        else if (WIFSIGNALED(status))
                        {
                                write_signal_message(WTERMSIG(status));
                        }
                }
        }

        return (0);
}
