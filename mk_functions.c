#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mk_functions.h"

/* Magic Keyboard functions */

void insert_word(trie_t *trie, char *word) {
    trie_insert(trie, word);
}

void remove_word(trie_t *trie, char *word) {
    trie_remove(trie, word);
}

void autocorrect(trie_t *trie, char word[], int k) {
    /* Prints the words from the trie that are at most k different from word */
    /* The words are printed in lexicographical order */
    char curr_word[NMAX];
    curr_word[0] = '\0';
    int condition = 0;
    autocorrect_rec(trie, trie->root, word, k, 0, curr_word, &condition);
    if (condition == 0) {
        printf("No words found\n");
    }
}

void autocorrect_rec(trie_t *trie, trie_node_t *node, char word[], int k,
                     int diff, char curr_word[], int *condition) {
    /* Recursive function that prints the words from the trie that are at most k
     * different from word */
    /* The words are printed in lexicographical order */
    if (node == NULL) {
        return;
    }
    if (strlen(curr_word) == strlen(word) && node->word_counter > 0) {
        if (diff <= k) {
            printf("%s\n", curr_word);
            *condition = 1;
        }
        return;
    }

    unsigned int size = strlen(curr_word);

    for (int i = 0; i < trie->alphabet_size; i++) {
        if (node->children[i] != NULL) {
            curr_word[size] = node->children[i]->letter;
            curr_word[size + 1] = '\0';
            if (size <= strlen(word)) {
                if (node->children[i]->letter != word[size]) {
                    autocorrect_rec(trie, node->children[i], word, k, diff + 1, curr_word,
                                    condition);
                } else {
                    autocorrect_rec(trie, node->children[i], word, k, diff, curr_word,
                                    condition);
                }
            }
        }
    }
}

void autocomplete(trie_t *trie, char *prefix, int criteria) {
    /* Prints the words from the trie that start with prefix, depending on the
     * criteria */
    if (trie->root == NULL) {
        return;
    }

    if (criteria == 1 || criteria == 0) {
        /* Prints the lowest lexicographical word that starts with prefix */
        char curr_word[NMAX];
        for (int i = 0; i < strlen(prefix); i++) {
            curr_word[i] = prefix[i];
        }
        curr_word[strlen(prefix)] = '\0';

        /* Go the node of the end of the prefix */
        trie_node_t *node = trie->root;
        for (int i = 0; i < strlen(prefix); i++) {
            if (node == NULL) {
                return;
            }
            node = node->children[prefix[i] - 'a'];
        }

        char *result = lowest_lexicographic(trie, node, prefix, curr_word);
        if (result != NULL) {
            printf("%s\n", result);
        } else {
            printf("No words found\n");
        }
    }
    if (criteria == 2 || criteria == 0) {
        /* Prints the shortest word that starts with the prefix */
        char curr_word[NMAX];
        for (int i = 0; i < strlen(prefix); i++) {
            curr_word[i] = prefix[i];
        }
        curr_word[strlen(prefix)] = '\0';

        /* Go the node of the end of the prefix */
        trie_node_t *node = trie->root;
        for (int i = 0; i < strlen(prefix); i++) {
            if (node == NULL) {
                return;
            }
            node = node->children[prefix[i] - 'a'];
        }

        char *result = shortest_word(trie, node, prefix, curr_word);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("No words found\n");
        }
    }
    if (criteria == 3 || criteria == 0) {
        /* Prints the most frequent word that starts with the prefix */
        /* In case of equality, print the lowest lexicographical word */
        /* Returns the node of the end of the word to then build it here */
        char curr_word[NMAX];
        for (int i = 0; i < strlen(prefix); i++) {
            curr_word[i] = prefix[i];
        }
        curr_word[strlen(prefix)] = '\0';

        /* Go the node of the end of the prefix */
        trie_node_t *node = trie->root;
        for (int i = 0; i < strlen(prefix); i++) {
            if (node == NULL) {
                return;
            }
            node = node->children[prefix[i] - 'a'];
        }

        trie_node_t *result = most_frequent_word(trie, node, prefix);

        if (result != NULL) {
            /* Print the word from root to the letter of the word */
            char word[NMAX];
            word[0] = '\0';

            /* The initial word will be reversed */
            node = result;
            int i = 0;
            while (node != NULL) {
                word[i] = node->letter;
                node = node->parent;
                i++;
            }
            word[i] = '\0';

            /* Reverse the word */
            char reversed_word[NMAX];
            reversed_word[0] = '\0';
            for (i = strlen(word) - 1; i >= 0; i--) {
                unsigned int size = strlen(reversed_word);
                reversed_word[size] = word[i];
                reversed_word[size + 1] = '\0';
            }

            printf("%s\n", reversed_word);
        } else {
            printf("No words found\n");
        }
    }
}

