#include "header.h"

#define BOOKS_FILE  "books.txt"
#define ISSUES_FILE "issues.txt"

void save_books(struct Book *ptr)
{
    FILE *fp = fopen(BOOKS_FILE, "w");
    if (!fp) { printf("Error opening %s\n", BOOKS_FILE); return; }
    while (ptr)
    {
        fprintf(fp, "%d|%s|%s|%d\n", ptr->id, ptr->title, ptr->author, ptr->quantity);
        ptr = ptr->next;
    }
    fclose(fp);
    printf("Books saved to %s\n", BOOKS_FILE);
}

void load_books(struct Book **ptr)
{
    FILE *fp = fopen(BOOKS_FILE, "r");
    if (!fp) { printf("No existing book data found.\n"); return; }

    struct Book *last = 0;
    int id, qty; char title[100], author[100];

    while (fscanf(fp, "%d|%99[^|]|%99[^|]|%d\n", &id, title, author, &qty) == 4)
    {
        struct Book *node = (struct Book *)malloc(sizeof(struct Book));
        node->id = id; strcpy(node->title, title);
        strcpy(node->author, author); node->quantity = qty; node->next = 0;
        if (*ptr == 0) { *ptr = node; last = node; }
        else           { last->next = node; last = node; }
    }
    fclose(fp);
    printf("Books loaded from %s\n", BOOKS_FILE);
}

void save_issues(struct Issue *ptr)
{
    FILE *fp = fopen(ISSUES_FILE, "w");
    if (!fp) { printf("Error opening %s\n", ISSUES_FILE); return; }
    while (ptr)
    {
        fprintf(fp, "%d|%d|%d|%s|%s|%s|%s\n",
                ptr->issue_id, ptr->book_id, ptr->user_id,
                ptr->user_name, ptr->issue_date, ptr->due_date, ptr->return_date);
        ptr = ptr->next;
    }
    fclose(fp);
    printf("Issue records saved to %s\n", ISSUES_FILE);
}

void load_issues(struct Issue **ptr)
{
    FILE *fp = fopen(ISSUES_FILE, "r");
    if (!fp) { printf("No existing issue data found.\n"); return; }

    struct Issue *last = 0;
    int issue_id, book_id, user_id;
    char user_name[100], issue_date[20], due_date[20], return_date[20];

    while (fscanf(fp, "%d|%d|%d|%99[^|]|%19[^|]|%19[^|]|%19[^\n]\n",
                  &issue_id, &book_id, &user_id,
                  user_name, issue_date, due_date, return_date) == 7)
    {
        struct Issue *node = (struct Issue *)malloc(sizeof(struct Issue));
        node->issue_id = issue_id; node->book_id = book_id; node->user_id = user_id;
        strcpy(node->user_name, user_name); strcpy(node->issue_date, issue_date);
        strcpy(node->due_date, due_date); strcpy(node->return_date, return_date);
        node->next = 0;
        if (*ptr == 0) { *ptr = node; last = node; }
        else           { last->next = node; last = node; }
    }
    fclose(fp);
    printf("Issue records loaded from %s\n", ISSUES_FILE);
}
