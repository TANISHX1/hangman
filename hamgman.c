#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_WORD_LENGTH 50
#define MAX_TRIES 6

// struct to hold a word and its hint
struct word_hint
{
    char word[MAX_WORD_LENGTH];
    char hint[MAX_WORD_LENGTH];
};
// Function to display the current state of the word
void displayword(const char word[], const bool guessed[])
{
    printf("Word : ");
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (guessed[tolower(word[i]) - 'a'])
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}
// Function to draw the hangman
void draw(int tries);

// main code
int main()
{

    // seed the random number generator with current time
    //  srand always provides a random value to rand().
    // adding words with hints.

    struct word_hint wordlist[] = {

        {"dog", "A popular pet"},
        {"chair", "A piece of furniture to sit on"},
        {"sun", "The star that provides light and warmth"},
        {"car", "A vehicle used for driving"},
        {"fish", "An animal that lives in water"},
        {"cup", "A small container for drinking"},
    };

    // selecting a random number
    srand(time(NULL));
    int index = rand() % 6;

    const char *secretword = wordlist[index].word;
    const char *hint = wordlist[index].hint;

    int length = strlen(secretword);

    char guessedword[MAX_WORD_LENGTH] = {0};
    bool guessedletter[26] = {false};

    printf("Welcome to Hangman!!!\n");
    printf("Hint: %s\n", hint);

    int tries = 0;

    while (tries < MAX_TRIES)
    {
        printf("\n");

        displayword(guessedword, guessedletter);
        draw(tries);

        char guess;
        printf("Enter a letter:\t");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (guessedletter[tolower(guess) - 'a'])
        {
            printf("You've already guessed that letter. "
                   "Try again.\n");
            continue;
        }

        guessedletter[guess - 'a'] = true;

        bool found = false;
        for (int i = 0; i < length; i++)
        {
            if (tolower(secretword[i]) == tolower(guess))
            {
                found = true;
                guessedword[i] = tolower(guess);
            }
        }
        if (found)
            printf("Good guess!\n");

        else
        {
            printf("Sorry the letter '%c' is not in the "
                   "secret Word\n",
                   guess);
            tries++;
        }
        if (strcmp(secretword, guessedword) == 0)
        {
            printf("\nCongratulations! You've guessed the "
                   "word: %s\n",
                   secretword);
            break;
        }
    }
    if (tries >= MAX_TRIES)
    {
        printf("\nSorry ,you've run out of tries.the word was: %s\n", secretword);
    }

    return 0;
}

/*void displayWord(const char word[], const bool guessed[])
{
    printf("Word : ");
     for(int i=0; word[i] != '\0'; i++)
     {
        if(guessed[word[i] - 'a'])
        printf("%c ",word[i]);

     else
     printf("_ ");
      }
      printf("\n");

}*/

void draw(int tries)
{
    const char *hangman[] = {
        "  ___________", " |           |", " |           O", " |          /|\\", " |          / \\",
        " | ",           " / \\"};
    printf("\n");
    for (int i = 0; i <= tries; i++)
    {
        printf("%s\n", hangman[i]);
    }
}
