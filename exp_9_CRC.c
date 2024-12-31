#include <stdio.h>
#include <string.h>

#define N strlen(g)  // Length of generator polynomial

// Declare global variables
char t[50], cs[50], g[50];
int a, e, c;

// XOR function to perform XOR operation between checksum and generator
void xor() {
    for (c = 1; c < N; c++) {
        // Perform XOR operation. If both bits are same, result is "0", otherwise "1".
        cs[c] = ((cs[c] == g[c]) ? '0' : '1');
    }
}

// CRC function to compute the checksum
void crc() {
    for (e = 0; e < N; e++) {
        // Copy first N bits of data into checksum
        cs[e] = t[e];
    }

    do {
        if (cs[0] == '1') {
            // If first leftmost bit is 1, perform XOR operation
            xor();
        }
        
        // Shift the checksum and append the next bit from data
        for (c = 0; c < N - 1; c++) {
            cs[c] = cs[c + 1];
        }
        
        // Append the next bit from data to the checksum
        cs[c] = t[e++];
    } while (e <= a + N - 1);  // Continue the operation until all data is processed
}

int main() {
    // Input data
    printf("\nEnter the data: ");
    scanf("%s", t);  // Input the data (e.g., 1101011011)

    // Input generator polynomial
    printf("\nEnter the generator polynomial: ");
    scanf("%s", g);  // Input the generator polynomial (e.g., 10011)

    a = strlen(t);  // Length of the data

    // Append N-1 zeros to the data
    for (e = a; e < a + N - 1; e++) {
        t[e] = '0';
    }

    // Display modified data (data + appended zeros)
    printf("\nModified data is: %s", t);

    // Compute the checksum
    crc();

    // Display the checksum
    printf("\nChecksum is: %s", cs);

    // Append the checksum to the data to form the final codeword
    for (e = a; e < a + N - 1; e++) {
        t[e] = cs[e - a];
    }

    // Display the final codeword
    printf("\nThe final codeword is: %s", t);

    // Error detection
    printf("\nTest error detection: 0 for YES and 1 for NO: ");
    scanf("%d", &e);  // Input to test error detection

    if (e == 0) {  // If user wants to simulate error
        do {
            printf("\nEnter the position where error is to be inserted: ");
            scanf("%d", &e);  // Input the position of the error
        } while (e == 0 || e > a + N - 1);  // Ensure valid position

        // Flip the bit at the specified position to simulate error
        t[e - 1] = (t[e - 1] == '0') ? '1' : '0';
        printf("\nErroneous data: %s\n", t);
    }

    // Recompute checksum for the modified data (with error)
    crc();

    // Check if checksum contains '1' indicating error detection
    for (e = 0; (e < N - 1) && (cs[e] != '1'); e++);
    if (e < N - 1) {
        printf("\nError detected\n\n");
    } else {
        printf("\nNo error detected\n\n");
    }

    return 0;
}
