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
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", userWordStart, word_length);
      return false;
    }
    else
    {
      
      if (!checkDict(userWordStart, num_words, words)) 
      {
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userWordStart);
        return false;
      }
    }
    if (strlen(userWordEnd) != word_length)
    {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", userWordEnd, word_length);
      return false;

    }
    else
    {  
      if (!checkDict(userWordEnd, num_words, words))
      {
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userWordEnd);
        return false;
      }
    }

    if (strcmp(userWordStart, userWordEnd) == 0) {
      printf("Your words are the same. Try again.\n");
      return false;
    }
  return true;
}
bool checkStart(char userWordStart[], char** words, int num_words, int word_length) {
    
    if (strlen(userWordStart) != word_length)
    {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", userWordStart, word_length);
      return false;
    }
    else
    {
      
      if (!checkDict(userWordStart, num_words, words)) 
      {
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userWordStart);
        return false;
      }
    }
  // printf("Your starting word is: %s.\n", userWordStart);
  return true;
}
bool checkEnd(char userWordEnd[], char** words, int num_words, int word_length) {
    
    if (strlen(userWordEnd) != word_length)
    {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", userWordEnd, word_length);
      return false;
    }
    else
    {
      
      if (!checkDict(userWordEnd, num_words, words)) 
      {
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userWordEnd);
        return false;
      }
    }
  // printf("Your ending word is: %s.\n", userWordEnd);
  return true;
}
// void nextMoves()
// {
  
// }
bool checkWin(char userWord[], char goalWord[])
{
  if(strcmp(userWord,goalWord) == 0)
    return true;
  return false;
}
char *newGameMenu()
{
  printf("\nEnter:\t1 to play again,\n\t2 to change the number of letters in the words and then play again, or\n\t3 to exit the program.\n");
  char *userChoice = malloc(sizeof(char) * 81);  // Allocate memory for userChoice
  scanf("%s", userChoice);
  printf("Your choice --> ");
  return userChoice;
}
bool quitMenu(char * choice, int num_words, char ** words, bool *fullRestart)
{
  if (strcmp(choice, "1") == 0) 
  {
    free(choice);
    return true;
  } 
  else if (strcmp(choice, "2") == 0)
  {
    *fullRestart = true;
    free(choice);
    return true;
  } 
  else if (strcmp(choice, "3") == 0) 
  {
    for (int i = 0; i < num_words; i++) 
    {
      free(words[i]);
    }
    free(words);
    free(choice);
    printf("\nThanks for playing!\nExiting...\n");
    return false;
  }
}
int main()
{
  int word_length,num_words;
  printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
  printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
  printf("Enjoy!\n\n");
  printf("How many letters do you want to have in the words? ");
  scanf("%d", &word_length);

char **words = read_file_words("words.txt", word_length, &num_words);
printf("Number of %d-letter words found: %d.\n\n",word_length,num_words);

int random;
bool fullRestart = false;
while(true) {  
  
  if(fullRestart) {
     for (int i = 0; i < num_words; i++) {    // free the memory of the previous words array
        free(words[i]);
    }
    free(words);
    printf("How many letters do you want to have in the words? ");
    scanf("%d", &word_length);
    

   

    words = read_file_words("words.txt", word_length, &num_words);
    printf("Number of %d-letter words found: %d.\n\n",word_length,num_words);
    fullRestart = false;
  }

  char userWordStart[81];
  char userWordEnd[81];
  bool goodToGo = false;
  

  while (!goodToGo) {
      //starting word
      printf("Enter starting and ending words, or 'r' for either for a random word: ");
  
      scanf("%s %s", userWordStart, userWordEnd);
 

      if (strcmp(userWordStart, "r") == 0 && strcmp(userWordEnd, "r") == 0) {

      goodToGo = true;
          random = rand() % num_words;
          strcpy(userWordStart, words[random]);
          random = rand() % num_words;
          strcpy(userWordEnd, words[random]);
      } 
      else if (strcmp(userWordStart, "r")  == 0) 
      {
        random = rand() % num_words;
        strcpy(userWordStart, words[random]);
        goodToGo = checkEnd(userWordEnd, words, num_words, word_length);
        
      } 
      else if(strcmp(userWordEnd, "r")  == 0)
      {
        random = rand() % num_words;
        strcpy(userWordEnd, words[random]);
        goodToGo = checkStart(userWordStart, words, num_words, word_length);
      }
      else 
      {
      goodToGo = checkUserWords(userWordStart, userWordEnd, words, num_words, word_length) ;
      }
        if(goodToGo)
        {
          printf("Your starting word is: %s.\n", userWordStart);
          printf("Your ending word is: %s.\n", userWordEnd);
        }
  }
  
    printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
    printf("You may also type in 'q' to quit guessing.\n");
    char userMove[81];
    char currWord[81];
    strcpy(currWord,userWordStart);
    int moves = 1;
   while (true)
  {
    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moves,currWord,userWordEnd);
    scanf("%s", userMove);
    if (strcmp(userMove, "q") == 0)
    {
      char *choice = newGameMenu();  // Store the user's choice in a variable
      // if (strcmp(choice, "1") == 0)
      // {
      //   free(choice);
      //   break;
        
      // }
      // else if (strcmp(choice, "2") == 0)
      // {
      //   //full restart
      //   fullRestart = true;
      //   free(choice);
      //   break;
      // }
      // else if (strcmp(choice, "3") == 0)
      // {
      //   for(int i = 0; i < num_words; i++)
      //   {
      //     free(words[i]);
      //   }
      //   free(words);
      //   free(choice);  // Free the memory allocated for choice
      //   printf("\nThanks for playing!\nExiting...\n");
      //   return 0;
      // }
      if(quitMenu(choice, num_words, words, &fullRestart))
      {
        break;
      }
      else
      {
        return 0;
      }
    }
    if(strlen(userMove) != word_length)
    {
  
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", userMove, word_length);
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
        strcpy(currWord,userMove);
        
        if(checkWin(currWord,userWordEnd))
        { 
          
          printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", userWordStart, currWord, moves);
          char *choice2 = newGameMenu();  // Store the user's choice in a variable
          // if (strcmp(choice2, "1") == 0)
          // {
          //   free(choice2);
          //   break;
          // }
          // else if (strcmp(choice2, "2") == 0)
          // {
          //   fullRestart = true;
          //   free(choice2);
          //   break;
          // }
          // else if (strcmp(choice2, "3") == 0)
          // {
          //   for(int i = 0; i < num_words; i++)
          //   {    
          //     free(words[i]);
          //   }
          //   free(words);
          //   free(choice2);  // Free the memory allocated for choice
          //   printf("\nThanks for playing!\nExiting...\n");
          //   return 0;
          // }
          if(quitMenu(choice2, num_words, words, &fullRestart) == 1 || quitMenu(choice2, num_words, words, &fullRestart) == 3)
            break;
          return quitMenu(choice2, num_words, words, &fullRestart);
        }
          moves++;
      }
      else
      {
        printf("Your word, '%s', is not exactly 1 character different. Try again.\n", userMove);
      }
    }
    else
    {
      printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userMove);
    }
  }
}//end of game loop
  
  return 0;
}