#include <stdio.h>
#include <limits.h>
#include "ping.h"

char destinationIP[300];

void vulnerableFunctionA(char Z0x) {
    int _xZ = 0, __x_Z = 25, Z_x_ = 1, x_Z_ = Z0x - 1; 
    char x0x0[] = "??????????????????????????????????????????????????????????????????????????????", 
         Z00Z[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("%c\n", *&Z00Z[x_Z_ < __x_Z ? x_Z_ : __x_Z]);
    if(((_xZ + Z_x_ - Z_x_ != _xZ) || (Z0x < Z_x_ || Z0x > __x_Z + Z_x_) || (_xZ == Z_x_))){
        printf("Wow.\n");
    }
}

void vulnerableFunctionB(char* str) {
    char cmd[350], *echo = "echo %s", *ptr = cmd; 
    int i = 0;
    while (echo[i]) {
        ptr[i] = echo[i];
        i++;
    }
    ptr[i++] = ' ';
    while (*str) {
        if (i < 349) {
            ptr[i++] = *str++;
        } else {
            break;
        }
    }
    ptr[i] = '\0';
    system(cmd); 
}


void vulnerableFunctionC(char *W2x) {
    int x2W = atoi(W2x); 
    if (x2W <= 0) {
        fprintf(stderr, "Invalid buffer size.\n");
        return;
    }

    char *xWx = (char *)malloc(x2W); 
    if (!xWx) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return;
    }
    char *xWxover = (char *)malloc(x2W); 
    if (!xWxover) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return;
    }

    char *xWX = xWx;
    while (*W2x && (*W2x < '0' || *W2x > '9')) {
        W2x++; 
    }
    while (*W2x && (xWX - xWx) < strlen(W2x) - 1) {
        *xWX++ = *W2x++; 
    }
    *xWX = '\0'; 

    printf("You placed:\n%s\n", xWx);
    printf("ON THE HEAP!!!\n");
    if(strlen(W2x) > x2W){
        printf("Wow! : %s\n", xWxover);
    }
    free(xWx);
}

void vulnerablePingUtility()
{
    printf("Ping Utility: Please enter the destination IP address:\n");
    scanf("%s", destinationIP);
    char *tempDest = destinationIP;
    printf("You have entered address:\n");
    printf(destinationIP);
    printf("\n\n");
    ping(2, &tempDest);
}

int main(int argc, char **argv) {
    char *fgets_ret;
    char input_buffer[300] = {0};
    char c;
    printf("Command Usage -----------------  Description\n");
    printf("0 (Your Number 1-26) - Convert your number to the corresponding letter in the alphabet! IE A = 1, B = 2\n1 (The message you want to echo) - Hello World Echo!  We shall echo your cheers!\n2 (Length of Your words) (Your Words) - Place your words on the heap!\n6 (Ping Utility) - Its great for network troubleshooting!\n");
    printf("[?] Input: ");
    fgets_ret = fgets(input_buffer, sizeof(input_buffer), stdin);

    // Ensure this program is executed with root privs
    if (getuid() != 0) {
    fprintf(stderr, "This program requires root priveleges, please run with sudo. Trust us its safe.\n");
    exit(EXIT_FAILURE);
    }

    if (fgets_ret != NULL) {
        c = input_buffer[0];
        switch(c) {
            case '0':
                printf("\n[*] %c: calling vulnerableFunctionA()\n", c);
                vulnerableFunctionA(input_buffer[2] - '0');
                break;
            case '1':
                printf("\n[*] %c: calling vulnerableFunctionB()\n", c);
                vulnerableFunctionB(input_buffer + 2);
                break;
            case '2':
                printf("\n[*] %c: calling vulnerableFunctionC()\n", c);
                vulnerableFunctionC(input_buffer + 2);
                break;
            case '3':
                // Option 3 code here
                break;
            case '6':
                printf("\n[*] %c: calling vulnerable ping utility\n", c);
                vulnerablePingUtility();
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

// 9 vulnerabilities have been officially inserted into this program. Happy hunting ;)
