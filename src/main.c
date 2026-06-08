#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

// Helper function to strip punctuation and lowercase a word
void clean_word(char* dest, const char* src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (isalpha((unsigned char)src[i])) {
            dest[j++] = tolower((unsigned char)src[i]);
        }
    }
    dest[j] = '\0';
}

int main() {
    // 1. Initialize Hash Table
    ht_hash_table* dictionary = ht_new();

    // 2. Load dictionary file
    printf("Loading dictionary file... Please wait.\n");
    FILE* file = fopen("data/stuff.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open stuff.txt file.\n");
        ht_del_hash_table(dictionary);
        return 1;
    }

    char word_buffer[100];
    while (fscanf(file, "%99s", word_buffer) == 1) {
        char cleaned[100];
        clean_word(cleaned, word_buffer);
        if (strlen(cleaned) > 0) {
            // Use the word as both key and value for a dictionary look-up
            ht_insert(dictionary, cleaned, cleaned); 
        }
    }
    fclose(file);
    printf("Dictionary loaded successfully!\n\n");

    //Take user input and spell check it
    char sentence[500];
    printf("Enter a sentence to spellcheck:\n> ");
    if (fgets(sentence, sizeof(sentence), stdin) != NULL) {
        
        printf("\n--- Spellcheck Results ---\n");
        
        // Tokenize the sentence by spaces and newlines
        char* token = strtok(sentence, " \n");
        while (token != NULL) {
            char cleaned[100];
            clean_word(cleaned, token);

            if (strlen(cleaned) > 0) {
                // Look up the word in the hash table
                char* found = ht_search(dictionary, cleaned);
                
                if (found != NULL) {
                    printf("[CORRECT]  %s\n", token);
                } else {
                    printf("[MISSPELT] %s <-- Check spelling!\n", token);
                }
            }
            token = strtok(NULL, " \n");
        }
    }

    //Free up memory cleanly
    ht_del_hash_table(dictionary);
    return 0;
}