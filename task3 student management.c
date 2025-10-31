#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "students.dat"
struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
};
void addStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayStudents();
int isIdExists(int id);
int main() {
    int choice;
    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Search Student\n");
        printf("5. Display All Students\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                displayStudents();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
int isIdExists(int id) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) return 0;
    struct Student s;
    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (s.id == id) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void addStudent() {
    struct Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    getchar();
    if (isIdExists(s.id)) {
        printf("Student ID already exists!\n");
        return;
    }
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; 
    printf("Enter Age: ");
    scanf("%d", &s.age);
    getchar();
    printf("Enter Course: ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = 0; 
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&s, sizeof(struct Student), 1, file);
    fclose(file);
    printf("Student added successfully!\n");
}

void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temp file!\n");
        fclose(file);
        return;
    }
    struct Student s;
    int found = 0;
    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (s.id != id) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("Student deleted successfully!\n");
    } else {
        printf("Student ID not found!\n");
        remove("temp.dat");
    }
}

void updateStudent() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    getchar();
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temp file!\n");
        fclose(file);
        return;
    }
    struct Student s;
    int found = 0;
    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (s.id == id) {
            printf("Enter new Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter new Age: ");
            scanf("%d", &s.age);
            getchar();

            printf("Enter new Course: ");
            fgets(s.course, sizeof(s.course), stdin);
            s.course[strcspn(s.course, "\n")] = 0;

            found = 1;
        }
        fwrite(&s, sizeof(struct Student), 1, temp);
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("Student updated successfully!\n");
    } else {
        printf("Student ID not found!\n");
        remove("temp.dat");
    }
}

void searchStudent() {
    int choice;
    printf("Search by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);
    getchar();
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    struct Student s;
    int found = 0;
    if (choice == 1) {
        int id;
        printf("Enter Student ID: ");
        scanf("%d", &id);
        while (fread(&s, sizeof(struct Student), 1, file)) {
            if (s.id == id) {
                printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\n", s.id, s.name, s.age, s.course);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        char name[50];
        printf("Enter Student Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        while (fread(&s, sizeof(struct Student), 1, file)) {
            if (strcmp(s.name, name) == 0) {
                printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\n", s.id, s.name, s.age, s.course);
                found = 1;
            }
        }
    } else {
        printf("Invalid choice!\n");
        fclose(file);
        return;
    }

    if (!found) {
        printf("Student not found!\n");
    }
    fclose(file);
}
void displayStudents() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    struct Student s;
    printf("\n--- All Students ---\n");
    while (fread(&s, sizeof(struct Student), 1, file)) {
        printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\n\n", s.id, s.name, s.age, s.course);
    }
    fclose(file);
}

