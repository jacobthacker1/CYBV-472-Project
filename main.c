#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

void vulnerableFunctionA(char a) {
    char overflow[] = "??????????????????????????????????????????????????????????????????????????????";
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("%c\n", letters[a - 1]);
    if(a < 0 || a > 26){
        printf("Integer Overflow Detected, a ? means you have printed from our super secret overflow array.  NOOOOOOO! D': \n");
    }
}

void vulnerableCommandExecution(char* input) {
    char command[350];
    snprintf(command, sizeof(command), "echo %s", input);
    system(command);
}

void vulnerableHeapOverflow(char *userInput) {
    // Allocate a fixed-size buffer on the heap
    char *buffer = (char *)malloc(100 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return;
    }
    char *overflow = (char *)malloc(100 * sizeof(char));
    if (overflow == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
    }
    // Copy user input into the buffer without bounds checking
    strcpy(buffer, userInput);

    printf("You entered: %s\n", buffer);
    if(strlen(userInput) > 100){
        printf("You also overflowed! : %s\n", overflow);
    }
    // Free the buffer
    free(buffer);
    free(overflow);
}

void vulnerablePing()
{
    // if the ping file is replaced with, malware, you can execute malware with root permissions
    system("./ping");
}

int main(int argc, char **argv) {
    char *fgets_ret;
    char input_buffer[300] = {0};
    char c;

    printf("[?] Input: ");
    fgets_ret = fgets(input_buffer, sizeof(input_buffer), stdin);

    if (fgets_ret != NULL) {
        c = input_buffer[0];
        switch(c) {
            case '0':
                printf("\n[*] %c: calling vulnerableFunctionA()\n", c);
                vulnerableFunctionA(input_buffer[2] - '0');
                break;
            case '1':
                printf("\n[*] %c: calling vulnerableCommandExecution()\n", c);
                vulnerableCommandExecution(input_buffer + 2);
                break;
            case '2':
                printf("\n[*] %c: calling vulnerableHeapOverflow()\n", c);
                vulnerableHeapOverflow(input_buffer + 2);
                break;
            case '3':
                // Option 3 code here
                printf("\n[*] %c: calling vulnerablePing\n", c);
                vulnerablePing();
                break;
            default:
                printf("\n[!] Selection %c not implemented\n", c);
                break;
        }
    } else {
        printf("\n[!] Error reading input\n");
    }

    printf("[*] Done!\n");

    return 0;
}
