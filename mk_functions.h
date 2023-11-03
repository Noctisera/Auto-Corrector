#define NMAX 200
#define ALPHABET_SIZE 26
#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

typedef struct trie_node_t trie_node_t;
struct trie_node_t {
    /* The character that this node represents */
    /* Not going to make it generic with void* data because I'm lazy */
    char letter;

    /* 1 if current node marks the end of a word, 0 otherwise */
    int word_counter;

    trie_node_t **children;
    int n_children;
    trie_node_t *parent;
};

typedef struct trie_t trie_t;
struct trie_t {
    trie_node_t *root;

    /* Number of words */
    int size;

    /* Trie-Specific, alphabet properties */
    int alphabet_size;
    char *alphabet;

    /* Optional - number of nodes, useful to test correctness */
    int nNodes;
};

/* Magic Keyboard functions */

/**
 * insert_word() - Insert a word in the trie.
 * @arg1: The trie to insert the word in.
 * @arg2: The word to be inserted.
 *
 * The function inserts the word in the trie. Crazy, right?
 */
void insert_word(trie_t *trie, char *word);
/**
 * remove_word() - Remove a word from the trie.
 * @arg1: The trie to remove the word from.
 * @arg2: The word to be removed.
 *
 * The function sets the word_counter of the last letter of the word to 0.
 */
void remove_word(trie_t *trie, char *word);
/**
 * autocorrect() - Autocorrect a word.
 * @arg1: The trie to autocorrect the word in.
 * @arg2: The word to be autocorrected.
 * @arg3: The maximum number of different letters.
 *
 * The function prints all the words in the trie that have at most k different
 * letters from the given word.
 */
void autocorrect(trie_t *trie, char *word, int k);
/**
 * autocorrect_rec() - Autocorrect a word recursively.
 * @arg1: The trie to autocorrect the word in.
 * @arg2: The node to start the search from.
 * @arg3: The word to be autocorrected.
 * @arg4: The maximum number of different letters.
 * @arg5: The number of different letters between the current word and the
 *        word to be autocorrected.
 * @arg6: The word that is being built.
 * @arg7: The condition to check if there weren't any words printed.
 *
 * The function prints all the words in the trie that have at most k different
 * letters from the given word.
 */
void autocorrect_rec(trie_t *trie, trie_node_t *node, char *word, int k,
                     int diff, char curr_word[], int *condition);
/**
 * autocomplete() - Autocomplete a word.
 * @arg1: The trie to autocomplete the word in.
 * @arg2: The prefix of the word to be autocompleted.
 * @arg3: The criteria number.
 *
 * Depending on the criteria number, the function calls the following functions
 * to print their characteristic words: 1 - lowest_lexicographic() 2 -
 * shortest_word() 3 - most_frequent_word() 0 - all of the above
 */
void autocomplete(trie_t *trie, char *prefix, int criteria);
/**
 * lowest_lexicographic() - Returns the lowest lexicographic word.
 * @arg1: The trie to print the word from.
 * @arg2: The node to start the search from.
 * @arg3: The prefix of the word to be autocompleted.
 * @arg4: The word that is being built.
 *
 * The function returns the lowest lexicographic word that starts with the given
 * prefix.
 */
char *lowest_lexicographic(trie_t *trie, trie_node_t *node, char *prefix,
                           char curr_word[]);
/**
 * shortest_word() - Returns the shortest word.
 * @arg1: The trie to print the word from.
 * @arg2: The node to start the search from.
 * @arg3: The prefix of the word to be autocompleted.
 * @arg4: The word that is being built.
 *
 * The function returns the shortest word that starts with the given prefix.
 */
char *shortest_word(trie_t *trie, trie_node_t *node, char *prefix,
                    char curr_word[]);
/**
 * most_frequent_word() - Returns the node of the last letter of the most
 * frequent word.
 * @arg1: The trie to print the word from.
 * @arg2: The node to start the search from.
 * @arg3: The prefix of the word to be autocompleted.
 *
 * The function returns the node of the last letter of the most frequent word
 * that starts with the given prefix.
 */
trie_node_t *most_frequent_word(trie_t *trie, trie_node_t *node, char *prefix);
/**
 * compare_words() - Compares two words.
 * @arg1: The node of the last letter of the first word.
 * @arg2: The node of the last letter of the second word.
 *
 * The function build the two words then compares them lexicographically.
 */
int compare_words(trie_node_t *node1, trie_node_t *node2);

/* Magical Keyboard functions end */

/* Trie functions */

trie_t *trie_create(int alphabet_size, char *alphabet);
trie_node_t *trie_create_node(trie_t *trie);
void trie_insert(trie_t *trie, char *key);
void trie_remove(trie_t *trie, char *key);
void free_node(trie_node_t *curr);
void trie_free(trie_t **pTrie);

/* Trie functions end */