char *lowest_lexicographic(trie_t *trie, trie_node_t *node, char *prefix, char curr_word[]) {
    /* Recursive function that returns the lowest lexicographical word that starts
     * with prefix */
    if (node == NULL) {
        return NULL;
    }
    if (node->word_counter > 0) {
        return curr_word;
    }

    unsigned int size = strlen(curr_word);

    for (int i = 0; i < trie->alphabet_size; i++) {
        if (node->children[i] != NULL) {
            /* Put the next letter in the word */
            curr_word[size] = node->children[i]->letter;
            curr_word[size + 1] = '\0';

            char *result =
                    lowest_lexicographic(trie, node->children[i], prefix, curr_word);
            if (result != NULL) {
                return result;
            }
        }
    }
    return NULL;
}

char *shortest_word(trie_t *trie, trie_node_t *node, char *prefix, char curr_word[]) {
    /* Recursive function that returns the shortest word that starts with prefix
     */
    if (node == NULL) {
        return NULL;
    }
    if (node->word_counter > 0) {
        char *return_word = NULL;
        return_word = malloc(sizeof(char) * NMAX);
        if (return_word == NULL) {
            printf("Malloc failed for return_word in shortes_word\n");
            exit(1);
        }
        memccpy(return_word, curr_word, '\0', NMAX);
        return return_word;
    }

    char aux_word[NMAX];
    for (int i = 0; i < strlen(curr_word); i++) {
        aux_word[i] = curr_word[i];
    }
    aux_word[strlen(curr_word)] = '\0';
    unsigned int size = strlen(aux_word);
    char *result = NULL;

    for (int i = 0; i < trie->alphabet_size; i++) {
        if (node->children[i] != NULL) {
            /* Put the next letter in the word */
            aux_word[size] = node->children[i]->letter;
            aux_word[size + 1] = '\0';

            char *partial_result = NULL;
            partial_result = shortest_word(trie, node->children[i], prefix, aux_word);

            if (partial_result != NULL) {
                if (result == NULL) {
                    result = partial_result;
                } else {
                    unsigned int len1 = strlen(result);
                    unsigned int len2 = strlen(partial_result);
                    if (len2 < len1) {
                        free(result);
                        result = partial_result;
                    } else {
                        free(partial_result);
                    }
                }
            }
        }
    }
    if (result != NULL) {
        return result;
    }
    return NULL;
}

trie_node_t *most_frequent_word(trie_t *trie, trie_node_t *node, char *prefix) {
    /* Recursive function that returns the node of the end of the word that starts
     * with prefix */
    /* In case of equality, return the lowest lexicographical word */
    if (node == NULL) {
        return NULL;
    }
    trie_node_t *result = NULL;

    if (node->word_counter > 0) {
        result = node;
    }

    for (int i = 0; i < trie->alphabet_size; i++) {
        if (node->children[i] != NULL) {
            trie_node_t *partial_result =
                    most_frequent_word(trie, node->children[i], prefix);

            if (partial_result != NULL) {
                if (result == NULL) {
                    result = partial_result;
                }
                else if (partial_result->word_counter > result->word_counter) {
                    result = partial_result;
                }
                else if (partial_result->word_counter == result->word_counter) {
                    if (compare_words(partial_result, result) == 0) {
                        result = partial_result;
                    }
                }
            }
        }
    }
    if (result != NULL) {
        return result;
    }
    return NULL;
}

