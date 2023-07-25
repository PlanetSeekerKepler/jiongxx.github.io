#include <stdio.h>

int main() {
    FILE *file;
    char buffer[16];
    
    // Open the .exe file in binary mode
    file = fopen("./modbus.exe", "rb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    
    // Read and print the binary data
    while (!feof(file)) {
        size_t bytesRead = fread(buffer, sizeof(char), sizeof(buffer), file);
        for (size_t i = 0; i < bytesRead; i++) {
            printf("%02X ", buffer[i] & 0xFF);
        }
        printf("\n");
    }
    
    // Close the file
    fclose(file);
    
    return 0;
}
