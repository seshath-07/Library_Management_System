#include "header.h"

int main(void)
{
    struct Book  *books  = 0;
    struct Issue *issues = 0;

    load_books(&books);
    load_issues(&issues);

    char ch;

    while (1)
    {
        printf("\n\t+----------------------------------------+\n");
        printf("\t|        Book Management Menu            |\n");
        printf("\t|----------------------------------------|\n");
        printf("\t| 1. Add New Book                        |\n");
        printf("\t| 2. Update Book Details                 |\n");
        printf("\t| 3. Remove Book                         |\n");
        printf("\t| 4. Search Book                         |\n");
        printf("\t| 5. View All Books                      |\n");
        printf("\t| 6. Issue Book                          |\n");
        printf("\t| 7. Return Book                         |\n");
        printf("\t| 8. List Issued Books                   |\n");
        printf("\t| 9. Save                                |\n");
        printf("\t| 0. Exit                                |\n");
        printf("\t+----------------------------------------+\n");
        printf("\tEnter option: ");
        scanf(" %c", &ch);

        switch (ch)
        {
            case '1': book_add(&books);                   break;
            case '2': book_update(&books);                break;
            case '3': book_remove(&books);                break;
            case '4': book_search(books);                 break;
            case '5': book_view_all(books);               break;
            case '6': issue_book(&books, &issues);        break;
            case '7': return_book(&books, &issues);       break;
            case '8': list_issued(issues);                break;
            case '9':
                save_books(books);
                save_issues(issues);
                break;
            case '0':
            {
                char confirm;
                printf("Save before exiting? (Y/N): "); scanf(" %c", &confirm);
                if ((confirm | 32) == 'y')
                {
                    save_books(books);
                    save_issues(issues);
                }
                printf("Saved and exited\n");
                exit(0);
            }
            default:
                printf("Invalid option. Try again.\n");
                break;
        }
    }

    return 0;
}
