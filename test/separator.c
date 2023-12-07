#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

void execute_command(const char *cmd)
{
	char *command = strdup(cmd);
	char *token = strtok(command, ";");

    if (cmd == NULL || cmd[0] == '\0') {
        fprintf(stderr, "Invalid command\n");
        return;
    }

    
    if (command == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    
    while (token != NULL) {
        if (system(token) != 0) {
            fprintf(stderr, "Failed to execute command: %s\n", token);
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

