/******************************************************************************
* S-INFO-054 --- Solution pour Travail 1                                      *
* Groupe 08                                                                   *
* Membres:                                                                    *
* - HOUIOUX Guillaume                                                         *
* - TONGRES Cyril                                                             *
* - PAVLISKO Joseph                                                           *
* - WALEM Hugo                                                                *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_BUFFER_VALUE 64
#define ALARM_INTERVAL 5

char buffer[MAX_BUFFER_VALUE];
int bufferIndex = 0;

void getCharacterInput();
void processAlarmSignal();

void handler(int signum) {
    if (signum == SIGALRM) {
        processAlarmSignal();
        alarm(ALARM_INTERVAL);
    }
}

int main(int argc, char *argv[]) {
    printf("Program started, taking at most %d characters :\n", MAX_BUFFER_VALUE);
    signal(SIGALRM , handler);
    alarm(ALARM_INTERVAL);
    getCharacterInput();
    return EXIT_SUCCESS;
}

void processAlarmSignal() {
    if (bufferIndex == 0) {
        printf("Nothing to process, terminate the program\n");
        exit(EXIT_SUCCESS);
    }

    printf ("Processing buffer : ");
    for (int i = 0; i < bufferIndex; i++) {
        printf("%c ", toupper(buffer[i]));
        buffer[i] = '\0'; // Once printed reset to default
    }
    bufferIndex = 0;
    printf("\n");
}

void getCharacterInput() {
    while (1) {
        if (bufferIndex < MAX_BUFFER_VALUE) {
            char inputChar = getchar();
            if (isalpha(inputChar)) {
                buffer[bufferIndex++] = inputChar;
            }
        } else {
            printf("Buffer capacity reached. Awaiting next signal to clear the buffer\n");
            pause();
        }
    }
}
