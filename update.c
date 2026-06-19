#include "header.h"

static void do_update(struct Book *b)
{
    char ch;
    printf("\nCurrent record:\n");
    print_book(b);

    printf("\nWhat to update?\n");
    printf("  T. Title\n  A. Author\n  Q. Quantity\n");
    printf("Enter choice: "); scanf(" %c", &ch);

    switch (ch | 32)
    {
        case 't':
            printf("New Title: "); scanf(" %[^\n]", b->title);
            printf("Title updated.\n"); break;
        case 'a':
            printf("New Author: "); scanf(" %[^\n]", b->author);
            printf("Author updated.\n"); break;
        case 'q':
            printf("New Quantity: "); scanf("%d", &b->quantity);
            printf("Quantity updated.\n"); break;
        default:
            printf("Invalid choice.\n"); return;
    }
    printf("\nUpdated record:\n");
    print_book(b);
}

void book_update(struct Book **ptr)
{
    char ch;
    printf("\n+---------------------------+\n");
    printf("|   Update Book Details     |\n");
    printf("|---------------------------|\n");
    printf("| A. By Book ID             |\n");
    printf("| B. By Book Name           |\n");
    printf("| D. Back to Main Menu      |\n");
    printf("+---------------------------+\n");
    printf("Enter choice: "); scanf(" %c", &ch);

    switch (ch | 32)
    {
        case 'a': update_by_id(ptr);   break;
        case 'b': update_by_name(ptr); break;
        case 'd': break;
        default:  printf("Invalid choice.\n"); break;
    }
}

void update_by_id(struct Book **ptr)
{
    int id;
    printf("Enter Book ID: "); scanf("%d", &id);
    struct Book *cur = *ptr;
    while (cur && cur->id != id) cur = cur->next;
    if (!cur) { printf("Book ID %d not found.\n", id); return; }
    do_update(cur);
}

void update_by_name(struct Book **ptr)
{
    char title[100];
    printf("Enter Title: "); scanf(" %[^\n]", title);

    int count = 0, tw = 5, aw = 6;
    struct Book *cur = *ptr;
    while (cur)
    {
        if (strcasecmp(cur->title, title) == 0)
        {
            count++;
            int t = (int)strlen(cur->title);
            int a = (int)strlen(cur->author);
            if (t > tw) tw = t;
            if (a > aw) aw = a;
        }
        cur = cur->next;
    }

    if (count == 0) { printf("No book with title '%s' found.\n", title); return; }

    if (count == 1)
    {
        cur = *ptr;
        while (cur && strcasecmp(cur->title, title) != 0) cur = cur->next;
        do_update(cur);
    }
    else
    {
        printf("\nMultiple books with that title:\n");
        /* header */
        printf("+--------+");
        for(int i=0;i<tw+2;i++) printf("-"); printf("+");
        for(int i=0;i<aw+2;i++) printf("-"); printf("+----------+\n");
        printf("| %-6s | %-*s | %-*s | %-8s |\n", "ID", tw, "Title", aw, "Author", "Qty");
        printf("+--------+");
        for(int i=0;i<tw+2;i++) printf("-"); printf("+");
        for(int i=0;i<aw+2;i++) printf("-"); printf("+----------+\n");

        cur = *ptr;
        while (cur)
        {
            if (strcasecmp(cur->title, title) == 0)
                printf("| %-6d | %-*s | %-*s | %-8d |\n",
                       cur->id, tw, cur->title, aw, cur->author, cur->quantity);
            cur = cur->next;
        }
        printf("+--------+");
        for(int i=0;i<tw+2;i++) printf("-"); printf("+");
        for(int i=0;i<aw+2;i++) printf("-"); printf("+----------+\n");

        int id;
        printf("Enter Book ID to update: "); scanf("%d", &id);
        cur = *ptr;
        while (cur && cur->id != id) cur = cur->next;
        if (!cur) { printf("ID %d not found.\n", id); return; }
        do_update(cur);
    }
}
