#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Utility functions */
void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i]))
            str[i] = toupper(str[i]);
    }
}

void removeSpaces(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (mod(a * x, m) == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

/* Monoalphabetical Substitution Ciphers */

/* 1. Atbash Cipher */
void atbashCipher(char *text) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                text[i] = 'Z' - (text[i] - 'A');
            else
                text[i] = 'z' - (text[i] - 'a');
        }
    }
}

/* 2. Caesar Cipher */
void caesarCipher(char *text, int shift) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = ((text[i] - base + shift) % 26) + base;
        }
    }
}

/* 3. Affine Cipher */
void affineCipherEncrypt(char *text, int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime to 26.\n");
        return;
    }
    
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = ((a * (text[i] - base) + b) % 26) + base;
        }
    }
}

void affineCipherDecrypt(char *text, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: 'a' must be coprime to 26.\n");
        return;
    }
    
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (mod(a_inv * (text[i] - base - b), 26)) + base;
        }
    }
}

/* Polyalphabetical Substitution Ciphers */

/* 1. Vigenere Cipher */
void vigenereCipherEncrypt(char *text, char *key) {
    int keyLen = strlen(key);
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLen]) - 'A';
            text[i] = ((text[i] - base + keyChar) % 26) + base;
        }
    }
}

void vigenereCipherDecrypt(char *text, char *key) {
    int keyLen = strlen(key);
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLen]) - 'A';
            text[i] = ((text[i] - base - keyChar + 26) % 26) + base;
        }
    }
}

/* 2. Gronsfeld Cipher */
void gronsfeldCipherEncrypt(char *text, char *key) {
    int keyLen = strlen(key);
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int keyDigit = key[i % keyLen] - '0';
            text[i] = ((text[i] - base + keyDigit) % 26) + base;
        }
    }
}

void gronsfeldCipherDecrypt(char *text, char *key) {
    int keyLen = strlen(key);
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int keyDigit = key[i % keyLen] - '0';
            text[i] = ((text[i] - base - keyDigit + 26) % 26) + base;
        }
    }
}

/* 3. Beaufort Cipher */
void beaufortCipher(char *text, char *key) {
    int keyLen = strlen(key);
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLen]);
            text[i] = ((keyChar - text[i] + 26) % 26) + 'A';
        }
    }
}

/* 4. Autokey Cipher */
void autokeyCipherEncrypt(char *text, char *key) {
    int keyLen = strlen(key);
    char *fullKey = (char *)malloc(strlen(text) + 1);
    int i;
    
    strcpy(fullKey, key);
    
    for (i = 0; i < strlen(text); i++) {
        if (i >= keyLen && isalpha(text[i - keyLen])) {
            fullKey[i] = text[i - keyLen];
        }
        
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(fullKey[i]) - 'A';
            text[i] = ((text[i] - base + keyChar) % 26) + base;
        }
    }
    
    free(fullKey);
}

void autokeyCipherDecrypt(char *text, char *key) {
    int keyLen = strlen(key);
    char *fullKey = (char *)malloc(strlen(text) + 1);
    char *originalText = (char *)malloc(strlen(text) + 1);
    strcpy(originalText, text);
    int i;
    
    strcpy(fullKey, key);
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(fullKey[i]) - 'A';
            originalText[i] = ((text[i] - base - keyChar + 26) % 26) + base;
            
            if (i >= keyLen) {
                fullKey[i] = originalText[i - keyLen];
            }
        }
    }
    
    strcpy(text, originalText);
    free(fullKey);
    free(originalText);
}

/* 5. Running Key Cipher */
void runningKeyCipherEncrypt(char *text, char *bookText) {
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(bookText[i]) - 'A';
            text[i] = ((text[i] - base + keyChar) % 26) + base;
        }
    }
}

void runningKeyCipherDecrypt(char *text, char *bookText) {
    int i;
    
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(bookText[i]) - 'A';
            text[i] = ((text[i] - base - keyChar + 26) % 26) + base;
        }
    }
}

/* Polygraphic Substitution Ciphers */

/* 1. Hill Cipher for 2x2 matrix */
void hillCipherEncrypt(char *text, int key[2][2]) {
    int len = strlen(text);
    if (len % 2 != 0) {
        strcat(text, "X"); // Padding if needed
        len++;
    }
    
    for (int i = 0; i < len; i += 2) {
        if (isalpha(text[i]) && isalpha(text[i + 1])) {
            int p1 = toupper(text[i]) - 'A';
            int p2 = toupper(text[i + 1]) - 'A';
            
            int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
            int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;
            
            text[i] = c1 + 'A';
            text[i + 1] = c2 + 'A';
        }
    }
}

