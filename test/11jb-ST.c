#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute_command(const char *cmd)
{
    char *command = strdup(cmd);
    char *token = strtok(command, ";");

    if (cmd == NULL || cmd[0] == '\0') {
        write(STDERR_FILENO, "Invalid command\n", 16);
        return;
    }

    if (command == NULL) {
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        return;
    }

    while (token != NULL) {
        if (system(token) != 0) {
            char error_msg[100];
            strcpy(error_msg, "Failed to execute command: ");
            strcat(error_msg, token);
            strcat(error_msg, "\n");
            write(STDERR_FILENO, error_msg, strlen(error_msg));
        }
        token = strtok(NULL, ";");
    }

    free(command);
}

int main() {
    char input_commands[] = "command1;command2;command3";

    execute_command(input_commands);

    return (0);
}

