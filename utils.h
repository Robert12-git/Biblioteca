// CIUREA Robert-Mihai - 313CBb
#include "trie.h"

#ifndef utils
#define utils

#define SIZE 250
#define NUM_PAR 3
#define ERROR -1
#define SEARCH_ 1
#define OUT_SEARCH 0
#define EVEN 0
#define ARRAY_STR 4
#define CONT 0
#define INFO 1

typedef struct BOOK {
    char *title;
    char *author;
    int rating;
    int pag;
} book;

int check_tilda (char *);
void add_book (FILE *, char *, Trie, Trie);
void search_book (FILE *, FILE *, Trie, char *);
void search_book_pre (FILE *, Trie, char *);
void list_author (FILE *, Trie, char *);
void search_by_author (FILE *, Trie, char *);
void search_author_pre (Trie, FILE *, char *);
void search_by_author_pref (FILE *, Trie, char *);

#endif