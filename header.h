#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ─── Book record ─────────────────────────────────────────── */
struct Book {
    int   id;
    char  title[100];
    char  author[100];
    int   quantity;
    struct Book *next;
};

/* ─── Issue record ────────────────────────────────────────── */
struct Issue {
    int  issue_id;
    int  book_id;
    int  user_id;
    char user_name[100];
    char issue_date[20];
    char due_date[20];
    char return_date[20];
    struct Issue *next;
};

/* ─── Book functions ──────────────────────────────────────── */
void book_add      (struct Book **);
void book_update   (struct Book **);
void book_remove   (struct Book **);
void book_search   (struct Book *);
void book_view_all (struct Book *);

void update_by_id    (struct Book **);
void update_by_name  (struct Book **);
void remove_by_id    (struct Book **);
void remove_by_name  (struct Book **);
void search_by_id    (struct Book *);
void search_by_name  (struct Book *);
void search_by_author(struct Book *);

/* ─── Issue functions ─────────────────────────────────────── */
void issue_book  (struct Book **, struct Issue **);
void return_book (struct Book **, struct Issue **);
void list_issued (struct Issue *);

/* ─── Persistence ─────────────────────────────────────────── */
void save_books  (struct Book *);
void load_books  (struct Book **);
void save_issues (struct Issue *);
void load_issues (struct Issue **);

/* ─── Utilities ───────────────────────────────────────────── */
void get_today        (char *buf);
void add_days         (const char *date, int days, char *out);
int  days_between     (const char *from, const char *to);
int  get_next_issue_id(struct Issue *);
void print_book       (struct Book *);
void print_issue      (struct Issue *);

#endif
