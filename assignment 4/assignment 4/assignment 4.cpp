#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>

using namespace std;

// Constants
const int MAX_ACCOUNTS = 100;
const int MIN_ACCOUNT_NUM = 10000;
const int MAX_ACCOUNT_NUM = 10099;

// Struct for holding account information
struct Account {
    string familyName;
    string givenName;
    int accountNum = 0;
    double balance = 0.0;
};

// Global variables
Account accounts[MAX_ACCOUNTS];
int numAccounts = 0;

// Function prototypes
void addAccount();
void removeAccount();
void displayAccount();
void applyDeposit();
void applyWithdrawal();
void sortAccounts();
void displayAverageBalance();
void displayTotalBalance();
void insertAccount();
void shiftAccounts(int index);

int main() {
    int choice;

    // Display menu until user chooses to exit
    do {
        std::cout << "============================" << endl;
        std::cout << "          Main Menu         " << endl;
        std::cout << "============================" << endl;
        std::cout << "1. Add a bank account" << endl;
        std::cout << "2. Remove a bank account" << endl;
        std::cout << "3. Display the information of a particular client's account" << endl;
        std::cout << "4. Apply a deposit to a particular account" << endl;
        std::cout << "5. Apply a withdrawal from a particular account" << endl;
        std::cout << "6. Sort and display the list of clients" << endl;
        std::cout << "7. Display the average balance value of the accounts" << endl;
        std::cout << "8. Display the total balance value of the accounts" << endl;
        std::cout << "9. Insert an account" << endl;
        std::cout << "10. Exit" << endl;

        // Get user's choice
        std::cout << "Enter your choice (1-10): ";
        std::cin >> choice;
        std::cout << endl;

        switch (choice) {
        case 1:
            addAccount();
            break;
        case 2:
            removeAccount();
            break;
        case 3:
            displayAccount();
            break;
        case 4:
            applyDeposit();
            break;
        case 5:
            applyWithdrawal();
            break;
        case 6:
            sortAccounts();
            break;
        case 7:
            displayAverageBalance();
            break;
        case 8:
            displayTotalBalance();
            break;
        case 9:
            insertAccount();
            break;
        case 10:
            std::cout << "Exiting the application..." << endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << endl;
            break;
        }

        std::cout << endl;

    } while (choice != 10);

    return 0;
}

void addAccount() {
    // Check if maximum number of accounts has been reached
    if (numAccounts == MAX_ACCOUNTS) {
        cout << "Maximum number of accounts reached. Cannot add new account." << endl;
        return;
    }

    // Get input for new account
    string familyName, givenName;
    int accountNum;
    double balance;

    // Prompt the user to enter a valid family name
    while (true) {
        cout << "Enter family name: ";
        cin >> familyName;
        if (familyName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid input. Family name must only contain letters. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Prompt the user to enter a valid given name
    while (true) {
        cout << "Enter first name: ";
        cin >> givenName;
        if (givenName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid input. Given name must only contain letters. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Generate a random account number between 10000 and 10099
    accountNum = rand() % (MAX_ACCOUNT_NUM - MIN_ACCOUNT_NUM + 1) + MIN_ACCOUNT_NUM;

    // Check for duplicate account number
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            // If the generated account number already exists, generate a new one
            accountNum = rand() % (MAX_ACCOUNT_NUM - MIN_ACCOUNT_NUM + 1) + MIN_ACCOUNT_NUM;
            i = -1; // start checking from the beginning of the array again
        }
    }

    // Prompt the user to enter a valid balance
    while (true) {
        cout << "Enter balance: ";
        cin >> balance;
        if (cin.fail() || balance < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Balance must be a non-negative number. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Add new account to array
    Account newAccount = { familyName, givenName, accountNum, balance };
    accounts[numAccounts] = newAccount;
    numAccounts++;

    cout << "Account added successfully. Account number: " << accountNum << endl;
}

void removeAccount() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        std::cout << "No accounts exist. Cannot remove account." << std::endl;
        return;
    }

    // Get input for account to remove
    int accountNum;

    while (true) {
        std::cout << "Enter account number to remove (between 10000 and 10099): ";
        if (!(std::cin >> accountNum)) {
            // Input was not a valid integer, clear error flag and discard input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (accountNum < MIN_ACCOUNT_NUM || accountNum > MAX_ACCOUNT_NUM) {
            std::cout << "Invalid account number. Please enter a number between 10000 and 10099." << std::endl;
            continue;
        }
        break;
    }

    // Find index of account to remove
    int removeIndex = -1;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            removeIndex = i;
            break;
        }
    }

    // Remove account if found
    if (removeIndex != -1) {
        // Shift accounts back to fill gap
        shiftAccounts(removeIndex);
        numAccounts--;
        std::cout << "Account removed successfully." << std::endl;
    }
    else {
        std::cout << "Account not found. Cannot remove account." << std::endl;
    }
}

