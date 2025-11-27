#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CyberRecord {
    int id;
    char name[50];
    int pcNo;
    char login[10];
    char logout[10];
    int amount;
};

void addRecord();
void displayRecords();
void searchRecord();
void updateRecord();
void deleteRecord();
void header();

int main() {
    int choice;

    while (1) {
        header();
        printf("1. Add New Record\n");
        printf("2. Search Record\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Display All Records\n");
        printf("6. Exit\n");

        printf("-------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: searchRecord(); break;
            case 3: updateRecord(); break;
            case 4: deleteRecord(); break;
            case 5: displayRecords(); break;
            case 6:
                printf("\n=========== PROGRAM TERMINATED ===========\n");
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar(); getchar(); // clear buffer
    }

    return 0;
}

// ------------------------------------------------------------
// Header Formatting
// ------------------------------------------------------------
void header() {
    system("clear || cls");
    printf("===========================================\n");
    printf("         CYBER MANAGEMENT SYSTEM\n");
    printf("===========================================\n\n");
}

// ------------------------------------------------------------
// Add New Record
// ------------------------------------------------------------
void addRecord() {
    struct CyberRecord r;
    FILE *fp = fopen("records.dat", "ab");

    header();
    printf("========== ADD NEW CYBER RECORD ==========\n");

    printf("Enter User ID        : ");
    scanf("%d", &r.id);

    printf("Enter Name           : ");
    scanf("%s", r.name);

    printf("Enter PC Number      : ");
    scanf("%d", &r.pcNo);

    printf("Login Time (HH:MM)   : ");
    scanf("%s", r.login);

    printf("Logout Time (HH:MM)  : ");
    scanf("%s", r.logout);

    printf("Amount to Pay (INR)  : ");
    scanf("%d", &r.amount);

    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);

    printf("\n-------------------------------------------\n");
    printf("Record added successfully!\n");
    printf("-------------------------------------------\n");
}

// ------------------------------------------------------------
// Display All Records
// ------------------------------------------------------------
void displayRecords() {
    struct CyberRecord r;
    FILE *fp = fopen("records.dat", "rb");

    header();
    printf("========== DISPLAYING ALL RECORDS =========\n\n");

    printf("-------------------------------------------------------------\n");
    printf("ID   Name             PC No.    Login    Logout    Amount\n");
    printf("-------------------------------------------------------------\n");

    while (fread(&r, sizeof(r), 1, fp)) {
        printf("%-4d %-15s %-9d %-8s %-8s %-6d\n",
               r.id, r.name, r.pcNo, r.login, r.logout, r.amount);
    }

    printf("-------------------------------------------------------------\n");
    fclose(fp);
}

// ------------------------------------------------------------
// Search Record by ID
// ------------------------------------------------------------
void searchRecord() {
    int id, found = 0;
    struct CyberRecord r;
    FILE *fp = fopen("records.dat", "rb");

    header();
    printf("=============== SEARCH RECORD ===============\n");
    printf("Enter User ID to search: ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            found = 1;

            printf("\n-------------------------------------------\n");
            printf("Record Found!\n");
            printf("-------------------------------------------\n");
            printf("ID        : %d\n", r.id);
            printf("Name      : %s\n", r.name);
            printf("PC No.    : %d\n", r.pcNo);
            printf("Login     : %s\n", r.login);
            printf("Logout    : %s\n", r.logout);
            printf("Amount    : %d\n", r.amount);
            printf("-------------------------------------------\n");
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nNo record found for ID %d\n", id);
}

// ------------------------------------------------------------
// Update Record by ID
// ------------------------------------------------------------
void updateRecord() {
    int id, found = 0;
    struct CyberRecord r;
    FILE *fp = fopen("records.dat", "rb+");

    header();
    printf("=============== UPDATE RECORD ===============\n");
    printf("Enter User ID to update: ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            found = 1;
            printf("\nEnter new details:\n");

            printf("Name           : ");
            scanf("%s", r.name);

            printf("PC Number      : ");
            scanf("%d", &r.pcNo);

            printf("Login Time     : ");
            scanf("%s", r.login);

            printf("Logout Time    : ");
            scanf("%s", r.logout);

            printf("Amount         : ");
            scanf("%d", &r.amount);

            fseek(fp, -sizeof(r), SEEK_CUR);
            fwrite(&r, sizeof(r), 1, fp);

            printf("\nRecord updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nNo record found for ID %d\n", id);
    }
}

// ------------------------------------------------------------
// Delete Record by ID
// ------------------------------------------------------------
void deleteRecord() {
    int id, found = 0;
    struct CyberRecord r;
    FILE *fp = fopen("records.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    header();
    printf("=============== DELETE RECORD ===============\n");
    printf("Enter User ID to delete: ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            found = 1;
            continue; // skip writing record to delete
        }
        fwrite(&r, sizeof(r), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("records.dat");
    rename("temp.dat", "records.dat");

    if (found)
        printf("\nRecord deleted successfully!\n");
    else
        printf("\nNo record found for ID %d\n", id);
}