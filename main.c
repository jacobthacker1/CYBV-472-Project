#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <shadow.h>


typedef struct {
    char methodName[64];
    void (*func)(void);
}Action;

typedef struct{
    char username[64];
    char password[64];
    int isAuthenticated;
}User;

void vulnerableFunctionA(char a) {
    char overflow[] = "??????????????????????????????????????????????????????????????????????????????";
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; printf("%c\n", letters[a - 1]);
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
    // if the ping file is replaced with malware, you can execute malware with root permissions
    system("./ping");
}

void vulnerableFormatString()
{
  char* username = "Administrator";
  //char* password = "un3xploi+a6LePa55w0rd";
  char* password = "passsword"; //weaker password for testing
  char userInputUsername [100];
  char userInputPassword [100];
  printf("Enter your username:\n");
  scanf("%s", userInputUsername);
  printf("Enter the password for ");
  printf(username);
  printf("\n");
  scanf("%s", userInputPassword);
  if (strncmp(username, userInputUsername, sizeof(username)) == 0 &&
      strncmp(password, userInputPassword, sizeof(password)) == 0)
  {
    printf("Login Successful\n");
  }
  else
  {
    printf("Login Failure, Incorrect Credentials\n");
  }
}
void evilFunction()
{
    //This code should "never" be run
    printf("Deleting all databases...");
}
void usefulFunction()
{
    int numCharacters;
    char generateChar;
    // Ask the user for input
    printf("Enter the number of characters to generate: ");
    scanf("%d", &numCharacters);
    // Clear the input buffer
    while ((getchar()) != '\n');
    printf("Enter the character to generate: ");
    scanf("%c", &generateChar);
    // Generate and print the specified number of characters
    printf("Generated characters: ");
    for (int i = 0; i < numCharacters; ++i) {
        printf("%c", generateChar);
    }
    printf("\n");

}

// Function definitions
void exitFunction() {
    printf("Exiting the program. Goodbye!\n");
    exit(1);
}

void vulnerableUseAfterFree()
{
    Action * actionPtr= (Action*) malloc(sizeof(Action));
    actionPtr->func = usefulFunction;
    strcpy (actionPtr->methodName, "Character Generator");
    printf("This program generates characters for you!\n");
    (*actionPtr->func)();
    strcpy (actionPtr->methodName, "Exit");
    free(actionPtr);
    actionPtr->func = exitFunction;
    char* coolWord = (char*) malloc(sizeof(Action)); // make sure the string is the same size as actionPtr
    printf("What is your favorite word?\n");
    scanf("%s",coolWord); //buffer overflow and use after free
    printf("The coolest word is: %s\n", coolWord);
    (*actionPtr->func)(); // run exit function
}

void vulnerableDoubleFree()
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
            //remove newline from username
            length = strcspn(currentUser->username, "\n");
            if (currentUser->username[length] == '\n') {
                currentUser->username[length] = '\0';
            }

            printf("Enter the password for %s: ", currentUser->username);
            fgets(currentUser->password, sizeof(currentUser->password), stdin);
            //remove newline from password
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
                    free(currentUser); // since it frees before log out is confirmed, we can deny logout and free again.
                    scanf("%c", &userSelection);
                    if (userSelection == 'n' || userSelection == 'N')
                        break;
                    if (userSelection == 'y' || userSelection == 'Y'){
                        free(currentUser);
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
                printf("\n[*] %c: calling vulnerablePing\n", c);
                vulnerablePing();
                break;
            case '4':
                //calculate average of percentages
                printf("\n[*] %c: calling vulnerableFormatString\n", c);
                vulnerableFormatString();
                break;
            case '5':
                printf("\n[*] %c: calling vulnerableUseAfterFree\n", c);
                vulnerableUseAfterFree();
                break;
            case '6':
                printf("\n[*] %c: calling vulnerableDoubleFree\n", c);
                vulnerableDoubleFree();
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