void displayAccount() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        cout << "No accounts exist. Cannot display account." << endl;
        return;
    }

    // Get input for account to display
    int accountNum;
    bool validInput = false;

    do {
        cout << "Enter account number to display (between 10000 and 10099): ";
        cin >> accountNum;

        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        }
        else if (accountNum < MIN_ACCOUNT_NUM || accountNum > MAX_ACCOUNT_NUM) {
            cout << "Invalid account number. Please enter a number between 10000 and 10099." << endl;
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    // Find account to display
    bool accountFound = false;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            cout << "Family name: " << accounts[i].familyName << endl;
            cout << "Given name: " << accounts[i].givenName << endl;
            cout << "Account number: " << accounts[i].accountNum << endl;
            cout << "Balance: " << accounts[i].balance << endl;
            accountFound = true;
            break;
        }
    }

    if (!accountFound) {
        cout << "Account not found. Cannot display account." << endl;
    }
}

void applyDeposit() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        cout << "No accounts exist. Cannot apply deposit." << endl;
        return;
    }

    // Get input for account to apply deposit
    int accountNum;
    double depositAmount;

    while (true) {
        cout << "Enter account number to apply deposit: ";
        if (!(cin >> accountNum)) {
            // Invalid input, clear the error and prompt again
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid account number. Please enter a valid number." << endl;
            continue;
        }

        // Validate account number
        if (accountNum < MIN_ACCOUNT_NUM || accountNum > MAX_ACCOUNT_NUM) {
            cout << "Invalid account number. Please enter a valid number." << endl;
            continue;
        }

        // Account number is valid, break out of the loop
        break;
    }

    while (true) {
        cout << "Enter deposit amount: ";
        if (!(cin >> depositAmount)) {
            // Invalid input, clear the error and prompt again
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid deposit amount. Please enter a valid number." << endl;
            continue;
        }

        // Validate deposit amount
        if (depositAmount <= 0) {
            cout << "Deposit amount must be greater than 0. Please enter a valid number." << endl;
            continue;
        }

        // Deposit amount is valid, break out of the loop
        break;
    }

    // Find account to apply deposit
    bool accountFound = false;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            accounts[i].balance += depositAmount;
            cout << "Deposit applied successfully. New balance: " << accounts[i].balance << endl;
            accountFound = true;
            break;
        }
    }

    if (!accountFound) {
        cout << "Account not found. Cannot apply deposit." << endl;
    }
}

void applyWithdrawal() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        cout << "No accounts exist. Cannot apply withdrawal." << endl;
        return;
    }

    // Get input for account to apply withdrawal
    int accountNum;
    double withdrawalAmount;

    while (true) {
        cout << "Enter account number to apply withdrawal: ";
        if (!(cin >> accountNum)) {
            // Invalid input, clear the error and prompt again
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid account number. Please enter a valid number." << endl;
            continue;
        }

        // Validate account number
        if (accountNum < MIN_ACCOUNT_NUM || accountNum > MAX_ACCOUNT_NUM) {
            cout << "Invalid account number. Please enter a valid number." << endl;
            continue;
        }

        // Account number is valid, break out of the loop
        break;
    }

    while (true) {
        cout << "Enter withdrawal amount: ";
        if (!(cin >> withdrawalAmount)) {
            // Invalid input, clear the error and prompt again
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid withdrawal amount. Please enter a valid number." << endl;
            continue;
        }

        // Validate withdrawal amount
        if (withdrawalAmount <= 0) {
            cout << "withdrawal amount must be greater than 0. Please enter a valid number." << endl;
            continue;
        }

        // Deposit amount is valid, break out of the loop
        break;
    }

    // Find account to apply withdrawal
    bool accountFound = false;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            accounts[i].balance -= withdrawalAmount;
            cout << "Withdrawal applied successfully. New balance: " << accounts[i].balance << endl;
            accountFound = true;
            break;
        }
    }

    if (!accountFound) {
        cout << "Account not found. Cannot apply deposit." << endl;
    }
}

void sortAccounts() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        cout << "No accounts exist. Cannot sort accounts." << endl;
        return;
    }

    // Prompt user for sort order
    char sortOrder;
    do {
        cout << "Enter sort order (A for ascending, D for descending): ";
        cin >> sortOrder;
    } while (sortOrder != 'A' && sortOrder != 'a' && sortOrder != 'D' && sortOrder != 'd');

    // Sort accounts
    if (sortOrder == 'A' || sortOrder == 'a') {
        // Sort accounts in ascending order
        for (int i = 0; i < numAccounts - 1; i++) {
            for (int j = i + 1; j < numAccounts; j++) {
                if (accounts[i].accountNum > accounts[j].accountNum) {
                    swap(accounts[i], accounts[j]);
                }
            }
        }
        cout << "Accounts sorted in ascending order." << endl;
    }
    else {
        // Sort accounts in descending order
        for (int i = 0; i < numAccounts - 1; i++) {
            for (int j = i + 1; j < numAccounts; j++) {
                if (accounts[i].accountNum < accounts[j].accountNum) {
                    swap(accounts[i], accounts[j]);
                }
            }
        }
        cout << "Accounts sorted in descending order." << endl;
    }
}

