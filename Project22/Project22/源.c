#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
// 单词结构
struct Word {
    char term[50];
    char definition[200];
};

// 常量定义
#define MAX_WORDS 100

// 函数声明
void displayMenu();
void loadWords(struct Word words[], int *numWords);
void displayWords(struct Word words[], int numWords);
void addWord(struct Word words[], int *numWords);
void saveWords(struct Word words[], int numWords);
void displayWordsFromFile();

int main() {
    struct Word words[MAX_WORDS];
    int numWords = 0;
    int choice;

    // 加载单词
    loadWords(words, &numWords);

    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayWords(words, numWords);
                break;
            case 2:
                addWord(words, &numWords);
                break;
            case 3:
                saveWords(words, numWords);
                break;
            case 4:
                displayWordsFromFile();
                break;
            case 0:
                printf("Exiting the Word Book. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\n=== Word Book Menu ===\n");
    printf("1. Display Words\n");
    printf("2. Add Word\n");
    printf("3. Save Words to File\n");
    printf("4. Display Words from File\n");
    printf("0. Exit\n");
}

void loadWords(struct Word words[], int *numWords) {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        printf("No existing word file found.\n");
        return;
    }

    while (fscanf(file, "%s %[^\n]s", words[*numWords].term, words[*numWords].definition) == 2) {
        (*numWords)++;
        if (*numWords >= MAX_WORDS) {
            printf("Maximum word limit reached.\n");
            break;
        }
    }

    fclose(file);
    printf("Words loaded from file.\n");
}

void displayWords(struct Word words[], int numWords) {
    printf("\n=== Words in the Book ===\n");
    for (int i = 0; i < numWords; i++) {
        printf("%d. %s: %s\n", i + 1, words[i].term, words[i].definition);
    }
}

void addWord(struct Word words[], int *numWords) {
    if (*numWords >= MAX_WORDS) {
        printf("Word limit reached.\n");
        return;
    }

    printf("Enter the term: ");
    scanf("%s", words[*numWords].term);
    printf("Enter the definition: ");
    scanf(" %[^\n]s", words[*numWords].definition);

    (*numWords)++;
    printf("Word added successfully.\n");
}

void saveWords(struct Word words[], int numWords) {
    FILE *file = fopen("words.txt", "w");
    if (file == NULL) {
        printf("Unable to create or open the file.\n");
        return;
    }

    for (int i = 0; i < numWords; i++) {
        fprintf(file, "%s %s\n", words[i].term, words[i].definition);
    }

    fclose(file);
    printf("Words saved to file successfully.\n");
}

void displayWordsFromFile() {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        printf("No existing word file found.\n");
        return;
    }

    printf("\n=== Words in the File ===\n");
    char line[256];
    int count = 1;

    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", count++, line);
    }

    fclose(file);
}
