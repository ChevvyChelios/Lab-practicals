#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

// Function to perform binary division (CRC)
void crc(char tdata[], char divisor[], char remainder[]) {
    int dataLen = strlen(tdata);
    int divisorLen = strlen(divisor);
    int i, j;

    strncpy(remainder, tdata, divisorLen); // Copy initial bits

    for (i = divisorLen; i <= dataLen; i++) {
        if (remainder[0] == '1') { 
            for (j = 1; j < divisorLen; j++) 
                remainder[j] = (remainder[j] == divisor[j]) ? '0' : '1';
        }

        for (j = 0; j < divisorLen - 1; j++) 
            remainder[j] = remainder[j + 1];
        remainder[divisorLen - 1] = (i < dataLen) ? tdata[i] : '0';
    }
}

// Function to generate transmitted data with CRC
void generateCRC(char data[], char divisor[], char transmitted[]) {
    char remainder[MAX_SIZE], tempData[MAX_SIZE];
    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);
    int i;

    // Copy original data to temporary buffer
    strcpy(tempData, data);

    // Append correct number of zeros (key length - 1)
    for (i = 0; i < divisorLen - 1; i++)
        strcat(tempData, "0");

    crc(tempData, divisor, remainder);

    // Correctly construct transmitted message
    strcpy(transmitted, data);  // Use original data
    strncat(transmitted, remainder, divisorLen - 1); // Append only correct remainder length

    printf("Transmitted data (with CRC): %s\n", transmitted);
}


// Function to check for errors in received data
void checkTransmission(char transmitted[], char divisor[]) {
    char remainder[MAX_SIZE];
    int i, error = 0;

    crc(transmitted, divisor, remainder);

    for (i = 0; i < strlen(divisor) - 1; i++) {
        if (remainder[i] != '0') {
            error = 1;
            break;
        }
    }

    if (error)
        printf("Error detected in received data!\n");
    else
        printf("No errors detected. Data is intact.\n");
}

int main() {
    char data[MAX_SIZE], key[MAX_SIZE], transmitted[MAX_SIZE];

    printf("Enter original data bits: ");
    scanf("%s", data);

    printf("Enter generator polynomial (key): ");
    scanf("%s", key);

    generateCRC(data, key, transmitted);

    printf("Enter received data bits: ");
    scanf("%s", transmitted);

    checkTransmission(transmitted, key);

    return 0;
}