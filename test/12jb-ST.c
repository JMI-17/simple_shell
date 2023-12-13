#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void execute_command(const char *cmd) {
    char *command = strdup(cmd);
    char *token = strtok(command, "&|");
    int status;

    if (cmd == NULL || cmd[0] == '\0') {
        write(STDERR_FILENO, "Invalid command\n", 16);
        return;
    }

    if (command == NULL) {
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        return;
    }

    while (token != NULL) {
        if (strstr(token, "&&") != NULL) {
            char *cmd1 = strtok(token, "&");
            char *cmd2 = strtok(NULL, "&");

            if (cmd1 != NULL && cmd2 != NULL) {
                status = system(cmd1);
                if (status == 0) {
                    status = system(cmd2);
                }
            }
        } else if (strstr(token, "||") != NULL) {
            char *cmd1 = strtok(token, "|");
            char *cmd2 = strtok(NULL, "|");

            if (cmd1 != NULL && cmd2 != NULL) {
                status = system(cmd1);
                if (status != 0) {
                    status = system(cmd2);
                }
            }
        } else {
            int pipe_pos = strcspn(token, "|&");
            char* command = strndup(token, pipe_pos);
            status = system(command);
            free(command);
        }

        if (status != 0) {
            char error_msg[100];
            strcpy(error_msg, "Failed to execute command: ");
            strcat(error_msg, token);
            strcat(error_msg, "\n");
            write(STDERR_FILENO, error_msg, strlen(error_msg));
        }

        token = strtok(NULL, "&|");
    }

    free(command);
}

int main() {
    char input_commands[] = "command1 && command2 || command3";

    execute_command(input_commands);

    return 0;
}