int determinant2x2(int matrix[2][2]) {
    return mod((matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]), 26);
}

void cofactorMatrix2x2(int matrix[2][2], int cofactor[2][2]) {
    cofactor[0][0] = matrix[1][1];
    cofactor[0][1] = -matrix[0][1];
    cofactor[1][0] = -matrix[1][0];
    cofactor[1][1] = matrix[0][0];
}

void hillCipherDecrypt(char *text, int key[2][2]) {
    int det = determinant2x2(key);
    int detInv = modInverse(det, 26);
    
    if (detInv == -1) {
        printf("Error: The key matrix is not invertible\n");
        return;
    }
    
    int cofactor[2][2];
    cofactorMatrix2x2(key, cofactor);
    
    // Adjugate
    int adj[2][2];
    adj[0][0] = mod(cofactor[0][0], 26);
    adj[0][1] = mod(cofactor[0][1], 26);
    adj[1][0] = mod(cofactor[1][0], 26);
    adj[1][1] = mod(cofactor[1][1], 26);
    
    // Inverse = adjugate * determinant^-1
    int keyInv[2][2];
    keyInv[0][0] = mod(adj[0][0] * detInv, 26);
    keyInv[0][1] = mod(adj[0][1] * detInv, 26);
    keyInv[1][0] = mod(adj[1][0] * detInv, 26);
    keyInv[1][1] = mod(adj[1][1] * detInv, 26);
    
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        if (isalpha(text[i]) && isalpha(text[i + 1])) {
            int c1 = toupper(text[i]) - 'A';
            int c2 = toupper(text[i + 1]) - 'A';
            
            int p1 = mod((keyInv[0][0] * c1 + keyInv[0][1] * c2), 26);
            int p2 = mod((keyInv[1][0] * c1 + keyInv[1][1] * c2), 26);
            
            text[i] = p1 + 'A';
            text[i + 1] = p2 + 'A';
        }
    }
}

/* Transpositional Ciphers */

/* 1. Rail Fence Cipher */
void railFenceCipherEncrypt(char *text, int rails) {
    int len = strlen(text);
    char fence[rails][len];
    
    // Initialize the fence with empty spaces
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            fence[i][j] = '\0';
        }
    }
    
    int row = 0;
    int dir = 1; // 1 for down, -1 for up
    
    // Fill the fence
    for (int i = 0; i < len; i++) {
        fence[row][i] = text[i];
        
        // Change direction when we hit the boundary
        if (row == 0) {
            dir = 1;
        } else if (row == rails - 1) {
            dir = -1;
        }
        
        row += dir;
    }
    
    // Read off the fence
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (fence[i][j] != '\0') {
                text[index++] = fence[i][j];
            }
        }
    }
    text[index] = '\0';
}

void railFenceCipherDecrypt(char *text, int rails) {
    int len = strlen(text);
    char fence[rails][len];
    
    // Initialize the fence with empty spaces
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            fence[i][j] = '\0';
        }
    }
    
    // Mark positions where letters will be placed
    int row = 0;
    int dir = 1;
    for (int i = 0; i < len; i++) {
        fence[row][i] = '*'; // Mark the position
        
        if (row == 0) {
            dir = 1;
        } else if (row == rails - 1) {
            dir = -1;
        }
        
        row += dir;
    }
    
    // Fill the marked positions with ciphertext
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (fence[i][j] == '*') {
                fence[i][j] = text[index++];
            }
        }
    }
    
    // Read off in zig-zag order
    index = 0;
    row = 0;
    dir = 1;
    for (int i = 0; i < len; i++) {
        text[index++] = fence[row][i];
        
        if (row == 0) {
            dir = 1;
        } else if (row == rails - 1) {
            dir = -1;
        }
        
        row += dir;
    }
    text[index] = '\0';
}

/* 2. Route Cipher (simple spiral implementation) */
void routeCipherEncrypt(char *text, int rows, int cols) {
    int len = strlen(text);
    char matrix[rows][cols];
    int index = 0;
    
    // Fill the matrix row by row
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < len) {
                matrix[i][j] = text[index++];
            } else {
                matrix[i][j] = 'X'; // Padding
            }
        }
    }
    
    // Read in spiral order (clockwise, starting from top-right)
    index = 0;
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    
    while (top <= bottom && left <= right) {
        // Move right
        for (int i = left; i <= right; i++) {
            text[index++] = matrix[top][i];
        }
        top++;
        
        // Move down
        for (int i = top; i <= bottom; i++) {
            text[index++] = matrix[i][right];
        }
        right--;
        
        // Move left
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                text[index++] = matrix[bottom][i];
            }
            bottom--;
        }
        
        // Move up
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                text[index++] = matrix[i][left];
            }
            left++;
        }
    }
    
    text[len] = '\0';
}

