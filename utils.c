// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

// Check if string ends in tile
int check_tilda (char *string) {
    if (string[strlen (string) - 2] == '~')
        return 1;
    
    return 0;
}

// Create structure info of a book
book *create_book (FILE *in, char *buffer) {
    book *info = NULL;
    char *token;

    info = (book *) calloc (1, sizeof (book));
    if (!info) return NULL;
    token = strtok (NULL, ":\n");
    
    info->title = (char *) calloc (strlen (token) + 1, sizeof (char));
    if (!(info->title)) return NULL;
    strcpy (info->title, token);

    token = strtok (NULL, ":\n");
    info->author = (char *) calloc (strlen (token) + 1, sizeof (char));
    if (!(info->author)) return NULL;
    strcpy (info->author, token);

    info->rating = atoi (strtok (NULL, ":\n"));
    info->pag = atoi (strtok (NULL, ":\n"));

    return info;
}

// Read data about book and add it in book trie and author trie
void add_book (FILE *in, char *buffer, Trie tri1, Trie tri2) {
    book *info = create_book (in, buffer);
    Trie ver = NULL;
    char *string = NULL;

    string = (char *) calloc (SIZE, sizeof (char));
    if (!string) return;
    strcpy (string, info->title);
    insert (tri1, string, info);

    strcpy (string, info->author);
    ver = search (tri2, string);
    if (!ver) {
        ver = alocNode ();
        strcpy (string, info->title);
        insert (ver, string, info);
        strcpy (string, info->author);
        insert (tri2, string, ver);
    } else {
        strcpy (string, info->title);
        insert (ver, string, info);
    }

    free (string);
    return;
}

// Search for a certain book in book trie, if it exists show info
void search_book (FILE *in, FILE *out, Trie tri, char *key) {
    book *show = NULL;
    char *title = NULL;

    title = (char *) calloc (strlen (key) + 1, sizeof (char));
    if (!(title)) return;
    strcpy (title, key);

    show = search (tri, title);
    if (!(show))
        fprintf (out, "Cartea %s nu exista in recomandarile tale.\n", key);
    else
        fprintf (out, "Informatii recomandare: %s, %s, %d, %d\n",
                        show->title, show->author, show->rating, show->pag);

    free (title);
    return;
}

// Search all books with prefix given and print the first three maximum
void search_book_pre (FILE *out, Trie tri, char *key) {
    int flag = CONT, out_rule = SEARCH_;
    char **array = NULL;
    char *copy = NULL;

    copy = (char *) calloc (strlen (key) + 1, sizeof (char));
    if (!copy) return;
    strcpy (copy, key);
    array = (char **) calloc (ARRAY_STR, sizeof (void *));
    if (!array) return;

    search_pref (tri, copy, array, &flag, &out_rule);
    if (!flag) fprintf (out, "Nicio carte gasita.\n");
    else
        for (int i = 0; i < flag; i++)
            fprintf (out, "%s\n", ((book *) array[i])->title);

    free (array);
    return;
}

// Recursive search through trie to find all possible authors
void pre_auth_rec (Trie trie, char *array, char *key,
                    int *flag, int *out_rule, FILE *out) {

    if (*(out_rule) == 0) return;
    if (strlen (key) == 0) {
        if (trie->isEnd) {
            fprintf (out, "%s\n", array);
            (*flag)++;
            if ((*flag) == NUM_PAR) {
                *(out_rule) = 0;
                return;
            }
            for (int i = 0; i < CHIL_SIZ; i++)
                if (trie->children[i]) {
                    array[strlen (array)] = int_char (i);
                    pre_auth_rec (trie->children[i], array, key,
                                        flag, out_rule, out);
                }
            array[strlen (array) - 1] = '\0';
            return;
        } else {
            for (int i = 0; i < CHIL_SIZ; i++)
                if (trie->children[i]) {
                    array[strlen (array)] = int_char (i);
                    pre_auth_rec (trie->children[i], array, key, flag, out_rule, out);
                }

            array[strlen (array) - 1] = '\0';
            return;
        }
    }

    Trie next_ch = NULL;
    int poz = char_int (*key);

    if (!(trie->children[poz])) {
        *(out_rule) = 0;
        return;
    }
    next_ch = trie->children[poz];

    if (!(next_ch) || !(next_ch->children)) {
        *(out_rule) = 0;
        return;
    }

    pre_auth_rec (next_ch, array, key + 1, flag, out_rule, out);
}

// List all authors by prefix given, if possible and limited by maximum 3
void search_author_pre (Trie tri, FILE *out, char *key) {
    int flag = CONT, out_rule = SEARCH_;
    char *array = NULL;
    
    if (key[strlen (key) - 1] == '~')
        key[strlen (key) - 1] = '\0';

    array = (char *) calloc (SIZE, sizeof (char));
    if (!array) return;
    strcpy (array, key);

    pre_auth_rec (tri, array, key, &flag, &out_rule, out);
    if (!flag) fprintf (out, "Niciun autor gasit.\n");
    
    free (array);
    return;
}

// Prints from a trie all books' titles existed
void find_titles (FILE *out, Trie tri) {
    if (tri->isEnd == INFO) {
        book *info;

        info = tri->info;
        fprintf (out, "%s\n", info->title);
        return;
    }

    for (int i = 0; i < CHIL_SIZ; i++)
        if (tri->children[i])
            find_titles (out, tri->children[i]);

    return;
}

// List all books of author given, if existed
void list_author (FILE *out, Trie tri, char *key) {
    Trie aux;

    key[strlen (key) - 1] = '\0';
    aux = search (tri, key);
    if (!(aux)) {
        fprintf (out, "Autorul %s nu face parte din recomandarile tale.\n",
                                key);
        return;
    }
    find_titles (out, aux);

    return;
}

// Search in trie by author and then in the trie of the author by book
void search_by_author (FILE *out, Trie tri, char *token) {
    Trie data;
    book *info;

    token = strtok (token, ":");
    data = search (tri, token);
    if (!data) {
        fprintf (out, "Autorul %s nu face parte din recomandarile tale.\n",
                        token);
        return;
    }

    token = strtok (NULL, ":\n");
    info = search (data, token);
    if (!info)
        fprintf (out, "Cartea %s nu exista in recomandarile tale.\n", token);
    else 
        fprintf (out, "Informatii recomandare: %s, %s, %d, %d\n",
                        info->title, info->author, info->rating, info->pag);

    return;
}

// Takes as first key the author's name and the searches in trie the books
void search_by_author_pref (FILE *out, Trie tri, char *key) {
    char *token;
    Trie info = NULL;

    token = strtok (key, ":~");
    info = search (tri, token);
    if (!info) {
        fprintf (out, "Autorul %s nu face parte din recomandarile tale.\n", token);
        return;
    }

    token = strtok (NULL, ":~");
    search_book_pre (out, info, token);

    return;
}