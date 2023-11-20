#include <stdio.h>
#include <limits.h>

void vulnerableFunctionA(char a) {
    char overflow[] = "??????????????????????????????????????????????????????????????????????????????";
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("%c\n", letters[a - 1]);
    if(a < 0 || a > 26){
        printf("Integer Overflow Detected, a ? means you have printed from our super secret overflow array.  NOOOOOOO! D': \n");
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
                // Option 1 code here
                break;
            case '2':
                // Option 2 code here
                break;
            case '3':
                // Option 3 code here
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
