#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookId;
    char title[50];
    char author[50];
    int quantity;
};

void addBook();
void displayBooks();
void issueBook();
void returnBook();
void deleteBook();

int main() {
    int choice;

    do {
        printf("\n====== LIBRARY MANAGEMENT SYSTEM ======\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Delete Book\n");
        printf("0. Exit\n");
        printf("======================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: deleteBook(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

/* ADD BOOK */
void addBook() {
    FILE *fp;
    struct Book b;

    fp = fopen("books.txt", "a");

    printf("Enter Book ID: ");
    scanf("%d", &b.bookId);
    printf("Enter Book Title: ");
    scanf("%s", b.title);
    printf("Enter Author Name: ");
    scanf("%s", b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fprintf(fp, "%d %s %s %d\n",
            b.bookId, b.title, b.author, b.quantity);

    fclose(fp);
    printf("Book added successfully!\n");
}

/* DISPLAY BOOKS */
void displayBooks() {
    FILE *fp;
    struct Book b;

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No book records found.\n");
        return;
    }

    printf("\nID   Title        Author       Quantity\n");
    printf("----------------------------------------\n");

    while (fscanf(fp, "%d %s %s %d",
                  &b.bookId, b.title, b.author, &b.quantity) != EOF) {

        printf("%-4d %-12s %-12s %-5d\n",
               b.bookId, b.title, b.author, b.quantity);
    }

    fclose(fp);
}

/* ISSUE BOOK */
void issueBook() {
    FILE *fp, *temp;
    struct Book b;
    int id, found = 0;

    fp = fopen("books.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("No book records found.\n");
        return;
    }

    printf("Enter Book ID to Issue: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %s %d",
                  &b.bookId, b.title, b.author, &b.quantity) != EOF) {

        if (b.bookId == id && b.quantity > 0) {
            b.quantity--;
            found = 1;
            printf("Book issued successfully!\n");
        }

        fprintf(temp, "%d %s %s %d\n",
                b.bookId, b.title, b.author, b.quantity);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        printf("Book not available or invalid ID.\n");
}

/* RETURN BOOK */
void returnBook() {
    FILE *fp, *temp;
    struct Book b;
    int id, found = 0;

    fp = fopen("books.txt", "r");
    temp = fopen("temp.txt", "w");

    printf("Enter Book ID to Return: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %s %d",
                  &b.bookId, b.title, b.author, &b.quantity) != EOF) {

        if (b.bookId == id) {
            b.quantity++;
            found = 1;
            printf("Book returned successfully!\n");
        }

        fprintf(temp, "%d %s %s %d\n",
                b.bookId, b.title, b.author, b.quantity);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        printf("Invalid Book ID.\n");
}

/* DELETE BOOK */
void deleteBook() {
    FILE *fp, *temp;
    struct Book b;
    int id, found = 0;

    fp = fopen("books.txt", "r");
    temp = fopen("temp.txt", "w");

    printf("Enter Book ID to Delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %s %d",
                  &b.bookId, b.title, b.author, &b.quantity) != EOF) {

        if (b.bookId == id) {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %s %s %d\n",
                b.bookId, b.title, b.author, b.quantity);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found.\n");
}
