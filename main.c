#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool checkDict(char userInput[], int numWords, char** words)
{
  int i = 0;
  for(i; i < numWords; i++)
  {
    if(strcmp(words[i], userInput) == 0)
    {
      return true;
    }
  }
  return false;
}
bool checkUserWords(char userWordStart[], char userWordEnd[], char** words, int num_words, int word_length) {
    
    if (strlen(userWordStart) != word_length)
    {
      printf("Your word, %s, is not a %d-letter word. Try again.\n", userWordStart, word_length);
      return false;
    }
    else
    {
      
      if (!checkDict(userWordStart, num_words, words)) 
      {
        printf("Your word, %s, is not a valid dictionary word. Try again.\n", userWordStart);
        return false;
      }
    }
    if (strlen(userWordEnd) != word_length)
    {
      printf("Your word, %s, is not a %d-letter word. Try again.\n", userWordEnd, word_length);
      return false;
    }
    else
    {  
      if (!checkDict(userWordEnd, num_words, words))
      {
        printf("Your word, %s, is not a valid dictionary word. Try again.\n", userWordEnd);
        return false;
      }
    }

    if (strcmp(userWordStart, userWordEnd) == 0) {
      printf("Your words are the same. Try again.\n");
      return false;
    }
  return true;
}
void nextMoves()
{
  
}
char *newGameMenu()
{
  printf("\nEnter:\t1 to play again,\n\t2 to change the number of letters in the words and then play again, or\n\t3 to exit the program.\n");
  char *userChoice = malloc(sizeof(char) * 81);  // Allocate memory for userChoice
  scanf("%s", userChoice);
  printf("Your choice --> ");
  return userChoice;
}

int main()
{
  	/*
  		Here are some print statements that you may use in your program.
  		You will need to change at least some of them.
  	*/
  
  
  	// 
  	// printf("Number of 4-letter words found: ???.\n\n");
  
  	// 
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
  printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
  printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
  printf("Enjoy!\n\n");
  
  printf("How many letters do you want to have in the words? ");
  scanf("%d", &word_length);
  
  
    
  char **words = read_file_words("words.txt", word_length, &num_words);
  printf("Number of 4-letter words found: %d.\n\n",num_words);
      char userWordStart[81];
    char userWordEnd[81];
bool goodToGo = false;

//   for(int i = 0; i < num_words; i++)
//   {
//     if(strcmp(words[i],"song") == 0)
//     {
//       printf("The word is in the dictionary.\n");
//     }
//   }
//   printf("The word is not in the dictionary.\n");
// return 0;
while (!goodToGo) {
    //starting word
    printf("Enter starting and ending words, or 'r' for either for a random word: ");

    scanf("%s %s", userWordStart, userWordEnd);
    if (strcmp(userWordStart, "r") == 0 || strcmp(userWordEnd, "r") == 0) {
        int random;
        goodToGo = true;
        if (strcmp(userWordStart, "r") == 0) {
            random = rand() % num_words;
            printf("Your starting word is: %s.\n", words[random]);
            strcpy(userWordStart, words[random]);
        }
        if (strcmp(userWordEnd, "r") == 0) {
            random = rand() % num_words;
            printf("Your ending word is: %s.\n", words[random]);
            strcpy(userWordEnd, words[random]);
        }
    } else {
        if (checkUserWords(userWordStart, userWordEnd, words, num_words, word_length)) {
            printf("Your starting word is: %s.\n", userWordStart);
            printf("Your ending word is: %s.\n", userWordEnd);
            goodToGo = true;
        }
    }
}



  printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
  printf("You may also type in 'q' to quit guessing.\n");
char userMove[81];
  char currWord[81];
  strcpy(currWord,userWordStart);
 while (true)
{
  printf("\n1. Previous word is '%s'. Goal word is '%s'. Next word: ", currWord,userWordEnd);
  scanf("%s", userMove);
  if (strcmp(userMove, "q") == 0)
  {
    char *choice = newGameMenu();  // Store the user's choice in a variable
    if (strcmp(choice, "1") == 0)
    {
      printf("testing 1\n");
    }
    else if (strcmp(choice, "2") == 0)
    {
      printf("testing 2\n");
    }
    else if (strcmp(choice, "3") == 0)
    {
      free(choice);  // Free the memory allocated for choice
      printf("\nThanks for playing!\nExiting...\n");
      return 0;
    }
    free(choice);  // Free the memory allocated for choice
  }
  if(strlen(userMove) != 4)
  {
    printf("Your word, '%s', is not a 4-letter word. Try again.\n", userMove);
    continue;
  }
    int numDiffCount = 0;
  if(checkDict(userMove,num_words,words))
  {
    for(int i = 0; i < word_length; i++)//we have to check the number of characters that are different since at least one has to be different
    {
      if(userMove[i] != currWord[i])
      {
          numDiffCount++;
      }
    }
    if(numDiffCount == 1)//if 1 letter is different 
    {
      printf("Your word, %s, is exactly 1 character different. fix later.\n", userMove);
    }
    else
    {
      printf("Your word, %s, is not exactly 1 character different. Try again.\n", userMove);
    }
  }
  else
  {
    printf("Your word, %s, is not a valid dictionary word. Try again.\n", userMove);
  }
  strcpy(currWord,userMove);
}
  
      // Print words array
      // for (int i = 0; i < num_words; i++) {
      //     printf("%s\n", words[i]);
      // }
      
      // // Free memory allocated for words
      // for (int i = 0; i < num_words; i++) {
      //     free(words[i]);
      // }
      

  // printf("%d\n", random);
  // printf("%s\n", words[0]);
  
      return 0;
}