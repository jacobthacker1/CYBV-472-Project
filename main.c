#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <shadow.h>
#include "ping.h"


typedef struct {
    char methodName[64];
    void (*func)(void);
}Action;

typedef struct{
    char username[64];
    char password[64];
    int isAuthenticated;
}User;
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

void vulnerableFunctionD()
{
    system("./ping google.com");

}
void evilFunction()
    //This code should "never" be run
{
    printf("Deleting all databases...");
}
void usefulFunction()
{
    int numCharacters;
    char generateChar;
    printf("Enter the number of characters to generate: ");
    scanf("%d", &numCharacters);
    printf("Enter the character to generate: ");
    while ((getchar()) != '\n');
    scanf("%c", &generateChar);
    printf("Generated characters: ");
    for (int i = 0; i < numCharacters; ++i) {
        printf("%c", generateChar);
    }
    printf("\n");

}
void exitFunction() {

    printf("Exiting the program. Goodbye!\n");
    exit(1);
}
void vulnerableFunctionE() 
{
    Action * actionPtr= (Action*) malloc(sizeof(Action));
    actionPtr->func = usefulFunction;
    printf("This program generates characters for you!\n");
    strcpy (actionPtr->methodName, "Character Generator");
    (*actionPtr->func)();
    strcpy (actionPtr->methodName, "Exit");
    actionPtr->func = exitFunction;
    free(actionPtr);
    char* coolWord = (char*) malloc(sizeof(Action));
    printf("What is your favorite word?\n");
    scanf("%s",coolWord); 
    printf("The coolest word is: %s\n", coolWord);
    (*actionPtr->func)(); 
}

void vulnerableFunctionF()
{
    User * currentUser = (User*) malloc(sizeof(User));
    currentUser->isAuthenticated = 0;
    char rootUsername[64] = "root";
    char rootPassword[64] = "tuturu";
    char userSelection;
    size_t length;

    while (1)
    {
        if (currentUser->isAuthenticated == 0)
        {
            printf("Enter the username: ");
            fgets(currentUser->username, sizeof(currentUser->username), stdin);
            length = strcspn(currentUser->username, "\n");
            if (currentUser->username[length] == '\n') {
                currentUser->username[length] = '\0';
            }

            printf("Enter the password for %s: ", currentUser->username);
            fgets(currentUser->password, sizeof(currentUser->password), stdin);
            length = strcspn(currentUser->password, "\n");
            if (currentUser->password[length] == '\n') {
                currentUser->password[length] = '\0';
            }

            if (strcmp(rootUsername, currentUser->username)==0 && strcmp(rootPassword, currentUser->password)==0)
            {
                printf("Successfully Authenticated as %s", currentUser->username);
                //login successful
                currentUser->isAuthenticated = 1; // Authenticate user.
            }
        }
        else
        {
            printf("You can perform the following actions: \n");
            printf("1. Ping test google.com\n");
            printf("2. View /etc/passwd\n");
            printf("3. View the /tmp directory\n");
            printf("4. Logout and exit\n");
            printf("5. Exit the program\n");
            scanf("%c", &userSelection);
            switch(userSelection)
            {
                case '1':
                    system("ping -c 4 google.com");
                    break;
                case '2':
                    system("cat /etc/passwd");
                    break;
                case '3':
                    system("ls /tmp");
                    break;
                case '4':
                    printf("Are you sure you want to logout and exit the program? (Y/N): ");
                    getchar();
                    scanf("%c", &userSelection);
                    free(currentUser); 
                    if (userSelection == 'n' || userSelection == 'N')
                    {
                        break;
                    }
                    if (userSelection == 'y' || userSelection == 'Y'){
                        printf("Logging out and exiting the program... ");
                        exit(1);
                    }
                    break;
                case '5':
                    exit(1);
                    break;
                default:
                    printf("Selection not implemented\n");
                    break;
            }
        }
    }
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
    printf("0 (Your Number 1-26) - Convert your number to the corresponding letter in the alphabet! IE A = 1, B = 2\n\
        1 (The message you want to echo) - Hello World Echo!  We shall echo your cheers!\n\
        2 (Length of Your words) (Your Words) - Place your words on the heap!\n\
        3 (Ping Test) - Test your network connectivity to google!\n\
        4 (Ping Utility) - Its great for network troubleshooting!\n\
        5 (Character Generator) - Generate text!\n\
        6 (Sysadmin tools) - A few utilities that may be handy!\n\
        \n");
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
                printf("\n[*] %c: calling vulnerableFunctionD\n", c);
                vulnerableFunctionD();
                break;
            case '4':
                printf("\n[*] %c: calling vulnerable ping utility\n", c);
                vulnerablePingUtility();
                break; 
            case '5':
                printf("\n[*] %c: calling vulnerableFunctionE\n", c);
                vulnerableFunctionE();
                break;
            case '6':
                printf("\n[*] %c: calling vulnerableFunctionF\n", c);
                vulnerableFunctionF();
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
