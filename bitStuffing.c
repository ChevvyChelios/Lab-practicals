#include <stdio.h>
#include <string.h>


int main() {
    char data[25], stuffedData[50];
    int i, count = 0, j = 0;
    
    printf("Enter the data: ");
    scanf("%s", data);
    int len = strlen(data);
    
    for(i = 0; i < len; i++) {
        if(data[i] == '1') {
            count++;
            stuffedData[j++] = data[i];
        } else {
            count = 0;
            stuffedData[j++] = data[i];
        }
        
        if(count == 5) {
            count = 0;
            stuffedData[j++] = '0';
        }
    }
    
    stuffedData[j] = '\0';
    printf("Data after bit stuffing: %s\n", stuffedData);
    return 0;
}