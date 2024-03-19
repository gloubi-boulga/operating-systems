// Joe Pavlisko

// Implémentez un programme qui accumule les frappes au clavier à l’aide de la
// fonction getchar() dans un buffer. Toutes les 5 secondes, le programme affiche
// les caractères accumulés en remplaçant les minuscules par des majuscules et
// vide le buffer. Utilisez un signal SIGALRM comme déclencheur. Si le buffer est
// vide lors de la réception du signal SIGALRM, le programme se termine.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int INTERVALLE_DALARME = 5;

int buffer[100];
int caracteres_accumules = 0;

void affiche_et_efface_buffer()
{
    for (int i = 0; i < caracteres_accumules; i++)
    {
        int character = buffer[i];
        // remplace les minuscules par des majuscules
        if (character < 123 && character >= 97)
        {
            character = character - 32;
        }
        printf("%c, ", (char)character);
    }
    caracteres_accumules = 0;
}

void alarm_handler(int signalint)
{
    if (signalint == SIGALRM)
    {
        if (!caracteres_accumules)
        {
            exit(EXIT_SUCCESS);
        }
        affiche_et_efface_buffer();
        alarm(INTERVALLE_DALARME);
    }
}

int main()
{
    signal(SIGALRM, alarm_handler);
    alarm(INTERVALLE_DALARME);

    printf("Type your characters:\n");
    while (1)
    {
        int c = getchar();
        buffer[caracteres_accumules] = c;
        caracteres_accumules++;
    }
}
