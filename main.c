#include "gamelib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>



#define PASSWORD "italia"


int main(void) {
  // play_music();
    char input_password[100];
    printf("chi ha vinto la coppa del mondo nel 2006??\n");
    sleep(1);
    printf("Inserisci la password per sbloccare il gioco: ");
    scanf("%s", input_password);

    if (strcmp(input_password, PASSWORD) == 0) {
        printf(" Bravissimo. Password corretta! Gioco sbloccato.\n");
        
        // Qui inizia il gioco
        unsigned short numero;
        int c = 0;
        int i;
        printf("\033[1;33mLa storia. Un team di investigatori del paranormale viene contrattualizzato per raccogliere prove sulle presenze che si aggirano in luoghi infestati\n");
        printf(" Riusciranno a capire di che fantasma si tratta prima di impazzire? sei sicuro di voler continuare??\n");
        sleep(2);
        
        printf("\033[1;34mLoading...\n");

        for (i = 0; i <= 10; i++) {
            printf("\033[1;36m[");
            for (int j = 0; j < i; j++) {
                printf("=");
            }
            for (int j = i; j < 10; j++) {
                printf(" ");
            }
            printf("]\n");
            sleep(1); // pausa di 1 secondo
        }
        printf("\033[1;32m||preme 'invio' per continuare||\n");
        printf("\033[0m");

        while (getchar() != '\n');

        do {
            printf("\n");
            printf("> \033[1;93m1\033[1m: Imposta Gioco.\n");
            printf("> \033[1;96m2\033[2m: Gioca.\n");
            printf("> \033[1;91m3\033[3m: Termina gioco.\n\n");

            printf("\033[92mScelta:\033[0m ");
            scanf("%hu", &numero);
            while ((c = getchar()) != '\n' && c != EOF); //pulizia dei buffer

            switch (numero) {
            case 1:
                imposta_gioco();
                break;
            case 2:
                gioca();
                break;
            case 3:
                termina_gioco();
                break;
            default:
                printf("\033[31mAttenzione!\033[0m Opzione non valida, per favore inserisci \033[31mun numero da 1 a 3\033[0m.\n");
            }
        } while (numero != 3);

    } else {
        printf("Password errata. Gioco bloccato.\n");
    }

    return 0;
}

