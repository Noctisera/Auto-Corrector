#include <stdio.h>
#include <string.h>

#include "mk_functions.h"

void execute_command(char *command, trie_t *trie) {
    if (strcmp(command, "INSERT") == 0) {
        /* Read the word */
        char word[NMAX];
        scanf("%s", word);

        /* Insert the word in the trie */
        insert_word(trie, word);
    }
    else if (strcmp(command, "LOAD") == 0) {
        /* Read the file name */
        char file_name[NMAX];
        fscanf(stdin, "%s", file_name);
        /* Open the file and read the words from it */
        FILE *file = fopen(file_name, "r");
        if (file == NULL) {
            printf("File not found\n");
            return;
        }

        /* Read all the words from the file */
        char word[NMAX];
        while (fscanf(file, "%s", word) != EOF) {
            /* Insert the word in the trie */
            insert_word(trie, word);
        }

        fclose(file);
    }
    else if (strcmp(command, "REMOVE") == 0) {
        /* Read the word */
        char word[NMAX];
        scanf("%s", word);

        /* Remove the word from the trie */
        remove_word(trie, word);
    }
    else if (strcmp(command, "AUTOCORRECT") == 0) {
        /* Read the word */
        char word[NMAX];
        scanf("%s", word);

        /* Read the maximum number of different letters */
        int max_diff;
        scanf("%d", &max_diff);

        autocorrect(trie, word, max_diff);
    }
    else if (strcmp(command, "AUTOCOMPLETE") == 0) {
        /* Read the prefix */
        char prefix[NMAX];
        scanf("%s", prefix);

        /* Read the criteria number */
        int criteria;
        scanf("%d", &criteria);
        autocomplete(trie, prefix, criteria);
    }
    else if (strcmp(command, "EXIT") == 0) {
        trie_free(&trie);
        return;
    }
    else {
        printf("No command found\n");
    }
}

int main(void) {
    /* Create the trie */
    trie_t *trie = trie_create(ALPHABET_SIZE, ALPHABET);

    /* Read the command */
    char command[NMAX];
    while (scanf("%s", command) != EOF) {
        /* Execute the command */
        execute_command(command, trie);
        if (strcmp(command, "EXIT") == 0) break;
    }
    return 0;
}