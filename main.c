// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

int main (int argc, char **argv) {
    if (argc != NUM_PAR)
        return ERROR;

    FILE *in = NULL, *out = NULL;
    char *buffer = NULL, *token;
    Trie trie1 = alocNode (), trie2 = alocNode ();
    int flag, tilda;

    in = fopen (argv[1], "rt");
    if (!in) return ERROR;

    out = fopen (argv[2], "wt");
    if (!out) {
        fclose (in);
        return ERROR;
    }

    buffer = (char *) calloc (SIZE, sizeof (char));
    if (!buffer) {
        fclose (out);
        fclose (in);
        return ERROR;
    }

    // Read each command and read data needed
    while (fgets (buffer, SIZE, in)) {
        tilda = check_tilda (buffer);
        token = strtok (buffer, " ");
        flag = SEARCH_;

        if (strcmp (token, "add_book") == EVEN)
            add_book (in, buffer, trie1, trie2);

        else if (strcmp (buffer, "search_book") == 0) {
            token = strtok (NULL, "~\n");

            // If string ends with prefix go to auto-complete case
            if (tilda) {
                search_book_pre (out, trie1, token);
            } else
                search_book (in, out, trie1, token);

        } else if (strcmp (buffer, "list_author") == EVEN) {
            token = strtok (NULL, "~");

            // If string ends with prefix go to auto-complete case
            if (tilda) {
                search_author_pre (trie2, out, token);
            } else
                list_author (out, trie2, token);

        } else if (strcmp (buffer, "search_by_author") == EVEN) {
            token = strtok (NULL, "\n");

            // If string ends with prefix go to auto-complete case
            if (tilda) {
                for (int i = 0; i < strlen (token); i++) {

                    // If search prefix title with autor
                    if (token[i] == ':') {
                        flag = OUT_SEARCH;
                        search_by_author_pref (out, trie2, token);
                        break;
                    }
                }
                // Else
                if (flag == SEARCH_)
                    search_author_pre (trie2, out, token);

            } else
                search_by_author (out, trie2, token);
        }
    }

    fclose (out);
    fclose (in);
    free (buffer);

    return 0;
}