void routeCipherDecrypt(char *text, int rows, int cols) {
    int len = strlen(text);
    char matrix[rows][cols];
    char result[len + 1];
    
    // Initialize matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = ' ';
        }
    }
    
    // Fill the matrix in spiral order
    int index = 0;
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    
    while (top <= bottom && left <= right && index < len) {
        // Move right
        for (int i = left; i <= right && index < len; i++) {
            matrix[top][i] = text[index++];
        }
        top++;
        
        // Move down
        for (int i = top; i <= bottom && index < len; i++) {
            matrix[i][right] = text[index++];
        }
        right--;
        
        // Move left
        if (top <= bottom) {
            for (int i = right; i >= left && index < len; i--) {
                matrix[bottom][i] = text[index++];
            }
            bottom--;
        }
        
        // Move up
        if (left <= right) {
            for (int i = bottom; i >= top && index < len; i--) {
                matrix[i][left] = text[index++];
            }
            left++;
        }
    }
    
    // Read the matrix row by row
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != ' ' && matrix[i][j] != 'X') {
                result[index++] = matrix[i][j];
            }
        }
    }
    result[index] = '\0';
    
    strcpy(text, result);
}

/* 3. Columnar Transposition Cipher */
void columnarTranspositionEncrypt(char *text, char *key) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    
    // Create a matrix to store the plaintext
    int rows = ceil((double)textLen / keyLen);
    char matrix[rows][keyLen];
    
    // Initialize matrix with placeholders
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            matrix[i][j] = ' ';
        }
    }
    
    // Fill the matrix row by row
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            if (index < textLen) {
                matrix[i][j] = text[index++];
            }
        }
    }
    
    // Determine the order of columns
    int order[keyLen];
    for (int i = 0; i < keyLen; i++) {
        order[i] = i;
    }
    
    // Sort columns based on key
    for (int i = 0; i < keyLen - 1; i++) {
        for (int j = i + 1; j < keyLen; j++) {
            if (key[order[i]] > key[order[j]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    
    // Read off column by column as per the key order
    index = 0;
    for (int i = 0; i < keyLen; i++) {
        for (int j = 0; j < rows; j++) {
            if (matrix[j][order[i]] != ' ') {
                text[index++] = matrix[j][order[i]];
            }
        }
    }
    text[index] = '\0';
}

void columnarTranspositionDecrypt(char *text, char *key) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    
    // Calculate number of rows
    int rows = ceil((double)textLen / keyLen);
    int lastRowCols = textLen % keyLen;
    if (lastRowCols == 0) lastRowCols = keyLen;
    
    // Determine the order of columns
    int order[keyLen];
    for (int i = 0; i < keyLen; i++) {
        order[i] = i;
    }
    
    // Sort columns based on key
    for (int i = 0; i < keyLen - 1; i++) {
        for (int j = i + 1; j < keyLen; j++) {
            if (key[order[i]] > key[order[j]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    
    // Create a matrix to store the ciphertext
    char matrix[rows][keyLen];
    
    // Initialize matrix with placeholders
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            matrix[i][j] = ' ';
        }
    }
    
    // Calculate column lengths
    int colLengths[keyLen];
    for (int j = 0; j < keyLen; j++) {
        colLengths[j] = rows;
        if (j >= lastRowCols && lastRowCols > 0) {
            colLengths[j]--;
        }
    }
    
    // Fill the matrix column by column
    int index = 0;
    for (int i = 0; i < keyLen; i++) {
        for (int j = 0; j < colLengths[order[i]]; j++) {
            matrix[j][order[i]] = text[index++];
        }
    }
    
    // Read off row by row
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            if (matrix[i][j] != ' ') {
                text[index++] = matrix[i][j];
            }
        }
    }
    text[index] = '\0';
}

int main() {
    char option[10];
    char text[1000], key[100];
    int shift, a, b, rails, rows, cols;
    int hillKey[2][2];
    
    while (1) {
        printf("\nCryptography Algorithms\n");
        printf("1. Atbash Cipher\n");
        printf("2. Caesar Cipher\n");
        printf("3. Affine Cipher\n");
        printf("4. Vigenere Cipher\n");
        printf("5. Gronsfeld Cipher\n");
        printf("6. Beaufort Cipher\n");
        printf("7. Autokey Cipher\n");
        printf("8. Running Key Cipher\n");
        printf("9. Hill Cipher (2x2)\n");
        printf("10. Rail Fence Cipher\n");
        printf("11. Route Cipher\n");
        printf("12. Columnar Transposition Cipher\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", option);
        
        // Clear input buffer
        while (getchar() != '\n');
        
        if (strcmp(option, "0") == 0) {
            break;
        }
        
        printf("Enter text: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0; // Remove newline
        
        if (strcmp(option, "1") == 0) {
            // Atbash Cipher
            printf("Mode (1 for encrypt/decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            if (mode == 1) {
                atbashCipher(text);
                printf("Result: %s\n", text);
            }
        }
        else if (strcmp(option, "2") == 0) {
            // Caesar Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            printf("Enter shift value: ");
            scanf("%d", &shift);
            
            if (mode == 1) {
                caesarCipher(text, shift);
            } else {
                caesarCipher(text, 26 - (shift % 26));
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "3") == 0) {
            // Affine Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            printf("Enter coefficient a (must be coprime to 26): ");
            scanf("%d", &a);
            
            printf("Enter coefficient b: ");
            scanf("%d", &b);
            
            if (mode == 1) {
                affineCipherEncrypt(text, a, b);
            } else {
                affineCipherDecrypt(text, a, b);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "4") == 0) {
            // Vigenere Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            while (getchar() != '\n'); // Clear input buffer
            
            printf("Enter key: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; // Remove newline
            
            if (mode == 1) {
                vigenereCipherEncrypt(text, key);
            } else {
                vigenereCipherDecrypt(text, key);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "5") == 0) {
            // Gronsfeld Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            while (getchar() != '\n'); // Clear input buffer
            
            printf("Enter key (digits only): ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; // Remove newline
            
            if (mode == 1) {
                gronsfeldCipherEncrypt(text, key);
            } else {
                gronsfeldCipherDecrypt(text, key);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "6") == 0) {
            // Beaufort Cipher
            printf("Mode (1 for encrypt/decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            while (getchar() != '\n'); // Clear input buffer
            
            printf("Enter key: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; // Remove newline
            
            beaufortCipher(text, key);
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "7") == 0) {
            // Autokey Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            while (getchar() != '\n'); // Clear input buffer
            
            printf("Enter key: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; // Remove newline
            
            if (mode == 1) {
                autokeyCipherEncrypt(text, key);
            } else {
                autokeyCipherDecrypt(text, key);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "8") == 0) {
            // Running Key Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            while (getchar() != '\n'); // Clear input buffer
            
            printf("Enter book text (as key): ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; // Remove newline
            
            if (mode == 1) {
                runningKeyCipherEncrypt(text, key);
            } else {
                runningKeyCipherDecrypt(text, key);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "9") == 0) {
            // Hill Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            printf("Enter 2x2 key matrix (4 integers separated by spaces): ");
            scanf("%d %d %d %d", &hillKey[0][0], &hillKey[0][1], &hillKey[1][0], &hillKey[1][1]);
            
            if (mode == 1) {
                hillCipherEncrypt(text, hillKey);
            } else {
                hillCipherDecrypt(text, hillKey);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "10") == 0) {
            // Rail Fence Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            printf("Enter number of rails: ");
            scanf("%d", &rails);
            
            if (mode == 1) {
                railFenceCipherEncrypt(text, rails);
            } else {
                railFenceCipherDecrypt(text, rails);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "11") == 0) {
            // Route Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            printf("Enter number of rows: ");
            scanf("%d", &rows);
            
            printf("Enter number of columns: ");
            scanf("%d", &cols);
            
            if (mode == 1) {
                routeCipherEncrypt(text, rows, cols);
            } else {
                routeCipherDecrypt(text, rows, cols);
            }
            printf("Result: %s\n", text);
        }
        else if (strcmp(option, "12") == 0) {
            // Columnar Transposition Cipher
            printf("Mode (1 for encrypt, 2 for decrypt): ");
            int mode;
            scanf("%d", &mode);
            
            while (getchar() != '\n'); // Clear input buffer
            
            printf("Enter key: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; // Remove newline
            
            if (mode == 1) {
                columnarTranspositionEncrypt(text, key);
            } else {
                columnarTranspositionDecrypt(text, key);
            }
            printf("Result: %s\n", text);
        }
        else {
            printf("Invalid option!\n");
        }
    }
    
    return 0;
}