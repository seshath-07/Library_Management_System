#include "header.h"

void get_today(char *buf)
{
    time_t t = time(0);
    struct tm *tm = localtime(&t);
    sprintf(buf, "%04d-%02d-%02d",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
}

void add_days(const char *date, int days, char *out)
{
    struct tm tm = {0};
    sscanf(date, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon  -= 1;
    tm.tm_mday += days;
    mktime(&tm);
    sprintf(out, "%04d-%02d-%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int days_between(const char *from, const char *to)
{
    struct tm t1 = {0}, t2 = {0};
    sscanf(from, "%d-%d-%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday);
    sscanf(to,   "%d-%d-%d", &t2.tm_year, &t2.tm_mon, &t2.tm_mday);
    t1.tm_year -= 1900; t1.tm_mon -= 1;
    t2.tm_year -= 1900; t2.tm_mon -= 1;
    time_t s1 = mktime(&t1);
    time_t s2 = mktime(&t2);
    return (int)((s2 - s1) / 86400);
}

int get_next_issue_id(struct Issue *ptr)
{
    int max = 0;
    while (ptr) { if (ptr->issue_id > max) max = ptr->issue_id; ptr = ptr->next; }
    return max + 1;
}

void print_book(struct Book *b)
{
    int tw = (int)strlen(b->title);  if (tw < 5)  tw = 5;
    int aw = (int)strlen(b->author); if (aw < 6)  aw = 6;

    /* border */
    printf("+--------+");
    for(int i=0;i<tw+2;i++) printf("-"); printf("+");
    for(int i=0;i<aw+2;i++) printf("-"); printf("+----------+\n");

    /* header */
    printf("| %-6s | %-*s | %-*s | %-8s |\n", "ID", tw, "Title", aw, "Author", "Qty");

    /* border */
    printf("+--------+");
    for(int i=0;i<tw+2;i++) printf("-"); printf("+");
    for(int i=0;i<aw+2;i++) printf("-"); printf("+----------+\n");

    /* data */
    printf("| %-6d | %-*s | %-*s | %-8d |\n", b->id, tw, b->title, aw, b->author, b->quantity);

    /* border */
    printf("+--------+");
    for(int i=0;i<tw+2;i++) printf("-"); printf("+");
    for(int i=0;i<aw+2;i++) printf("-"); printf("+----------+\n");
}

void print_issue(struct Issue *is)
{
    printf("+----------+--------+--------+--------------------+------------+------------+------------+\n");
    printf("| %-8s | %-6s | %-6s | %-18s | %-10s | %-10s | %-10s |\n",
           "IssueID","BookID","UserID","UserName","IssueDate","DueDate","ReturnDate");
    printf("+----------+--------+--------+--------------------+------------+------------+------------+\n");
    printf("| %-8d | %-6d | %-6d | %-18s | %-10s | %-10s | %-10s |\n",
           is->issue_id, is->book_id, is->user_id, is->user_name,
           is->issue_date, is->due_date, is->return_date);
    printf("+----------+--------+--------+--------------------+------------+------------+------------+\n");
}
