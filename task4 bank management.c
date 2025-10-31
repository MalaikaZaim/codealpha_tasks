#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "accounts.dat"
struct Account {
    int acc_no;
    char name[50];
    float balance;
};
void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();
int findAccount(int acc_no, struct Account *acc);
void updateAccount(struct Account acc);
int main() {
    int choice;
    while (1) {
        printf("\n+++ Bank Account Management System +++\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                balanceEnquiry();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void createAccount() {
    struct Account acc;
    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);
    getchar();
    if (findAccount(acc.acc_no, &acc)) {
        printf("Account number already exists!\n");
        return;
    }
    printf("Enter Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; 
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&acc, sizeof(struct Account), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

void deposit() {
    int acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    struct Account acc;
    if (!findAccount(acc_no, &acc)) {
        printf("Account not found!\n");
        return;
    }
    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    acc.balance += amount;
    updateAccount(acc);
    printf("Deposit successful! New Balance: %.2f\n", acc.balance);
}

void withdraw() {
    int acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    struct Account acc;
    if (!findAccount(acc_no, &acc)) {
        printf("Account not found!\n");
        return;
    }
    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > acc.balance) {
        printf("Invalid amount or insufficient balance!\n");
        return;
    }
    acc.balance -= amount;
    updateAccount(acc);
    printf("Withdrawal successful! New Balance: %.2f\n", acc.balance);
}

void balanceEnquiry() {
    int acc_no;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);

    struct Account acc;
    if (!findAccount(acc_no, &acc)) {
        printf("Account not found!\n");
        return;
    }

    printf("Account Holder: %s\nBalance: %.2f\n", acc.name, acc.balance);
}

int findAccount(int acc_no, struct Account *acc) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) return 0;
    while (fread(acc, sizeof(struct Account), 1, file)) {
        if (acc->acc_no == acc_no) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void updateAccount(struct Account acc) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) return;
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        fclose(file);
        return;
    }
    struct Account temp_acc;
    while (fread(&temp_acc, sizeof(struct Account), 1, file)) {
        if (temp_acc.acc_no == acc.acc_no) {
            fwrite(&acc, sizeof(struct Account), 1, temp);
        } else {
            fwrite(&temp_acc, sizeof(struct Account), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
}

