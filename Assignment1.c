#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define URL_SIZE 100

typedef struct Page {
    int id;
    char url[URL_SIZE];
    struct Page* next;
    struct Page* prev;
} Page;

int main() {
    int choice;
    int page_id = 1; // Unique identifier for each page
    // Initialize the current page to NULL
    // This will represent the current tab in the browser
    Page* current = NULL;
    do {
        printf("Menu:\n");
        printf("1. Visit a new page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show current tab\n");
        printf("5. Close current tab\n");
        printf("6. Show history\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char url[URL_SIZE];
                printf("Enter page URL: ");
                scanf(" %[^\n]", url); // Reads input until newline

                Page* new_page = malloc(sizeof(Page));
                new_page->id = page_id++;
                strcpy(new_page->url, url);
                new_page->prev = current;
                new_page->next = NULL;
                if (current) current->next = new_page;
                current = new_page;

                printf("Visited new page!\nCurrent tab: [ID: %d] %s\n", current->id, current->url);
                break;
            }
            case 2:
                if (current && current->prev) {
                    current = current->prev;
                    printf("Went back!\nCurrent tab: [ID: %d] %s\n", current->id, current->url);
                } else if (current) {
                    printf("No previous page. You are at the first visited page: [ID: %d] %s\n", current->id, current->url);
                } else {
                    printf("No page open.\n");
                }
                break;
            case 3:
                if (current && current->next) {
                    current = current->next;
                    printf("Went forward!\nCurrent tab: [ID: %d] %s\n", current->id, current->url);
                } else if (current) {
                    printf("No next page. You are at the last visited page: [ID: %d] %s\n", current->id, current->url);
                } else {
                    printf("No page open.\n");
                }
                break;
            case 4:
                if (current) {
                    printf("Current tab: [ID: %d] %s\n", current->id, current->url);
                } else {
                    printf("No page open.\n");
                }
                break;
            case 5:
                if (current) {
                    Page* to_close = current;
                    if (current->prev) {
                        current = current->prev;
                        current->next = to_close->next;
                        if (to_close->next) {
                            to_close->next->prev = current;
                        }
                    } else if (current->next) {
                        current = current->next;
                        current->prev = NULL;
                    } else {
                        current = NULL;
                    }
                    printf("Closed tab: [ID: %d] %s\n", to_close->id, to_close->url);
                    free(to_close);
                    if (current)
                        printf("Current tab: [ID: %d] %s\n", current->id, current->url);
                    else
                        printf("No page open.\n");
                } else {
                    printf("No page open to close.\n");
                }
                break;
            case 6:
                printf("History of open pages:\n");
                if (!current) {
                    printf("No history available.\n");
                    break;
                }
                //Move to the first page
                Page* temp = current;
                while (temp && temp->prev) {
                    temp = temp->prev;
                }
                // Print the history
                while (temp) {
                    printf("[ID: %d] %s\n", temp->id, temp->url);
                    temp = temp->next;
                }
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}