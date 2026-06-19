#include "header.h"

/* ── find max title and author widths in the list ─────────── */
static void col_widths(struct Book *ptr, int *tw, int *aw)
{
    *tw = 5;   /* minimum = length of "Title" */
    *aw = 6;   /* minimum = length of "Author" */
    while (ptr)
    {
        int t = (int)strlen(ptr->title);
        int a = (int)strlen(ptr->author);
        if (t > *tw) *tw = t;
        if (a > *aw) *aw = a;
        ptr = ptr->next;
    }
}

static void print_border(int tw, int aw)
{
    printf("+--------+");
    for (int i = 0; i < tw+2; i++) printf("-"); printf("+");
    for (int i = 0; i < aw+2; i++) printf("-"); printf("+----------+\n");
}

static void print_header(int tw, int aw)
{
    print_border(tw, aw);
    printf("| %-6s | %-*s | %-*s | %-8s |\n", "ID", tw, "Title", aw, "Author", "Qty");
    print_border(tw, aw);
}

/* ── View All ─────────────────────────────────────────────── */
void book_view_all(struct Book *ptr)
{
    if (!ptr) { printf("No books in the catalog.\n"); return; }

    int tw, aw;
    col_widths(ptr, &tw, &aw);

    printf("\n*** ALL BOOKS ***\n");
    print_header(tw, aw);
    while (ptr)
    {
        printf("| %-6d | %-*s | %-*s | %-8d |\n",
               ptr->id, tw, ptr->title, aw, ptr->author, ptr->quantity);
        ptr = ptr->next;
    }
    print_border(tw, aw);
}

/* ── Search menu ──────────────────────────────────────────── */
void book_search(struct Book *ptr)
{
    char ch;
    printf("\n+---------------------------+\n");
    printf("|        Search Book        |\n");
    printf("|---------------------------|\n");
    printf("| A. By Book ID             |\n");
    printf("| B. By Book Name           |\n");
    printf("| C. By Author Name         |\n");
    printf("| D. Back to Main Menu      |\n");
    printf("+---------------------------+\n");
    printf("Enter choice: "); scanf(" %c", &ch);

    switch (ch | 32)
    {
        case 'a': search_by_id(ptr);     break;
        case 'b': search_by_name(ptr);   break;
        case 'c': search_by_author(ptr); break;
        case 'd': break;
        default:  printf("Invalid choice.\n"); break;
    }
}

void search_by_id(struct Book *ptr)
{
    int id;
    printf("Enter Book ID: "); scanf("%d", &id);
    while (ptr && ptr->id != id) ptr = ptr->next;
    if (!ptr) { printf("Book ID %d not found.\n", id); return; }
    print_book(ptr);
}

void search_by_name(struct Book *ptr)
{
    char title[100];
    printf("Enter Title: "); scanf(" %[^\n]", title);

    /* find matches to compute widths */
    struct Book *tmp = ptr;
    int tw = 5, aw = 6, found = 0;
    while (tmp)
    {
        if (strcasecmp(tmp->title, title) == 0)
        {
            int t = (int)strlen(tmp->title);
            int a = (int)strlen(tmp->author);
            if (t > tw) tw = t;
            if (a > aw) aw = a;
            found = 1;
        }
        tmp = tmp->next;
    }

    if (!found) { printf("No books found with title '%s'.\n", title); return; }

    print_header(tw, aw);
    while (ptr)
    {
        if (strcasecmp(ptr->title, title) == 0)
            printf("| %-6d | %-*s | %-*s | %-8d |\n",
                   ptr->id, tw, ptr->title, aw, ptr->author, ptr->quantity);
        ptr = ptr->next;
    }
    print_border(tw, aw);
}

void search_by_author(struct Book *ptr)
{
    char author[100];
    printf("Enter Author: "); scanf(" %[^\n]", author);

    struct Book *tmp = ptr;
    int tw = 5, aw = 6, found = 0;
    while (tmp)
    {
        if (strcasecmp(tmp->author, author) == 0)
        {
            int t = (int)strlen(tmp->title);
            int a = (int)strlen(tmp->author);
            if (t > tw) tw = t;
            if (a > aw) aw = a;
            found = 1;
        }
        tmp = tmp->next;
    }

    if (!found) { printf("No books found by author '%s'.\n", author); return; }

    print_header(tw, aw);
    while (ptr)
    {
        if (strcasecmp(ptr->author, author) == 0)
            printf("| %-6d | %-*s | %-*s | %-8d |\n",
                   ptr->id, tw, ptr->title, aw, ptr->author, ptr->quantity);
        ptr = ptr->next;
    }
    print_border(tw, aw);
}
