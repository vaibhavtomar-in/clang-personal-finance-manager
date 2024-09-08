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

// Structure for user credentials
struct User {
    char username[50];
    char password[50];
};

// Function declarations
void signup();
void login();
void addTransaction(char *filename);
void readTransactions(char *filename);
void readTransactionsByMonthYear(char *filename);
void showExpensePercentages(char *filename);
void showMonthlyExpensePercentages(char *filename);
void showExpensePercentagePerWeek(char *filename);
void getCategoryFullName(char code, char fullName[]);
void getAccountFullName(char code, char fullName[]);

int main() {
    int choice;

    while (1) {
        printf("\nTransaction Management System\n");
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
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

// Function to sign up a new user
void signup() {
    FILE *filePtr;
    struct User newUser;
    char fileName[60];

    printf("Enter a username: ");
    getchar();  // Clear the buffer
    gets(newUser.username);  // Use gets() to input the username

    printf("Enter a password: ");
    gets(newUser.password);  // Use gets() to input the password

    filePtr = fopen("users.bin", "ab");
    if (filePtr == NULL) {
        printf("Error opening users file!\n");
        return;
    }

    fwrite(&newUser, sizeof(struct User), 1, filePtr);
    fclose(filePtr);

    // Create a new file for the user
    sprintf(fileName, "%s_transactions.bin", newUser.username);
    filePtr = fopen(fileName, "wb");
    if (filePtr == NULL) {
        printf("Error creating user file!\n");
        return;
    }
    fclose(filePtr);

    printf("Signup successful! You can now login.\n");
}

// Function to log in an existing user
void login() {
    FILE *filePtr;
    struct User currentUser;
    char username[50], password[50], fileName[60];
    int found = 0;

    printf("Enter your username: ");
    gets(username);

    printf("Enter your password: ");
    gets(password); 
    filePtr = fopen("users.bin", "rb");
    if (filePtr == NULL) {
        printf("Error opening users file!\n");
        return;
    }

    while (fread(&currentUser, sizeof(struct User), 1, filePtr)) {
        if (strcmp(currentUser.username, username) == 0 && strcmp(currentUser.password, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(filePtr);

    if (!found) {
        printf("Invalid username or password!\n");
        return;
    }

    // Use the logged-in user's transaction file
    sprintf(fileName, "%s_transactions.bin", username);

    // Logged in successfully, display user menu
    int choice;
    while (1) {
        printf("\nWelcome, %s\n", username);
        printf("1. Add a new transaction\n");
        printf("2. View all transactions\n");
        printf("3. View transactions for a specific month/year\n");
        printf("4. Show expense percentage by category\n");
        printf("5. Show expense percentage per week for a specific month\n");
        printf("6. Show expense percentage by category for a specific month\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addTransaction(fileName);
                break;
            case 2:
                readTransactions(fileName);
                break;
            case 3:
                readTransactionsByMonthYear(fileName);
                break;
            case 4:
                showExpensePercentages(fileName);
                break;
            case 5:
                showExpensePercentagePerWeek(fileName);
                break;
            case 6:
                showMonthlyExpensePercentages(fileName);
                break;
            case 7:
                printf("Logging out.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to add a transaction
void addTransaction(char *filename) {
    FILE *filePtr;
    struct Transaction t;

    filePtr = fopen(filename, "ab");
    if (filePtr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    reEnterDate:
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &t.day, &t.month, &t.year);
    if((t.month<1 || t.month>12) || (t.day<1||t.day>31) || (t.year<1000 || t.year >9999)){
        printf("Invalid date. Please re-enter.\n");
        goto reEnterDate;
    }
    if ((t.month == 1|| t.month == 3|| t.month == 5|| t.month == 7|| t.month == 8|| t.month == 10|| t.month == 12 ) && (t.day < 1 || t.day > 31 )){
        printf("invalid date entered, try again\n");
        goto reEnterDate;
    }
    if ((t.month == 4|| t.month == 6|| t.month == 9|| t.month == 11) && (t.day < 1 || t.day > 30 )){
        printf("invalid date entered, try again\n");
        goto reEnterDate;
    }
    if (t.month == 2 ){
        if (((t.year%4 == 0) && (t.day<1 || t.day>29)) || ((t.year%4 != 0) && (t.day<1 || t.day>28))){
            printf("invalid date entered, try again\n");
            goto reEnterDate;
        }
    }

    printf("Enter Amount: ");
    scanf("%f", &t.amount);
    getchar();

    reEnterCategory:
    printf("Category Codes\nF for food\nS for social life\nP for pets\nT for transport\nC for culture\nH for household\nA for apparel\nB for beauty\nL for health\nE for education\nG for gift\nO for others\nTransaction category code : ");
    scanf("%c", &t.categoryCode);
    getchar();
    if(!(t.categoryCode == 'F' || t.categoryCode == 'S' || t.categoryCode == 'P' || t.categoryCode == 'T' || t.categoryCode == 'C' || t.categoryCode == 'H' || t.categoryCode == 'A' || t.categoryCode == 'B' || t.categoryCode == 'L' || t.categoryCode == 'E' || t.categoryCode == 'G' || t.categoryCode == 'O')){
        printf("Invalid category code. Please try again.\n");
        goto reEnterCategory;
    }
    
    reEnterAccount:
    printf("Enter Account Code (C for Cash, O for UPI & Card): ");
    scanf("%c", &t.accountCode);
    getchar();
    if(!(t.accountCode == 'C' || t.accountCode == 'O')){
        printf("Invalid account code. Please try again.\n");
        goto reEnterAccount;
    }

    printf("Enter Note: ");
    gets(t.note);

    fwrite(&t, sizeof(struct Transaction), 1, filePtr);

    fclose(filePtr);

    printf("Transaction added successfully.\n");
}

// Function to get the category full name
void getCategoryFullName(char code, char fullName[]) {
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

// Function to get the account full name
void getAccountFullName(char code, char fullName[]) {
    if (code == 'C') {
        strcpy(fullName, "Cash");
    } else if (code == 'O') {
        strcpy(fullName, "UPI & Card");
    } else {
        strcpy(fullName, "Unknown");
    }
}

// Function to read all transactions
void readTransactions(char *filename) {
    FILE *filePtr;
    struct Transaction t;
    char categoryFullName[20];
    char accountFullName[12];
    int count = 0;

    filePtr = fopen(filename, "rb");
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

// Function to read transactions by month/year
void readTransactionsByMonthYear(char *filename) {
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

    filePtr = fopen(filename, "rb");
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
        printf("No transactions found for the given month and year.\n");
    }

    fclose(filePtr);
}

// Function to show expense percentages by category
void showExpensePercentages(char *filename) {
    FILE *filePtr;
    struct Transaction t;
    float total = 0.0, categoryTotals[11] = {0}; 
    char categoryFullName[20];

    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("Error opening file or no transactions found.\n");
        return;
    }

    while (fread(&t, sizeof(struct Transaction), 1, filePtr)) {
        total += t.amount;
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
        }
    }

    if (total == 0) {
        printf("No transactions to calculate percentages.\n");
    } else {
        printf("\nExpense Percentages by Category:\n");
        printf("------------------------------------\n");
        for (int i = 0; i < 11; i++) {
            getCategoryFullName("FSPTCHABLEG"[i], categoryFullName);
            printf("%-12s: %.2f%%\n", categoryFullName, (categoryTotals[i] / total) * 100);
        }
    }

    fclose(filePtr);
}

void showExpensePercentagePerWeek(char *filename) {
    FILE *filePtr;
    struct Transaction t;
    int month, year;
    float weekTotals[5] = {0}; 
    float totalAmount = 0;      

    printf("Enter the month (MM): ");
    scanf("%d", &month);
    printf("Enter the year (YYYY): ");
    scanf("%d", &year);

    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("Error opening file or no transactions found.\n");
        return;
    }
    while (fread(&t, sizeof(struct Transaction), 1, filePtr)) {
        if (t.month == month && t.year == year) {
            int week = (t.day - 1) / 7; 
            if (week < 5) {  
                weekTotals[week] += t.amount;
            }
            totalAmount += t.amount;     
        }
    }

    fclose(filePtr);

    // Display the expense percentage per week
    printf("\nExpense percentage per week for %02d/%04d:\n", month, year);
    if (totalAmount == 0) {
        printf("No transactions found for the given month and year.\n");
        return;
    }

    printf("Total expenditure this month : %.2f\n", totalAmount);
    for (int i = 0; i < 5; i++) {
        if (weekTotals[i] > 0) {
            float percentage = (weekTotals[i] / totalAmount) * 100;
            printf("Week %d: %.2f%% , Amount : %.2f\n", i + 1, percentage, weekTotals[i]);
        }
    }
}
void showMonthlyExpensePercentages(char *filename) {
    FILE *filePtr;
    struct Transaction t;
    float totalAmount = 0.0, categoryTotals[11] = {0}; 
    char categoryFullName[20];
    int month, year;
    int categoriesUsed[11] = {0}; 
    printf("Enter the month (MM): ");
    scanf("%d", &month);
    printf("Enter the year (YYYY): ");
    scanf("%d", &year);

    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("Error opening file or no transactions found.\n");
        return;
    }

    while (fread(&t, sizeof(struct Transaction), 1, filePtr)) {
        if (t.month == month && t.year == year) {
            totalAmount += t.amount;
            switch (t.categoryCode) {
                case 'F': categoryTotals[0] += t.amount; categoriesUsed[0] = 1; break;
                case 'S': categoryTotals[1] += t.amount; categoriesUsed[1] = 1; break;
                case 'P': categoryTotals[2] += t.amount; categoriesUsed[2] = 1; break;
                case 'T': categoryTotals[3] += t.amount; categoriesUsed[3] = 1; break;
                case 'C': categoryTotals[4] += t.amount; categoriesUsed[4] = 1; break;
                case 'H': categoryTotals[5] += t.amount; categoriesUsed[5] = 1; break;
                case 'A': categoryTotals[6] += t.amount; categoriesUsed[6] = 1; break;
                case 'B': categoryTotals[7] += t.amount; categoriesUsed[7] = 1; break;
                case 'L': categoryTotals[8] += t.amount; categoriesUsed[8] = 1; break;
                case 'E': categoryTotals[9] += t.amount; categoriesUsed[9] = 1; break;
                case 'G': categoryTotals[10] += t.amount; categoriesUsed[10] = 1; break;
            }
        }
    }

    fclose(filePtr);

    if (totalAmount == 0) {
        printf("No transactions found for the given month and year.\n");
        return;
    }

    printf("\nTotal expenses for %02d/%04d: %.2f\n", month, year, totalAmount);

    printf("\nCategory Breakdown:\n");
    printf("------------------------------------\n");
    for (int i = 0; i < 11; i++) {
        if (categoriesUsed[i]) {
            getCategoryFullName("FSPTCHABLEG"[i], categoryFullName);
            printf("%-12s: %.2f%%, Amount %.2f\n", categoryFullName, (categoryTotals[i] / totalAmount) * 100, categoryTotals[i]);
        }
    }
}