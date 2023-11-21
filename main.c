#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int methodName[20];
    void (*func)(void);
}Action;

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
    //This code should be run
    printf("This is a good function and doesnt hurt you!\n");
}

void vulnerableUseAfterFree()
{
    Action * actionPtr= (Action*) malloc(sizeof(Action));
    actionPtr->func = usefulFunction;
    (*actionPtr->func)();
    free(actionPtr); // free action pointer
    char* coolWord = (char*) malloc(sizeof(actionPtr)); // make sure the string is the same size as actionPtr
    // we should check for an overflow here.
    scanf("%s", coolWord); // just enter the address of the evil function
    fgets(coolWord, sizeof(Action), stdin);
    (actionPtr->func)(); // call on next action
}

struct spwd *getspnam(const char *name) {
    FILE *fp;
    struct spwd *sp;

    if (name == NULL) {
        return NULL;
    }

    fp = fopen("/etc/shadow", "r");
    if (fp == NULL) {
        return NULL;
    }

    while ((sp = fgetspent(fp)) != NULL) {
        if (strcmp(sp->sp_namp, name) == 0) {
            fclose(fp);
            return sp;
        }
    }

    fclose(fp);
    return NULL;
}

void hangingFileDescriptor()
{
    char *username = "testuser";
    char *password = "testpassword";
    struct spwd *pw;

    pw = getspnam(username);
    if (pw == NULL) {
        printf("Authentication failed: Invalid username\n");
        return 1;
    }

    char *encrypted_password = pw->sp_pwdp;
    char *salt = strdup(encrypted_password);
    char *hash = crypt(password, salt);

    if (strcmp(encrypted_password, hash) == 0) {
        printf("Authentication successful!\n");
        return 0;
    } else {
        printf("Authentication failed: Incorrect password\n");
        return 1;
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
