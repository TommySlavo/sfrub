#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const *b) {
    for (;; a++, b++) {
        if (*a == ' ' && *b == ' ') {
            return 0;
        }
        else if (*a == ' ' || ((*a^42) < (*b^42))) {
            return -1;
        }
        else if (*b == ' ' || ((*a^42) > (*b^42))) { 
            return 1; // a is larger
        }
    }
}

int cmp(const void* in1, const void* in2) {
    // cast pointers to pointers
    const char* a = *(const char**)in1;
    const char*b = *(const char**)in2;
    return frobcmp(a, b);
}

void readErr() {
    if (ferror(stdin)) {
        fprintf(stderr, "Error while reading file!");
        exit(1);
    }
}

int main(void) {
    char* word;
    char** words; // array that holds pointers to words
    word = (char*)malloc(sizeof(char));
    words = (char**)malloc(sizeof(char*));

    char curr = getchar();
    readErr();
    char next = getchar();
    readErr();
    int letterIterator = 0;
    int wordIterator = 0;
    while (curr != EOF && !ferror(stdin)) {
        word[letterIterator] = curr;
        char* temp = realloc(word, (letterIterator + 2)*sizeof(char));
        if (temp != NULL) {
            word = temp;
        }
        else {
            free(word);
            fprintf(stderr, "Error Allocation Memory");
            exit(1);
        }

        if (curr == ' ') {
            words[wordIterator] = word;
            char** anotherOne = realloc(words, (wordIterator + 2)*sizeof(char*));

            if (anotherOne != NULL) {
                words = anotherOne;
                wordIterator++;
                word = NULL;
                word = (char*)malloc(sizeof(char));
                letterIterator = -1;
            }
            else {
                free(words);
                fprintf(stderr, "Error Allocation Memory");
                exit(1);
            }
        }
        if (next == EOF && curr == ' ') {
            break;
        }
        else if (curr == ' ' && next == ' ') {
            while(curr == ' ') {
                curr = getchar();
                readErr();
            }
            next = getchar();
            readErr();
            letterIterator++;
            continue;
        }
        else if (next == EOF) {
            curr = ' ';
            letterIterator++;
            continue;
        }
        curr = next;
        next = getchar();
        readErr();
        letterIterator++;
    }

    qsort(words, wordIterator, sizeof(char*), cmp);

    for (size_t i = 0; i < wordIterator; i++) {
        for (size_t j = 0; ; j++) {
            if (putchar(words[i][j]) == EOF) {
                fprintf(stderr, "Error while writing character");
                exit(1);
            }
            if (words[i][j] == ' ') {
                break;
            }
        }
    }

    // deallocate space taken for words

    for (size_t i = 0; i < wordIterator; i++) {
        free(words[i]);
    }
    free(words);


    exit(0);
    
}