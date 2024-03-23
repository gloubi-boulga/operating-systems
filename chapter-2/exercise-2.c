#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* expand_tabs(char *string);

int main() {

    char* inputString = "Bonj\tour";
    char* expandedString = expand_tabs(inputString);

    printf("%s\n", inputString);
    printf("%s\n", expandedString);

    free(expandedString);
    return EXIT_SUCCESS;
}

char* expand_tabs(char *string) {

    int inputSize = strlen(string);
    int tab = 0;

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '\t') {
            tab += 4;
        }
    }

    int outputSize = inputSize + tab;
    char* finalString = malloc(outputSize * sizeof(char));

    int j, k;

    for (j = 0, k = 0; j < inputSize; j++) {
        if (string[j] == '\t') {
            for (int l = 0; l < 4; l++) {
                finalString[k++] = ' ';
            }
        } else {
            finalString[k++] = string[j];
        }
    }

    return finalString;
}