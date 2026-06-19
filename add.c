#include "header.h"

void book_add(struct Book **ptr)
{
    struct Book *node = (struct Book *)malloc(sizeof(struct Book));
    node->next = 0;

    /* generate unique random 6-digit ID */
    srand((unsigned int)time(0));
    int id;
    do {
        id = 100000 + rand() % 900000;   /* 100000 – 999999 */
        struct Book *cur = *ptr;
        int taken = 0;
        while (cur) { if (cur->id == id) { taken = 1; break; } cur = cur->next; }
        if (!taken) break;
    } while (1);
    node->id = id;

    printf("\n*** ADD NEW BOOK ***\n");
    printf("Enter Title   : "); scanf(" %[^\n]", node->title);
    printf("Enter Author  : "); scanf(" %[^\n]", node->author);
    printf("Enter Quantity: "); scanf("%d", &node->quantity);

    if (*ptr == 0)
    {
        *ptr = node;
    }
    else
    {
        struct Book *last = *ptr;
        while (last->next) last = last->next;
        last->next = node;
    }

    printf("\nBook added successfully! Assigned Book ID: %d\n", node->id);
    print_book(node);
}
