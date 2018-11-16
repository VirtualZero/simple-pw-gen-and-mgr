/* pwgen.c - random password generator & manager */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define FALSE 0
#define TRUE 1

char serviceName[50] = "\0";
char username[50] = "\0";
char pwCharSet[91] = "\0";
int pwLength = 0;
char password[91] = "\0"; 

int getValidatedServiceName();
int getValidatedUsername();
int getPWCharacters();
int getValidatedPWLength();
void makePassword();
void writeToFile();
int main(void) {
    int validated = FALSE;
    
    while (validated == FALSE) {
        validated = getValidatedServiceName();
    }

    validated = FALSE;
    while (validated == FALSE) {
        validated = getValidatedUsername();
    }
    
    validated = FALSE;
    while (validated == FALSE) {
        validated = getPWCharacters();
    }
    
    validated = FALSE;
    while (validated == FALSE) {
        validated = getValidatedPWLength();
    }
    
    makePassword();
    writeToFile();
}

int getValidatedServiceName() {
    int validated = FALSE;
    printf("Enter the name of the service the password is for: ");
    scanf(" %50[^\n]", serviceName);
    validated = TRUE;
    return validated;
}

int getValidatedUsername() {
    int validated = FALSE;
    printf("Enter your username or email for the service: ");
    scanf(" %50[^\n]", username);
    validated = TRUE;
    return validated;
}

int getPWCharacters() {
    int validated = FALSE;
    int validPwCharSet = FALSE;
    int containsUpper = FALSE;
    int containsLower = FALSE;
    int containsDigits = FALSE;
    int containsPunct = FALSE;
    char yn;
    
    while (validPwCharSet == FALSE) {
        printf("\nShould your password contain:\n");
    
        while (validated == FALSE) {
            printf("Uppercase Letters? (y/n): ");
            scanf(" %1c", &yn);

            if (yn == 'y' || yn == 'Y') {
                containsUpper = TRUE;
                validated = TRUE;
                strcat(pwCharSet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            }

            else if (yn == 'n' || yn == 'N') {
                validated = TRUE;
            }

            else {
                continue;
            }
        }

        validated = FALSE;
        yn = '\0';
        while (validated == FALSE) {
            printf("Lowercase Letters? (y/n): ");
            scanf(" %1c", &yn);

            if (yn == 'y' || yn == 'Y') {
                containsLower = TRUE;
                validated = TRUE;
                strcat(pwCharSet, "abcdefghijklmnopqrstuvwxyz");
            }

            else if (yn == 'n' || yn == 'N') {
                validated = TRUE;
            }

            else {
                continue;
            }
        }

        validated = FALSE;
        yn = '\0';
        while (validated == FALSE) {
            printf("Digits? (y/n): ");
            scanf(" %1c", &yn);

            if (yn == 'y' || yn == 'Y') {
                containsDigits = TRUE;
                validated = TRUE;
                strcat(pwCharSet, "0123456789");
            }

            else if (yn == 'n' || yn == 'N') {
                validated = TRUE;
            }

            else {
                continue;
            }
        }

        validated = FALSE;
        yn = '\0';
        while (validated == FALSE) {
            printf("Punctuation? (y/n): ");
            scanf(" %1c", &yn);

            if (yn == 'y' || yn == 'Y') {
                containsPunct = TRUE;
                validated = TRUE;
                strcat(pwCharSet, "~!@#$%%^&*()_+=-`][{};:/?.>,<");
            }

            else if (yn == 'n' || yn == 'N') {
                validated = TRUE;
            }

            else {
                continue;
            }
        }
        
        if (strlen(pwCharSet) != 0) {
            validPwCharSet = TRUE;
        }
        
        else {
            validated = FALSE;
            printf("\n[ERROR] You must choose some characters for your password!\n\n");
        }
    }
    
    validated = TRUE;
    return validated;
}

int getValidatedPWLength() {
    int validated = FALSE;
    int flush;
    
    while (validated == FALSE) {
        int chosenPWLength = 0;
        printf("\nChoose the length of your new password:\n");
        printf("1) 8\n");
        printf("2) 16\n");
        printf("3) 32\n");
        printf("4) 64\n");
        printf("Enter the number of your choice (1-4): ");
        scanf(" %d", &chosenPWLength);
        
        if (chosenPWLength == 1) {
            validated = TRUE;
            pwLength = 8;
        }
        
        else if (chosenPWLength == 2) {
            validated = TRUE;
            pwLength = 16;
        }
        
        else if (chosenPWLength == 3) {
            validated = TRUE;
            pwLength = 32;
        }
        
        else if (chosenPWLength == 4) {
            validated = TRUE;
            pwLength = 64;
        }

        
        if (validated == TRUE) {
            return validated;
        }
        
        else {
            printf("\n[ERROR] Invalid Password Length!\n");
            while((flush=getchar()) != '\n' && flush != EOF);

        }
    }
}

void makePassword() {
    srand(time(0));
    for (int i = 0; i < pwLength; i++) {
        password[i] = pwCharSet[rand() % strlen(pwCharSet)];
    }
    
    printf("\nYour password is:\n%s\n", password);
}

void writeToFile() {
    FILE *credentialsFile;
    credentialsFile = fopen("account_credentials.txt", "a");
    
    if (credentialsFile == NULL) {
        printf("[ERROR] Error writing to file. Check permissions.");
    }
    
    else {
        fprintf(credentialsFile, "%s\n%s\n%s\n\n", serviceName, username, password);
        fclose(credentialsFile);
        printf("\nYour credentials have been saved to account_credentials.txt.\n");
    }
}
