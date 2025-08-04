#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024

int main() {
    char strata[256];
    char command[MAX_CMD_LEN];
    char full_cmd[MAX_CMD_LEN + 50];
    
    printf("Enter strata name!\n-> ");
    if (!fgets(strata, sizeof(strata), stdin)) {
        perror("Error reading input");
        return 1;
    }
    strata[strcspn(strata, "\n")] = 0; // Remove newline
    
    printf("You entered to %s!\n", strata);
    printf("To exit type 'exit'\n");
    
    while (1) {
        printf("%s$ ", strata);
        if (!fgets(command, sizeof(command), stdin)) {
            perror("Error reading command");
            continue;
        }
        command[strcspn(command, "\n")] = 0; // Remove newline
        
        if (strcmp(command, "exit") == 0) {
            break;
        }
        
        // Construct and execute command
        snprintf(full_cmd, sizeof(full_cmd), "strat %s sh -c '%s'", strata, command);
        int ret = system(full_cmd);
        
        if (ret == -1) {
            perror("Command execution failed");
        }
    }
    
    return 0;
}
