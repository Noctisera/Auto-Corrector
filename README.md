# README Auto Corrector

## Description

This is a program that simulates a basic autocorrector with a wide amount of different functions. Its role is to save the vocabulary of a person (or in this case text from text files) and autocorrect specific words based on the previously analysed vocabulary.

## What does it do?
It has multiple commands that the user can use to autocorrect words using different methods or to modify the vocabulary from which it takes its answers.

1.	INSERT {word} - Adds a word to the vocabulary. If the word is already existent, increment its usage counter by 1.
2.	LOAD {file_name} - Reads all the words from the given text file and inserts them into the vocabulary.
3.	REMOVE {word} - Deletes a word from the vocabulary, reseting its  usage counter to 0.
4.	AUTOCORRECT {word} {diff} - Prints from the vocabulary all the words similar to the given one that have at most {diff} different letters.
5.	AUTOCOMPLETE {prefix} {criteria} - Prints the words from the vocabulary that start with the given prefix, depending on the given criteria:
	- Criteria 1: Prints the lowest lexicographical word that starts with prefix.
	- Criteria 2: Prints the shortest word that starts with the prefix.
	- Criteria 3: Prints the most frequent word that starts with the prefix. In case of equality, print the lowest lexicographical word.
	- Criteria 0: All of the above.
6.	EXIT - Frees the used memory and exits the code.

## Code structure and implementation

To store words in the vocabulary I'll be using trie data structure. Each level on the tree will represent a letter that points to other letters that it forms words with. To know where a word ends, each letter has a 'word_counter' variable that also keeps count of the usage of the word.

To explain how the insert works it would mean to explain the concept of trie in general, so I'm not going to do it here. Go search it up.

Removing a word simply resets its 'word_counter' to 0. For more time and memory efficiency the code could be modified to also delete the unused letters from the trie.

## Other notes

The only usable characters are small letters. Using anything else will most likely result in the creation of a black hole in your computer that will eat your whole house, the planet and then the solar system.
