#include <stdio.h>
#include <stdlib.h>
typedef struct Node
    *NodePtr; // Make:  NodePtr to be a synonym for: struct Node *
struct Node {
  char data;      // The data stored at the node
  NodePtr pNext; // Pointer to the next node
};
char **read_file_words(const char *filename, int word_length, int *num_words) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    
    // Allocate memory for words array
    char **words = malloc(1 * sizeof(char *));
    if (words == NULL) {
        printf("Error allocating memory for words array\n");
        exit(1);
    }
    
    // Read words from file
    char buffer[100];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove trailing newline
        if (strlen(buffer) == word_length) {
            words[i] = strdup(buffer); // Copy word to heap
            if (words[i] == NULL) {
                printf("Error allocating memory for word %s\n", buffer);
                exit(1);
            }
            i++;
            words = realloc(words, (i + 1) * sizeof(char *)); // Expand words array
            if (words == NULL) {
                printf("Error reallocating memory for words array\n");
                exit(1);
            }
        }
    }
    fclose(file);
    
    *num_words = i;
    return words;
}

int main() {
	/*
		Here are some print statements that you may use in your program.
		You will need to change at least some of them.
	*/
	printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
	// printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	// printf("Enjoy!\n\n");

	// 
	// printf("Number of 4-letter words found: ???.\n\n");

	// printf("Enter starting and ending words, or 'r' for either for a random word: ");
	// printf("Your word, 'zzzzz', is not a 4-letter word. Try again.\n");
	// printf("Your word, 'sonf', is not a valid dictionary word. Try again.\n");
	// printf("Your starting word is: song.\n");
	// printf("Your ending word is: sink.\n");

	// printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
 //    printf("You may also type in 'q' to quit guessing.\n");

	// printf("\n1. Previous word is 'song'. Goal word is 'sink'. Next word: ");

	// printf("Your word, 'sinks', is not a 4-letter word. Try again.\n");
	// printf("Your word, 'sint', is not a valid dictionary word. Try again.\n");
	// printf("Your word, 'guards', is not exactly 1 character different. Try again.\n");

	// printf("Congratulations! You changed 'song' into 'sink' in 3 moves.\n");

	// printf("\nEnter: \t1 to play again,\n");
 //    printf("\t2 to change the number of letters in the words and then play again, or\n");
 //    printf("\t3 to exit the program.\n");
 //    printf("Your choice --> ");

	/* 
		This code demonstrates how to read in from a file.
	*/


int word_length,num_words;

printf("Welcome to the word ladder game!\n");
printf("Enter the number of letters you'd like the words to have: ");
scanf("%d", &word_length);
  
    char **words = read_file_words("words.txt", word_length, &num_words);
    printf("Found %d words of length %d in the file\n", num_words, word_length);
    
    // Print words array
    for (int i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
    
    // Free memory allocated for words
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);
    
    return 0;
}