void displayAverageBalance() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        cout << "No accounts exist. Cannot display average balance." << endl;
        return;
    }

    // Calculate average balance
    double totalBalance = 0;
    for (int i = 0; i < numAccounts; i++) {
        totalBalance += accounts[i].balance;
    }
    double averageBalance = totalBalance / numAccounts;

    cout << "Average balance: " << averageBalance << endl;
}

void displayTotalBalance() {
    // Check if any accounts exist
    if (numAccounts == 0) {
        cout << "No accounts exist. Cannot display total balance." << endl;
        return;
    }

    // Calculate total balance
    double totalBalance = 0;
    for (int i = 0; i < numAccounts; i++) {
        totalBalance += accounts[i].balance;
    }

    cout << "Total balance: " << totalBalance << endl;
}

void insertAccount() {
    // Check if maximum number of accounts has been reached
    if (numAccounts == MAX_ACCOUNTS) {
        cout << "Maximum number of accounts reached. Cannot insert account." << endl;
        return;
    }

    // Get input for new account
    string familyName, givenName;
    int accountNum;
    double balance;
    int insertIndex;

    while (true) {
        cout << "Enter family name: ";
        cin >> familyName;
        if (familyName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid input. Family name must only contain letters. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Prompt the user to enter a valid given name
    while (true) {
        cout << "Enter first name: ";
        cin >> givenName;
        if (givenName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid input. Given name must only contain letters. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Prompt the user to enter a valid account number
    while (true) {
        cout << "Enter account number (between 10000 and 10099): ";
        cin >> accountNum;
        if (cin.fail() || accountNum < MIN_ACCOUNT_NUM || accountNum > MAX_ACCOUNT_NUM) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Account number must be an integer between 10000 and 10099. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Check for duplicate account number
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            cout << "Account number already exists. Cannot add new account." << endl;
            return;
        }
    }

    // Prompt the user to enter a valid balance
    while (true) {
        cout << "Enter balance: ";
        cin >> balance;
        if (cin.fail() || balance < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Balance must be a non-negative number. Please try again." << endl;
        }
        else {
            break;
        }
    }
    cout << "Enter index to insert account (0 to " << numAccounts << "): ";
    cin >> insertIndex;

    // Check if account number is unique
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNum == accountNum) {
            cout << "Account number already exists. Cannot insert account." << endl;
            return;
        }
    }

    // Shift accounts to make space for new account
    for (int i = numAccounts - 1; i >= insertIndex; i--) {
        accounts[i + 1] = accounts[i];
    }

    // Insert new account
    Account newAccount = { familyName, givenName, accountNum, balance };
    accounts[insertIndex] = newAccount;
    numAccounts++;

    cout << "Account inserted successfully." << endl;
}

void shiftAccounts(int index) {
    for (int i = index; i < numAccounts - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    // set the last account to a default account
    accounts[numAccounts - 1] = Account{ "", "", 0, 0.0 };
}

void showMenu() {
    cout << "Bank Program" << endl;
    cout << "1. Add a bank account" << endl;
    cout << "2. Remove a bank account" << endl;
    cout << "3. Display the information of a particular client's account" << endl;
    cout << "4. Apply a deposit to a particular account" << endl;
    cout << "5. Apply a withdrawal from a particular account" << endl;
    cout << "6. Sort and display the list of clients according to their balance, family name and given name, in ascending or descending order" << endl;
    cout << "7. Display the average balance value of the accounts" << endl;
    cout << "8. Display the total balance value of the accounts" << endl;
    cout << "9. Insert an account at any position in the array" << endl;
    cout << "10. Exit" << endl;
}

void handleMenuSelection(int selection) {
    switch (selection) {
    case 1:
        addAccount();
        break;
    case 2:
        removeAccount();
        break;
    case 3:
        displayAccount();
        break;
    case 4:
        applyDeposit();
        break;
    case 5:
        applyWithdrawal();
        break;
    case 6:
        sortAccounts();
        break;
    case 7:
        displayAverageBalance();
        break;
    case 8:
        displayTotalBalance();
        break;
    case 9:
        insertAccount();
        break;
    case 10:
        exit(0);
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
        break;
    }
}