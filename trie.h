// CIUREA Robert-Mihai - 313CBb
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TRIE__
#define TRIE__

#define CHIL_SIZ 68
#define ALPHABET_SIZE 26
#define BLOCK 1
#define LOWER 25
#define UPPER 51
#define SET_UP 26
#define NUMBERS 61
#define SET_NUM 52
#define DOT 62
#define LINE 63
#define APOSTROPHE 64
#define QUESTION 65
#define EXCLAMATION 66
#define SPACE 67
#define NO_INFO 0
#define INFO 1
#define NO_LENGTH 0
#define GET_OUT 0
#define FULL_BUFFER 3

typedef struct tr {
    struct tr **children;
    void *info;
    int isEnd;
} _trie, *Trie;

int char_int (char);
char int_char (int);
Trie alocNode();
void insert(Trie, char *, void *);
void *search(Trie, char *);
void search_pref (Trie, char *, char **, int *, int *);

#endif