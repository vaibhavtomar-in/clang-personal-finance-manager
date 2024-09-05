#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a transaction
struct Transaction {
    int day;               
    int month;             
    int year;              
    float amount;          
    char categoryCode;     
    char accountCode;      
    char note[100];        
};

// Function declarations
void addTransaction();
void readTransactions();
void getCategoryFullName(char code, char fullName[]);
void getAccountFullName(char code, char fullName[]);

int main() {
    int choice;

    while (1) {
        printf("\nTransaction Management System\n");
        printf("1. Add a new transaction\n");
        printf("2. View all transactions\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                readTransactions();
                break;
            case 3:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function implementations

void addTransaction() {
    FILE *filePtr;
    struct Transaction t;

    filePtr = fopen("transactions2.bin", "ab");
    if (filePtr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &t.day, &t.month, &t.year);

    printf("Enter Amount: ");
    scanf("%f", &t.amount);
    getchar();

    printf("Category Codes\nF for food\nS for social life\nP for pets\nT for transport\nC for culture\nH for household\nA for apparel\nB for beauty\nL for health\nE for education\nG for gift\nO for others\nTransaction category code : ");
    scanf("%c", &t.categoryCode);
    getchar();

    printf("Enter Account Code (C for Cash, O for UPI & Card): ");
    scanf("%c", &t.accountCode);
    getchar();

    printf("Enter Note: ");
    gets(t.note);

    fwrite(&t, sizeof(struct Transaction), 1, filePtr);

    fclose(filePtr);

    printf("Transaction added successfully.\n");
}

void getCategoryFullName(char code, char fullName[]) {
    // Convert category code to full name
    switch (code) {
        case 'F':
            strcpy(fullName, "Food");
            break;
        case 'S':
            strcpy(fullName, "Social life");
            break;
        case 'P':
            strcpy(fullName, "Pets");
            break;
        case 'T':
            strcpy(fullName, "Transport");
            break;
        case 'C':
            strcpy(fullName, "Culture");
            break;
        case 'H':
            strcpy(fullName, "Household");
            break;
        case 'A':
            strcpy(fullName, "Apparel");
            break;
        case 'B':
            strcpy(fullName, "Beauty");
            break;
        case 'L':
            strcpy(fullName, "Health");
            break;
        case 'E':
            strcpy(fullName, "Education");
            break;
        case 'G':
            strcpy(fullName, "Gift");
            break;
        case 'O':
            strcpy(fullName, "Other");
            break;
        default:
            strcpy(fullName, "Unknown");
            break;
    }
}

void getAccountFullName(char code, char fullName[]) {
    // Convert account code to full name
    if (code == 'C') {
        strcpy(fullName, "Cash");
    } else if (code == 'O') {
        strcpy(fullName, "UPI & Card");
    } else {
        strcpy(fullName, "Unknown");
    }
}

void readTransactions() {
    FILE *filePtr;
    struct Transaction t;
    char categoryFullName[20];
    char accountFullName[12];
    int count = 0;

    filePtr = fopen("transactions2.bin", "rb");
    if (filePtr == NULL) {
        printf("Error opening file or no transactions found.\n");
        return;
    }

    printf("\nList of Transactions:\n");
    printf("Date         Amount   Category       Account      Note                            \n");
    printf("-------------------------------------------------------------------------------------------\n");

    while (fread(&t, sizeof(struct Transaction), 1, filePtr)) {
        getCategoryFullName(t.categoryCode, categoryFullName);
        getAccountFullName(t.accountCode, accountFullName);
        printf("%02d/%02d/%04d  %-7.2f  %-12s  %-10s  %-30s\n", 
               t.day, t.month, t.year, t.amount, categoryFullName, accountFullName, t.note);
        count++;
    }


    if (count == 0) {
        printf("No transactions found.\n");
    }

    fclose(filePtr);
}
