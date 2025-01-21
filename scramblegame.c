#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to scramble a word
void scrambleWord(char *original, char *scrambled) {
    int len = strlen(original);
    int used[len];
    for (int i = 0; i < len; i++) {
        used[i] = 0;
    }

    int index = 0;
    while (index < len) {
        int randomIndex = rand() % len;
        if (!used[randomIndex]) {
            scrambled[index++] = original[randomIndex];
            used[randomIndex] = 1;
        }
    }
    scrambled[len] = '\0'; // Null-terminate the scrambled word
}

// Function to load words from a file into an array
int loadWords(const char *filename, char words[][50], int maxWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    int count = 0;
    while (count < maxWords && fscanf(file, "%49s", words[count]) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

int main() {

    // Rules of Game 
    printf("Welcome to the Word Scramble Game!\n");
    printf("Rules:\n");
    printf("1. A scrambled word will be shown.\n");
    printf("2. Your task is to guess the original word.\n");
    printf("3. You can play as many rounds as you like.\n");
    printf("4. Your streak increases with each correct guess but resets if you guess wrong.\n");
    printf("5. No uppercase letters or special characters must be used.\n");
    printf("6. No spaces are allowed.\n");
    printf("7. No integers are allowed in string\n");
    printf("8. No viewing the words.txt file\n");
    printf("\nPress Enter to start the game...");
    getchar();
    char words[1000][50]; // Array to store up to 1000 words
    int totalWords;

    // Load words from the file
    totalWords = loadWords("words.txt", words, 1000);
    if (totalWords == 0) {
        printf("No words loaded. Exiting.\n");
        return 1;
    }

    // Seed the random number generator
    srand(time(0));

    int correctStreak = 0; // Track the number of correct guesses
    char playAgain;

    do {
        // Select a random word from the array
        char *originalWord = words[rand() % totalWords];
        char scrambledWord[50];

        // Scramble the selected word
        scrambleWord(originalWord, scrambledWord);

        // Print the scrambled word
        printf("\nScrambled Word: %s\n", scrambledWord);

        // Ask the user to guess
        char userGuess[50];
        printf("Guess the original word: ");
        scanf("%s", userGuess);

        // Check if the guess is correct
        if (strcmp(userGuess, originalWord) == 0) {
            printf("Correct! The original word was '%s'.\n", originalWord);
            correctStreak++;
        } else {
            printf("Incorrect. The original word was '%s'.\n", originalWord);
            correctStreak = 0; // Reset streak on incorrect guess
        }

        // Print the current streak
        printf("Current Streak: %d\n", correctStreak);

        // Ask if the user wants to play again
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');
    
    printf("Thanks for playing! Final Streak: %d\n", correctStreak);
    return 0;
}

  