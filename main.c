#include <stdio.h>
#include <limits.h>

void vulnerableFunctionA(unsigned int a, unsigned int b) {
    unsigned int result = 0;
    int overflowFlag = 0;  // This flag is intended to be modified by overflow

    // Storing original values for later comparison
    unsigned int original_a = a;
    unsigned int original_b = b;

    // Adding the integers with the potential for overflow
    result = a + b;

    // Checking if overflowFlag has been altered due to overflow
    if (overflowFlag != 0) {
        printf("Overflow successfully executed! Variables were altered.\n");
    }

    // Showing the result of the addition
    printf("Result of %u + %u is %u\n", original_a, original_b, result);
}

int main() {
    int option;
    unsigned int a, b;

    printf("Enter an option followed by any necessary arguments: ");
    
    if (scanf("%d", &option) != 1) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    switch (option) {
        case 1:
            if (scanf("%u %u", &a, &b) != 2) {
                fprintf(stderr, "Error reading integers for option 1.\n");
                return 1;
            }
            vulnerableFunctionA(a, b);
            break;
        case 2:
            // Option 2 code here
            break;
        case 3:
            // Option 3 code here
            break;
        default:
            printf("Invalid option\n");
    }

    return 0;
}
