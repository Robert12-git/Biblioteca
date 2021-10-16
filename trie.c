// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

// Convert character to position in array
int char_int (char key) {
    if (key <= 'z' && key >= 'a')
        return (key - 'a');
    else if (key <= 'Z' && key >= 'A')
        return (key - 'A' + SET_UP);
    else if (key <= '9' && key >= '0')
        return (key -'0' + SET_NUM);
    else if (key == '.')
        return DOT;
    else if (key == '-')
        return LINE;
    else if (key == '\'')
        return APOSTROPHE;
    else if (key == '?')
        return QUESTION;
    else if (key == '!')
        return EXCLAMATION;
    else return SPACE;
}

// Convert position in array to character
char int_char (int poz) {
    if (poz <= LOWER)
        return (poz + 'a');
    else if (poz <= UPPER)
        return (poz + 'A' - SET_UP);
    else if (poz <= NUMBERS)
        return (poz + '0' - SET_NUM);
    else if (poz == DOT)
        return ('.');
    else if (poz == LINE)
        return ('-');
    else if (poz == APOSTROPHE)
        return ('\'');
    else if (poz == QUESTION)
        return ('?');
    else if (poz == EXCLAMATION)
        return ('!');
    else if (poz == SPACE)
        return (' ');

    return 0;
}

// Create tree
Trie alocNode() {
    Trie trie = NULL;
    
    trie = (Trie) calloc (BLOCK, sizeof (_trie));
    if (!trie) return NULL;

    trie->children = (Trie *) calloc (CHIL_SIZ, sizeof (Trie));
    if (!(trie->children)) return NULL;

    trie->info = NULL;
    trie->isEnd = NO_INFO;

    return trie;
}

// Insert data in trie
void insert(Trie trie, char *key, void *info) {
    if (strlen (key) == NO_LENGTH) {
        trie->info = info;
        trie->isEnd = INFO;
        return;
    }

    Trie next_ch = NULL;
    int poz = char_int (*key);

    if (!(trie->children[poz]))
        trie->children[poz] = alocNode ();
    next_ch = trie->children[poz];

    insert (next_ch, ++key, info);
    return;
}

// Serch by key for specific data an return it
void *search(Trie trie, char *key) { 
    if (strlen (key) == NO_LENGTH)
        return trie->info;

    Trie next_ch = NULL;
    int poz = char_int (*key);

    if (!(trie->children[poz])) return NULL;
    next_ch = trie->children[poz];

    if (!(next_ch)) return NULL;
    return search(next_ch, ++key);
}

// Same as search, but hold data in array
void search_pref (Trie trie, char *key, char **data, int *flag, int *out_rule) {
    if (*(out_rule) == GET_OUT) return;

    if (strlen (key) == NO_LENGTH) {
        if (trie->isEnd) {
            data[*flag] = trie->info;
            (*flag)++;
            if ((*flag) == FULL_BUFFER) {
                *(out_rule) = GET_OUT;
                return;
            }

            for (int i = 0; i < CHIL_SIZ; i++)
                if (trie->children[i])
                    search_pref (trie->children[i], key, data, flag, out_rule);

            return;
        } else {
            for (int i = 0; i < CHIL_SIZ; i++)
                if (trie->children[i])
                    search_pref (trie->children[i], key, data, flag, out_rule);
            
            return;
        }
    }

    Trie next_ch = NULL;
    int poz = char_int (*key);
        
    if (!(trie->children[poz])) {
        *(out_rule) = GET_OUT;
        return;
    }
    next_ch = trie->children[poz];

    if (!(next_ch) || !(next_ch->children)) {
        *(out_rule) = GET_OUT;
        return;
    }

    search_pref(next_ch, ++key, data, flag, out_rule);  
}