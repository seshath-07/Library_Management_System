#include "header.h"

#define DUE_DAYS  7
#define LATE_FEE  2

void issue_book(struct Book **bptr, struct Issue **iptr)
{
    printf("\n*** ISSUE BOOK ***\n");

    int book_id;
    printf("Enter Book ID: "); scanf("%d", &book_id);
    struct Book *book = *bptr;
    while (book && book->id != book_id) book = book->next;
    if (!book) { printf("Book ID %d not found.\n", book_id); return; }
    if (book->quantity <= 0) { printf("No copies available for '%s'.\n", book->title); return; }

    print_book(book);

    struct Issue *node = (struct Issue *)malloc(sizeof(struct Issue));
    node->next     = 0;
    node->issue_id = get_next_issue_id(*iptr);
    node->book_id  = book_id;

    printf("Enter User ID  : "); scanf("%d",      &node->user_id);
    printf("Enter User Name: "); scanf(" %[^\n]",  node->user_name);

    get_today(node->issue_date);
    add_days(node->issue_date, DUE_DAYS, node->due_date);
    strcpy(node->return_date, "N/A");

    book->quantity--;

    if (*iptr == 0)
        *iptr = node;
    else
    {
        struct Issue *last = *iptr;
        while (last->next) last = last->next;
        last->next = node;
    }

    printf("\nBook issued successfully!\n");
    print_issue(node);
    printf("Remaining copies: %d\n", book->quantity);
}

void return_book(struct Book **bptr, struct Issue **iptr)
{
    printf("\n*** RETURN BOOK ***\n");

    int book_id, user_id;
    printf("Enter Book ID: "); scanf("%d", &book_id);
    printf("Enter User ID: "); scanf("%d", &user_id);

    struct Issue *rec = *iptr;
    while (rec)
    {
        if (rec->book_id == book_id &&
            rec->user_id == user_id &&
            strcmp(rec->return_date, "N/A") == 0)
            break;
        rec = rec->next;
    }
    if (!rec) { printf("No active issue for Book ID %d / User ID %d.\n", book_id, user_id); return; }

    char today[20];
    get_today(today);
    strcpy(rec->return_date, today);

    struct Book *book = *bptr;
    while (book && book->id != book_id) book = book->next;
    if (book) book->quantity++;

    int late = days_between(rec->due_date, today);
    printf("\nBook returned successfully!\n");
    print_issue(rec);
    if (late > 0)
        printf("*** Late by %d day(s). Late fee: Rs.%d ***\n", late, late * LATE_FEE);
    else
        printf("Returned on time. No late fee.\n");
}

void list_issued(struct Issue *ptr)
{
    if (!ptr) { printf("No issue records found.\n"); return; }

    printf("\n*** LIST OF ISSUED BOOKS ***\n");
    printf("+----------+--------+--------+--------------------+------------+------------+------------+\n");
    printf("| %-8s | %-6s | %-6s | %-18s | %-10s | %-10s | %-10s |\n",
           "IssueID","BookID","UserID","UserName","IssueDate","DueDate","ReturnDate");
    printf("+----------+--------+--------+--------------------+------------+------------+------------+\n");
    while (ptr)
    {
        printf("| %-8d | %-6d | %-6d | %-18s | %-10s | %-10s | %-10s |\n",
               ptr->issue_id, ptr->book_id, ptr->user_id, ptr->user_name,
               ptr->issue_date, ptr->due_date, ptr->return_date);
        ptr = ptr->next;
    }
    printf("+----------+--------+--------+--------------------+------------+------------+------------+\n");
}