int compare_words(trie_node_t *node1, trie_node_t *node2) {
    /* Compares two words lexicographically */
    /* Returns 0 if the first word is lexicographically smaller than the second */
    /* Returns 1 if the second word is lexicographically smaller than the first */

    char word1[NMAX];
    char word2[NMAX];

    trie_node_t *node = node1;
    int i = 0;
    while (node != NULL) {
        word1[i] = node->letter;
        node = node->parent;
        i++;
    }
    word1[i] = '\0';

    node = node2;
    i = 0;
    while (node != NULL) {
        word2[i] = node->letter;
        node = node->parent;
        i++;
    }
    word2[i] = '\0';

    /* Reverse the words */
    char aux[NMAX];
    for (i = 0; i < strlen(word1); i++) {
        aux[i] = word1[strlen(word1) - i - 1];
    }
    aux[strlen(word1)] = '\0';
    strcpy(word1, aux);

    for (i = 0; i < strlen(word2); i++) {
        aux[i] = word2[strlen(word2) - i - 1];
    }
    aux[strlen(word2)] = '\0';
    strcpy(word2, aux);

    /* Compare the words */
    if (strcmp(word1, word2) > 0) {
        return 1;
    }
    return 0;
}

/* Magical Keyboard functions end */

/* Trie functions */

trie_t *trie_create(int alphabet_size, char *alphabet) {
    trie_t *trie = malloc(sizeof(trie_t));
    if (trie == NULL) {
        printf("Malloc failed at trie_create\n");
        exit(1);
    }
    trie->size = 0;
    trie->root = NULL;
    trie->alphabet_size = alphabet_size;
    trie->alphabet = alphabet;
    trie->nNodes = 1;
    return trie;
}

trie_node_t *trie_create_node(trie_t *trie) {
    trie_node_t *node = NULL;
    node = malloc(sizeof(trie_node_t));
    if (node == NULL) {
        printf("Malloc failed at trie_create_node\n");
        exit(1);
    }
    node->word_counter = 0;
    node->children = NULL;
    node->parent = NULL;
    node->children = malloc(trie->alphabet_size * sizeof(trie_node_t *));
    if (node->children == NULL) {
        printf("Malloc failed at trie_create_node\n");
        exit(1);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->n_children = 0;
    node->letter = '\0';
    return node;
}

void trie_insert(trie_t *trie, char *key) {
    int k = 0;
    if (trie->root == NULL) {
        trie->root = trie_create_node(trie);
    }
    trie_node_t *curr = trie->root;
    while (key[k]) {
        if (!curr->children[key[k] - 'a']) {
            curr->children[key[k] - 'a'] = trie_create_node(trie);
            curr->children[key[k] - 'a']->parent = curr;
            trie->nNodes++;
            curr->n_children++;
        }
        curr = curr->children[key[k] - 'a'];
        memcpy(&curr->letter, &key[k], sizeof(char));
        k++;
    }
    curr->word_counter++;
}

void trie_remove(trie_t *trie, char *key) {
    int k = 0;
    trie_node_t *curr = trie->root;
    if (!curr) {
        return;
    }
    /* Go to the end of the key and change the word_counter to 0 */
    while (key[k]) {
        if (!curr->children[key[k] - 'a']) {
            return;
        }
        curr = curr->children[key[k] - 'a'];
        k++;
    }
    curr->word_counter = 0;
}

void free_node(trie_node_t *curr) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (curr->children[i]) {
            free_node(curr->children[i]);
            free(curr->children[i]);
        }
    }
    free(curr->children);
}

void trie_free(trie_t **pTrie) {
    trie_t *trie = *pTrie;
    trie_node_t *curr;
    curr = trie->root;
    if (curr) {
        free_node(curr);
        free(trie->root);
    }
    free(trie);
    pTrie = NULL;
}

/* Trie functions end */