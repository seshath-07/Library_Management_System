#include "header.h"

static void unlink_book(struct Book **ptr, int id)
{
    struct Book *cur  = *ptr;
    struct Book *prev = 0;

    while (cur && cur->id != id) { prev = cur; cur = cur->next; }
    if (!cur) { printf("Book ID %d not found.\n", id); return; }

    print_book(cur);
    char confirm;
    printf("Confirm delete? (Y to confirm): "); scanf(" %c", &confirm);
    if ((confirm | 32) != 'y') { printf("Deletion cancelled.\n"); return; }

    if (prev) prev->next = cur->next;
    else      *ptr       = cur->next;

    printf("Book '%s' (ID %d) removed.\n", cur->title, cur->id);
    free(cur);
}

void book_remove(struct Book **ptr)
{
    char ch;
    printf("\n+---------------------------+\n");
    printf("|        Remove Book        |\n");
    printf("|---------------------------|\n");
    printf("| A. By Book ID             |\n");
    printf("| B. By Book Name           |\n");
    printf("| D. Back to Main Menu      |\n");
    printf("+---------------------------+\n");
    printf("Enter choice: "); scanf(" %c", &ch);

    switch (ch | 32)
    {
        case 'a': remove_by_id(ptr);   break;
        case 'b': remove_by_name(ptr); break;
        case 'd': break;
        default:  printf("Invalid choice.\n"); break;
    }
}

void remove_by_id(struct Book **ptr)
{
    int id;
    printf("Enter Book ID: "); scanf("%d", &id);
    unlink_book(ptr, id);
}

void remove_by_name(struct Book **ptr)
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
    printf("Enter Book ID to remove: "); scanf("%d", &id);
    unlink_book(ptr, id);
}
