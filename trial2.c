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
void readTransactionsByMonthYear();
void showExpensePercentages();
void getCategoryFullName(char code, char fullName[]);
void getAccountFullName(char code, char fullName[]);

int main() {
    int choice;

    while (1) {
        printf("\nTransaction Management System\n");
        printf("1. Add a new transaction\n");
        printf("2. View all transactions\n");
        printf("3. View transactions for a specific month/year\n");
        printf("4. Show expense percentage by category\n");
        printf("5. Exit\n");
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
                readTransactionsByMonthYear();
                break;
            case 4:
                showExpensePercentages();
                break;
            case 5:
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

void readTransactionsByMonthYear() {
    FILE *filePtr;
    struct Transaction t;
    int month, year;
    char categoryFullName[20];
    char accountFullName[12];
    int count = 0;

    printf("Enter the month (MM): ");
    scanf("%d", &month);
    printf("Enter the year (YYYY): ");
    scanf("%d", &year);

    filePtr = fopen("transactions2.bin", "rb");
    if (filePtr == NULL) {
        printf("Error opening file or no transactions found.\n");
        return;
    }

    printf("\nTransactions for %02d/%04d:\n", month, year);
    printf("Date         Amount   Category       Account      Note                            \n");
    printf("-------------------------------------------------------------------------------------------\n");

    while (fread(&t, sizeof(struct Transaction), 1, filePtr)) {
        if (t.month == month && t.year == year) {
            getCategoryFullName(t.categoryCode, categoryFullName);
            getAccountFullName(t.accountCode, accountFullName);
            printf("%02d/%02d/%04d  %-7.2f  %-12s  %-10s  %-30s\n", 
                   t.day, t.month, t.year, t.amount, categoryFullName, accountFullName, t.note);
            count++;
        }
    }

    if (count == 0) {
        printf("No transactions found for %02d/%04d.\n", month, year);
    }

    fclose(filePtr);
}

void showExpensePercentages() {
    FILE *filePtr;
    struct Transaction t;
    float totalAmount = 0;
    float categoryTotals[12] = {0}; // Array to store the total for each category
    int count = 0;

    filePtr = fopen("transactions2.bin", "rb");
    if (filePtr == NULL) {
        printf("Error opening file or no transactions found.\n");
        return;
    }

    // First pass: Calculate total and category-wise expenses
    while (fread(&t, sizeof(struct Transaction), 1, filePtr)) {
        totalAmount += t.amount;

        switch (t.categoryCode) {
            case 'F': categoryTotals[0] += t.amount; break;
            case 'S': categoryTotals[1] += t.amount; break;
            case 'P': categoryTotals[2] += t.amount; break;
            case 'T': categoryTotals[3] += t.amount; break;
            case 'C': categoryTotals[4] += t.amount; break;
            case 'H': categoryTotals[5] += t.amount; break;
            case 'A': categoryTotals[6] += t.amount; break;
            case 'B': categoryTotals[7] += t.amount; break;
            case 'L': categoryTotals[8] += t.amount; break;
            case 'E': categoryTotals[9] += t.amount; break;
            case 'G': categoryTotals[10] += t.amount; break;
            case 'O': categoryTotals[11] += t.amount; break;
        }
        count++;
    }

    fclose(filePtr);

    if (totalAmount == 0) {
        printf("No transactions to calculate percentages.\n");
        return;
    }

    // Second pass: Display the percentage for each category
    printf("\nExpense Breakdown by Category:\n");
    printf("---------------------------------\n");

    char categoryNames[12][15] = {"Food", "Social life", "Pets", "Transport", "Culture", "Household",
                                  "Apparel", "Beauty", "Health", "Education", "Gift", "Other"};
    
    for (int i = 0; i < 12; i++) {
        if (categoryTotals[i] > 0) {
            printf("%-12s: %.2f%%\n", categoryNames[i], (categoryTotals[i] / totalAmount) * 100);
        }
    }
}
