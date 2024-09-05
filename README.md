
# Transaction Management System

This is a simple C-based console application that allows users to manage their financial transactions. The program allows users to:
- Add new transactions
- View all transactions
- View transactions for a specific month and year
- View a breakdown of expenses by category in percentage

## Features

1. **Add New Transaction**:  
   Users can input the date, amount, transaction category, account type, and an optional note for each transaction. This data is stored in a binary file (`transactions2.bin`).

2. **View All Transactions**:  
   Displays all recorded transactions, including the date, amount, category, account type, and any note associated with the transaction.

3. **View Transactions for a Specific Month and Year**:  
   Filters and displays only the transactions made in the specified month and year.

4. **Show Expense Percentages by Category**:  
   Displays how much of the total expense was spent on each category, as a percentage. Only categories with expenses are shown.

## Transaction Categories
- **F**: Food
- **S**: Social life
- **P**: Pets
- **T**: Transport
- **C**: Culture
- **H**: Household
- **A**: Apparel
- **B**: Beauty
- **L**: Health
- **E**: Education
- **G**: Gift
- **O**: Others

## Account Codes
- **C**: Cash
- **O**: UPI & Card

## How to Run

1. **Compile the Program**:
   Use a C compiler like `gcc` to compile the program.

   ```bash
   gcc transaction_management.c -o transaction_management
   ```

2. **Run the Program**:
   After compiling, run the executable.

   ```bash
   ./transaction_management
   ```

3. **Follow the On-Screen Prompts**:
   - Choose from the available options in the menu to manage your transactions.

## Usage

### Adding a New Transaction
- Select option `1` from the menu.
- Enter the transaction details as prompted.
  
### Viewing All Transactions
- Select option `2` from the menu to see a list of all recorded transactions.

### Viewing Transactions by Month/Year
- Select option `3` from the menu.
- Enter the month and year to filter the transactions.

### Viewing Expense Percentages by Category
- Select option `4` from the menu.
- The program will calculate and display the percentage of total expenses for each category.

### Exiting the Program
- Select option `5` to exit the program.

## File Storage
- All transactions are saved to a binary file (`transactions2.bin`) and will persist across program runs. 

## Future Improvements
- Implement data validation to ensure that dates and amounts are entered correctly.
- Provide an option to delete or edit a transaction.
- Implement more advanced reporting features, such as filtering by date range or exporting to CSV.
