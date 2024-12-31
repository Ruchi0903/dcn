#include<stdio.h>

int data[4], encoded[7], edata[7], syn[3];
int gmatrix[4][7] = {
    {0,1,1,1,0,0,0}, 
    {1,0,1,0,1,0,0}, 
    {1,1,0,0,0,1,0}, 
    {1,1,1,0,0,0,1}
};
int hmatrix[3][7] = {
    {1,0,0,0,1,1,1}, 
    {0,1,0,1,0,1,1}, 
    {0,0,1,1,1,0,1}
};

int main() {
    int i, j;

    // Input original data bits
    printf("Hamming Code encoding\n");
    printf("Enter the 4 bit data (one by one): \n");
    for (i = 0; i < 4; i++) 
        scanf("%d", &data[i]);

    // Print the generator matrix
    printf("Generator Matrix\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            printf("%d", gmatrix[i][j]);
        }
        printf("\n");
    }

    // Generate encoded data using the generator matrix
    printf("\n\nEncoded data : ");
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 4; j++) 
            encoded[i] ^= (data[j] * gmatrix[j][i]);  // bitwise XOR
        printf("%d", encoded[i]);
    }

    // Decode and check for errors
    printf("\n\nHamming Code Decoding \n\n");
    printf("Enter the encoded bit received (one by one):\n");
    for (i = 0; i < 7; i++) 
        scanf("%d", &edata[i]);

    // Compute the syndrome using the H matrix
    printf("Syndrome = ");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) 
            syn[i] ^= (edata[j] * hmatrix[i][j]);
        printf("%d", syn[i]);
    }

    // Check for errors
    for (j = 0; j <= 7; j++) {
        if (syn[0] == hmatrix[0][j] && 
            syn[1] == hmatrix[1][j] && 
            syn[2] == hmatrix[2][j]) 
            break;
    }

    if (j == 7) 
        printf("\n\nThe code is error-free\n");
    else {
        printf("\n\nError Received at bit no %d of the data\n\n", j + 1);
        edata[j] = !edata[j];  // Correct the error
        printf("The correct data should be : ");
        for (i = 0; i < 7; i++) 
            printf("%d", edata[i]);
    }
    printf("\n\n");
    return 0;
}
