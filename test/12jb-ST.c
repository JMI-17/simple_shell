#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

void execute_command(const char *cmd)
{
	char *command = strdup(cmd);
	char *token = strtok(command, ";");
	int status;
        int execute_next_command = 1;

    if (cmd == NULL || cmd[0] == '\0') {
        fprintf(stderr, "Invalid command\n");
        return;
    }

    
    if (command == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    

    while (token != NULL)
    {
        if (strstr(token, "&&") != NULL) {
            char *cmd1 = strtok(token, "&&");
            char *cmd2 = strtok(NULL, "&&");

            if (cmd1 != NULL && cmd2 != NULL) {
                status = system(cmd1);
                if (status != 0) {
                    execute_next_command = 0;
                } else {
                    status = system(cmd2);
                }
            }
        } else if (strstr(token, "||") != NULL) {
            char *cmd1 = strtok(token, "||");
            char *cmd2 = strtok(NULL, "||");

            if (cmd1 != NULL && cmd2 != NULL) {
                status = system(cmd1);
                if (status == 0) {
                    execute_next_command = 0;
                } else {
                    status = system(cmd2);
                }
            }
        } else {
            status = system(token);
        }

        if (status != 0) {
            fprintf(stderr, "Failed to execute command: %s\n", token);
        }

        if (!execute_next_command) {
            break;
        }

        token = strtok(NULL, ";");
    }

    free(command);
}

int main() {
    char input_commands[] = "command1 && command2 || command3";

    execute_command(input_commands);

    return (0);
}

