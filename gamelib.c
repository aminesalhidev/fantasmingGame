
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdbool.h>
#include "gamelib.h"
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Definizione delle costanti per le difficoltà
#define MAX_OGGETTI_DISPONIBILI 3
#define DIFFICOLTA_PRINCIPIANTE 1
#define DIFFICOLTA_INTERMEDIO 2
#define DIFFICOLTA_INCUBO 3
#define DIFFICOLTA_MEDIA 2
#define DIFFICOLTA_ALTA 3
#define MAX_GIOCATORI 4
static int map_created;
int nplayers;
static int difficulty_level;
int indice_giocatore_corrente = 0;
struct Giocatore *giocatore[4];
unsigned short andiamo;
unsigned short numero;
unsigned short number;
struct Zona_mappa *pLast = NULL;
struct Zona_mappa *pFirst = NULL;
int turno_attuale = 0;


int askInt(const char *prompt)
{
    int n = -1;
    while (n < 0)
    {
        printf("%s", prompt);
        scanf("%d", &n);
    }
    return n;
}

void mostra_zaino(struct Giocatore *giocatore)
{
    const char *nome_oggetto_iniziale;

    switch (giocatore->zaino[0])
    {
    case EMF:
        nome_oggetto_iniziale = "EMF";
        break;
    case spirit_box:
        nome_oggetto_iniziale = "Spirit Box";
        break;
    case videocamera:
        nome_oggetto_iniziale = "Videocamera";
        break;
    case calmanti:
        nome_oggetto_iniziale = "Calmanti";
        break;
    case sale:
        nome_oggetto_iniziale = "Sale";
        break;
    default:
        return;
    }

    printf("Contenuto zaino di %s:\nOggetto iniziale: %s\n", giocatore->nome_giocatore, nome_oggetto_iniziale);

    for (int i = 1; i < 3; i++)
    {
        switch (giocatore->zaino[i])
        {
        case cento_dollari:
            printf("100$\n");
            break;
        case nessun_oggetto:
            printf("nessun_oggetto\n");
            break;
        case coltello:
            printf("coltello\n");
            break;
        case calmanti1:
            printf("calmanti1\n");
            break;
        case adrenalina:
            printf("adrenalina\n");
            break;
        }
    }
}

void imposta_gioco(struct Giocatore *giocatori)
{

    // Inizializza la mappa
    if (!map_created)
    {
        map_created = 1;
        pFirst = (struct Zona_mappa *)malloc(sizeof(struct Zona_mappa));
        pLast = pFirst;
        pLast->prossima_zona = NULL;
    }

    // Ciclo principale
    int scelta_menu;
    int c;
    do

    {
        printf("\033[1;34mMenù\n");
        printf("\033[1;33m> 1 Inserisci zona\n");
        printf("\033[1;32m> 2 Cancella zona\n");
        printf("\033[1;36m> 3 Stampa mappa\n");
        printf("\033[1;31m> 4 Chiudi mappa\n");
        scanf("%d", &scelta_menu);
        while ((c = getchar()) != '\n' && c != EOF)
            ; // pulizia dei buffer} while (scelta_menu < 1 || scelta_menu > 4);

        // Processa la scelta dell'utente
        switch (scelta_menu)
        {
        case 1:
            inserisci_zona();
            break;
        case 2:
            cancella_zona();
            break;
        case 3:
            stampa_mappa();
            break;
        case 4:
            chiudi_mappa();
            break;
        default:
            printf("\033[31mAttenzione!\033[0m Opzione non valida, per favore inserisci \033[31mun numero da 1 a 4\033[0m.\n");
        }
    } while (scelta_menu != 4);

    // Chiude la mappa
    chiudi_mappa();
}

struct Zona_mappa *genera_mappa()
{

    //questo codice andrebbe risutruttura meglio secondo me.
    // Crea la prima zona mappa
    struct Zona_mappa *prima_zona = malloc(sizeof(struct Zona_mappa));
    prima_zona->zona = cucina;
    

    // Crea la seconda zona mappa
    struct Zona_mappa *seconda_zona = malloc(sizeof(struct Zona_mappa));
    seconda_zona->zona = soggiorno;
    prima_zona->prossima_zona = seconda_zona;

    // Crea la terza zona
    struct Zona_mappa *terza_zona = malloc(sizeof(struct Zona_mappa));
    terza_zona->zona = garage;
    seconda_zona->prossima_zona = terza_zona;

    struct Zona_mappa *quarta_zona = malloc(sizeof(struct Zona_mappa));
    quarta_zona->zona = camera;
    terza_zona->prossima_zona = quarta_zona;

    // Crea la terza zona
    struct Zona_mappa *quinta_zona = malloc(sizeof(struct Zona_mappa));
    quinta_zona->zona = bagno;
    quarta_zona->prossima_zona = quinta_zona;

    struct Zona_mappa *ultima_zona = malloc(sizeof(struct Zona_mappa));
    ultima_zona->zona = seminterrato;
    quinta_zona->prossima_zona = ultima_zona;

    ultima_zona->prossima_zona = prima_zona;

    // Assegna i valori ai puntatori globali
    pFirst = prima_zona;
    pLast = ultima_zona;

    return prima_zona; // Restituisce l'indirizzo della prima zona
}

void inserisci_zona()
{
     //alloca la memoria alla nuova zona
    struct Zona_mappa *nuova_zona = malloc(sizeof(struct Zona_mappa));
    if (nuova_zona == NULL)
    {
        fprintf(stderr, "ERRORE: impossibile allocare memoria per la nuova zona\n");
        return;
    }
    // assegna un oggetto casuale ad ogni giocatore
    nuova_zona->zona = rand() % 6;
    int r = rand() % 100;
    if (r < 40)
    {
        nuova_zona->oggetto_zona = nessun_oggetto;
    }
    else if (r < 55)
    {
        nuova_zona->oggetto_zona = calmanti1;
    }
    else if (r < 70)
    {
        nuova_zona->oggetto_zona = coltello;
    }
    else if (r < 85)
    {
        nuova_zona->oggetto_zona = cento_dollari;
    }
    else
    {
        nuova_zona->oggetto_zona = adrenalina;
    }
    // Insert the new zone at the end of the list
    if (pFirst == NULL)
    { // Se l'elenco è vuoto, imposta First e Last come nuova zona
        pFirst = nuova_zona;
        pLast = nuova_zona;
        pLast->prossima_zona = NULL;
    }
    else
    {
        pLast->prossima_zona = nuova_zona;
        pLast = nuova_zona;
        pLast->prossima_zona = NULL;
    }
    printf("Nuova zona creata con successo. Premi 3 per visualizzarla.\n");
}

void cancella_zona()
{
// Caso speciale: la lista è vuota
    if (pFirst == NULL)
    {
        return;
    }

    struct Zona_mappa **pp = &pFirst;
    while ((*pp)->prossima_zona != NULL)
    {
        pp = &(*pp)->prossima_zona;
    }

    free(*pp);
    *pp = NULL;
    pLast = pp == &pFirst ? NULL : pLast;

    printf("Zona cancellata con successo\n");
}

void stampa_mappa()
{
    // Caso particolare: la lista è vuota
    if (pFirst == NULL)
    {
        printf("La mappa è vuota\n");
        return;
    }

    printf("Stampa della mappa:\n");
    struct Zona_mappa *p = pFirst;
    while (p != NULL)
    {
        printf(" - Zona di tipo %d, con oggetto %d\n", p->zona, p->oggetto_zona);
        p = p->prossima_zona;
    }
}

void chiudi_mappa()
{
    if (map_created == 0)
    {
      //mostra che la mappa e stata creata.
        map_created = 1;
    }
    else
    {
        printf("La mappa è già stata creata in precedenza.\n");
    }
}

void gioca(struct Giocatore *giocatori)
{

 printf("**************************************************************\n");
    printf("            Benvenuto al gioco fantasming!            \n");
    printf("**************************************************************\n\n");

    // Verifica se la mappa è stata creata
    if (!map_created)
    {
        printf("Attenzione: la mappa non è stata ancora creata. Assicurarsi che la creazione della mappa sia terminata prima di iniziare a giocare.\n");
        return;
    }

    // Inizio del gioco
    printf("Il gioco è iniziato. Buon divertimento!\n");

    srand(time(NULL));
    char input[30];
    // Lettura del numero di giocatori
    // Inizializza nplayers con il numero corretto di giocatori
    nplayers = 4;
     do
    {
        printf("Inserisci il numero dei giocatori (da 1 a 4): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            // Gestione errore lettura input
            printf("Errore lettura input.\n");
            continue;
            ;
        }
        if (sscanf(input, "%d", &nplayers) != 1)
        {
            // L'input inserito non è un intero
            printf("Inserisci un valore numerico valido.\n");
            nplayers = 0;
        }
    } while (nplayers < 1 || nplayers > 4);

    // inizializzazione dei giocatore
    memset(giocatori, 0, sizeof(struct Giocatore) * 4);

    // Inizializzazione dei giocatori
    for (int i = 0; i < nplayers; i++)
    {
        printf("Inserisci il nome del giocatore %d: ", (i + 1));
        scanf("%s", giocatori[i].nome_giocatore);

        // Inizializza le statistiche del giocatore
        giocatori[i].sanita_mentale = 100;
        giocatori[i].zaino[0] = rand() % 5;
        for (int j = 1; j < 3; j++)
            giocatori[i].zaino[j] = nessun_oggetto;

        // Mostra l'inventario del giocatore
        mostra_zaino(&giocatori[i]);
    }

    do
    {
        printf("Seleziona il livello di difficoltà:\n");
        printf("1. Principiante\n");
        printf("2. Intermedio\n");
        printf("3. Incubo\n");
        scanf("%d", &difficulty_level);
        
    } while (difficulty_level < 1 || difficulty_level > 3);

    if (nplayers < 2)
    {
        printf("Attenzione! Non ci sono abbastanza giocatori per iniziare il gioco.\n");
        return;
    }

    int indice_giocatore_corrente = 0;

    // Cicla attraverso tutti i giocatori
    while (1)
    {
        struct Giocatore *giocatore = &giocatori[indice_giocatore_corrente];

        // Posiziona il giocatore nella prima zona della mappa
        giocatore->posizione = pLast;

        short int andiamo;
        int c;
        do
        {
            // Mostra le opzioni al giocatore
            printf("Turno del giocatore %s.\n", giocatori[indice_giocatore_corrente].nome_giocatore);
            printf("1: Torna al caravan\n");
            printf("2: Stampa il tuo giocatore\n");
            printf("3: Stampa la tua zona\n");
            printf("4: Avanza\n");
            printf("5: Raccogli questa prova\n");
            printf("6: Raccogli questo oggetto\n");
            printf("7: Usa questo oggetto\n");
            printf("8: Passa il turno\n");
            printf("9: termina il turno\n");
            printf("10: svuota lo zaino\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ; // pulizia dei buffer} while (scelta_menu < 1 || scelta_menu > 4);

            scanf("%hd", &andiamo);

            // Esegue la funzione scelta dal giocatore
            switch (andiamo)
            {
            case 1:
                torna_caravan(giocatore);
                break;
            case 2:
                stampa_giocatore(giocatore);
                break;
            case 3:
                stampa_zona(giocatore);
                break;
            case 4:
                avanza(giocatori, nplayers, &indice_giocatore_corrente);
                break;
            case 5:
                raccogli_prova(giocatore);
                giocatore->turno_avanzato = 1;
                passa_turno(giocatori, nplayers, &indice_giocatore_corrente, 0);
                break;
            case 6:
                raccogli_oggetto(giocatore);
                break;
            case 7:
                usa_oggetto(giocatore, nplayers, indice_giocatore_corrente);
                break;
            case 8:
              passa_turno(giocatori, nplayers, &indice_giocatore_corrente, 1);
          
                break;
            case 9:
                termina_turno(giocatore, nplayers);
                break;
            case 10:
                svuota_zaino(giocatore);
            default:
                printf("Inserisci un numero compreso tra 1 e 10.\n");
                break;
            }
        } while (andiamo != 10);
    }
    // Chiamata alla funzione probabilita_decremento_salute_mentale
    probabilita_decremento_salute_mentale(giocatore);
}

void torna_caravan(struct Giocatore *giocatore, struct Giocatore *caravan, struct Zona_mappa *prima_zona, int nplayers, int *indice_giocatore_corrente, int prove_necessarie)
{
   double probabilita_fantasma = 0.3; // probabilità di 0,3 (30%) che il fantasma appaia


if (difficolta_principiante(difficulty_level)) {
    probabilita_fantasma += 0.05;
} else if (difficolta_intermedio(difficulty_level)) {
    probabilita_fantasma += 0.1;
} else if (difficolta_incubo(difficulty_level)) {
    probabilita_fantasma += 0.15;
}

    if (giocatore->posizione->fantasma_presente)
    {
        printf("Non puoi tornare al caravan perché il fantasma è nella stessa zona!\n");
        // Controllo se il fantasma appare
        if ((double)rand() / RAND_MAX < probabilita_fantasma)
        {
            printf("Il fantasma è apparso nel caravan!\n");
            giocatore->posizione->fantasma_presente = true;
        }
    }
    else
    {
        if (giocatore->posizione->zona == giocatore->caravan)
        {
            printf("Sei già nel caravan.\n");
            return;
        }
        
        // Torniamo al caravan solo se il giocatore ha almeno una prova
        bool ha_prova = false;
        for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
        {
            int prova_corrente = giocatore->zaino[i];
            if (prova_corrente == prova_EMF || prova_corrente == prova_spirit_box || prova_corrente == prova_videocamera)
            {
                ha_prova = true;
                break;
            }
        }
        if (!ha_prova)
        {
            printf("Non puoi tornare al caravan senza almeno una prova!\n");
            return;
        }

        // Lasciamo le prove eventualmente raccolte nel caravan
        int n_prove_raccolte = 0;
        for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
        {
            int prova_corrente = giocatore->zaino[i];
            if (prova_corrente == prova_EMF || prova_corrente == prova_spirit_box || prova_corrente == prova_videocamera)
            {
                printf("Hai lasciato la prova %d nel caravan.\n", prova_corrente);
                rimuovi_prova_dallo_zaino(giocatore, prova_corrente);
                n_prove_raccolte++;
            }
        }
// Controllo situazione giocatore
    struct Giocatore *giocatore_corrente = giocatore;
    controlla_situazione_giocatore(giocatore, giocatore_corrente);

        }
}

bool trova_oggetto_nello_zaino(struct Giocatore *giocatore, enum Tipo_oggetto_zona oggetto_da_cercare)
{
    for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
    {
        if (giocatore->zaino[i] == oggetto_da_cercare)
        {
            return 1;
        }
    }
    return 0;
}  

void controlla_situazione_giocatore(struct Giocatore* giocatore, struct Zona_mappa* zona_attuale) {
   
     // Controlla la sanità mentale del giocatore
    if (giocatore->sanita_mentale <= 0) {
        printf("%s ha perso tutti i punti di sanità mentale e non può più giocare.\n", giocatore->nome_giocatore);
        giocatore->ha_perso = 1; // Imposta il flag "gioca" del giocatore a 0 per indicare che non gioca più
        return;
    }
    
     // Se il giocatore ha depositato tutte e tre le prove, dichiara la vittoria
        if (giocatore -> n_prove_raccolte == 3) {
               for (int i = 0; i < 5; i++) { // Ripeti l'animazione 5 volte
        printf("  ,-'     `._\n");
        printf(" (_,..      `.\n");
        printf("    `''-,_    `._    ,',\n");
        printf("          `''-,_`''-,_/ / \n");
        printf("                `''-/''  \n");
        printf("                   \\   \n");
        printf("                    `^'\n");
        usleep(500000); // Aspetta 500 millisecondi (0.5 secondi)
        printf("  ,-'     `._\n");
        printf(" (_,..      `.         ,\n");
        printf("    `''-,_    `._    ,'|\n");
        printf("          `''-,_`''-,_/ / \n");
        printf("                `''-/''  \n");
        printf("                   \\   \n");  
        printf("                    `^'\n");
        usleep(500000); // Aspetta altri 500 millisecondi (0.5 secondi)
    }
            printf(" %s ha depositato tutte e tre le prove necessarie, la partita è vinta!\n", giocatore->nome_giocatore);
            giocatore -> ha_vinto = 1;
                      termina_gioco(giocatore);
       }
      }
      
void rimuovi_prova_dallo_zaino(struct Giocatore *giocatore, int prova_da_rimuovere)
{
    for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
    {
        if (giocatore->zaino[i] == prova_da_rimuovere)
        {
            // Sposta a sinistra tutti gli elementi dopo l'elemento rimosso
            for (int j = i; j < giocatore->n_oggetti_zaino - 1; j++)
            {
                giocatore->zaino[j] = giocatore->zaino[j + 1];
            }
          // Riduci il numero di oggetti nello zaino
            giocatore->n_oggetti_zaino--;

            // Stampa l'elemento rimosso
            const char *nome_prova;
            switch (prova_da_rimuovere)
            {
            case prova_EMF:
                nome_prova = "prova EMF";
                break;
            case prova_spirit_box:
                nome_prova = "prova spirit box";
                break;
            case prova_videocamera:
                nome_prova = "prova videocamera";
                break;
            default:
                nome_prova = "prova sconosciuta";
                break;
            }
            printf("Hai rimosso l'oggetto '%s' dallo zaino.\n", nome_prova);
            break;
        }
    }
}

int controllo_prova(struct Giocatore *giocatore, struct Giocatore *caravan, const enum Tipo_prova tipo_prova)
{

    if (giocatore->posizione != caravan->posizione)
    {
        printf("Devi essere nel caravan per depositare una prova.\n");
        return -1;
    }

    int prova_trovata = 0;
    for (int i = 0; i < giocatore->n_oggetti_zaino; i++)

    {

        if (giocatore->zaino[i] == tipo_prova)
        {
            prova_trovata = 1;
            // Rimuovi la prova dallo zaino del giocatore
            for (int j = i; j < giocatore->n_oggetti_zaino - 1; j++)
            {
                giocatore->zaino[j] = giocatore->zaino[j + 1];
            }
            giocatore->n_oggetti_zaino--;
            break;
        }
    }

    if (!prova_trovata)
    {
        printf("Non hai la prova nel tuo zaino.\n");
        return -1;
    }

    switch (tipo_prova)

    {
    case EMF:
        giocatore->ha_raccolto_prova = 0;
        break;
    case spirit_box:
        giocatore->ha_raccolto_prova = 1;
        break;
    case videocamera:
        giocatore->ha_raccolto_prova = 2;
        break;
    default:
        break;
    }

    // Inizializza prove_trovate a nessuna_prova all'inizio del gioco
    if (giocatore->n_prove_raccolte == 0)
    {

        for (int i = 0; i < 3; i++)
        {
            giocatore->prove_trovate[i] = nessuna_prova;
        }
    }

    int n_prove_depositate = 0;
    for (int i = 0; i < 3; i++)
    {
        if (giocatore->prove_trovate[i] == nessuna_prova)
        {
            giocatore->prove_trovate[i] = tipo_prova;
            n_prove_depositate++;
            break;
        }
    }

    printf("Hai depositato la prova %d nel caravan.\n", tipo_prova);
    return n_prove_depositate;
}

void svuota_zaino(struct Giocatore *giocatore)
{
    printf("Stai per svuotare lo zaino, sei sicuro di volerlo fare? (s/n)\n");

    char risposta;
    scanf(" %c", &risposta);

    if (risposta == 's' || risposta == 'S')
    {
        for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
        {
            giocatore->zaino[i] = nessun_oggetto;
        }
        giocatore->n_oggetti_zaino = 0;

        printf("Lo zaino è stato svuotato.\n");
    }
    else
    {
        printf("Operazione annullata.\n");
    }
}

void raccogli_prova(struct Giocatore *giocatore)
{
    // Controlla se c'è una prova nella zona attuale del giocatore
    if (giocatore->posizione->prova == nessuna_prova)
    {
        printf("Non c'è nessuna prova in questa zona.\n");
    }
    else
    {
        // Controlla se il giocatore ha l'oggetto corrispondente alla prova
        int oggetto_corrispondente = -1;
        switch (giocatore->posizione->prova)
        {
        case prova_EMF:
            oggetto_corrispondente = EMF;
            printf("HAI RACCOLTO LA  PROVA_EMF\n");
            break;
        case prova_spirit_box:
            oggetto_corrispondente = spirit_box;
            printf("HAI RACCOLTO LA PROVA_SPIRIT_BOX\n");
            break;
        case prova_videocamera:
            oggetto_corrispondente = videocamera;
            printf("HAI RACCOLTO LA PROVA_VIDEOCAMERA\n");
            break;
        default:
            printf("Errore: prova non valida.\n");
            exit(EXIT_FAILURE);
        }

        int oggetto_trovato = 0;
        for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
        {
            if (giocatore->zaino[i] == oggetto_corrispondente)
            {
                // Rimuovi l'oggetto dallo zaino del giocatore e aggiungi la prova
                for (int j = i; j < giocatore->n_oggetti_zaino - 1; j++)
                {
                    giocatore->zaino[j] = giocatore->zaino[j + 1];
                }
                giocatore->zaino[giocatore->n_oggetti_zaino - 1] = giocatore->posizione->prova;
                giocatore->ha_raccolto_prova = 1;
                oggetto_trovato = 1;
                break;
            }
        }

        if (!oggetto_trovato)
        {
            printf("Non hai l'oggetto corrispondente per raccogliere questa prova.\n");
            return;
        }

        // Aggiorna il numero di prove raccolte dal giocatore
        giocatore->n_prove_raccolte++;
        printf("Hai raccolto la prova %d in questa zona.\n", giocatore->posizione->prova);
    
    // Calcola la probabilità di apparizione del fantasma
         int probabilita_fantasma = 0;

        switch (difficulty_level)
        {
        case DIFFICOLTA_PRINCIPIANTE:
        probabilita_fantasma = 10;
        break;
        case DIFFICOLTA_INTERMEDIO:
        probabilita_fantasma = 20;
        break;
        case DIFFICOLTA_INCUBO:
        probabilita_fantasma = 30;
        break;
        }
  // Aggiorna la probabilità di apparizione del fantasma in base al numero di prove raccolteve raccolte
  probabilita_fantasma += giocatore->n_prove_raccolte * 5;
  // Controlla se il fantasma appare
  int random = rand() % 100 + 1;
  if (random <= probabilita_fantasma)
  {
      printf("Il fantasma è apparso nella tua zona! Attento!\n");
      // Diminuisci la sanità mentale del giocatore nella zona
      int sanita_mentale_da_diminuire = 0;
      switch (difficulty_level)
      {
      case DIFFICOLTA_PRINCIPIANTE:
          sanita_mentale_da_diminuire = 5;
          break;
      case DIFFICOLTA_INTERMEDIO:
          sanita_mentale_da_diminuire = 10;
          break;
      case DIFFICOLTA_INCUBO:
          sanita_mentale_da_diminuire = 15;
          break;
      }
      giocatore->sanita_mentale -= sanita_mentale_da_diminuire;
      printf("La tua sanità mentale è diminuita di %d punti.\n", sanita_mentale_da_diminuire);

      printf("I tuoi punti vita sono: %d\n", giocatore->sanita_mentale);
  }
    }
}

void avanza(struct Giocatore *giocatore, int nplayers, int *indice_giocatore_corrente, struct Zona_mappa *zona)
{
  
    // Aggiorna il campo "prova" della zona in modo casuale
    int random = rand() % 100 + 1;
    if (random <= 40)
        giocatore->posizione->prova = nessuna_prova;
    else if (random <= 60)
        giocatore->posizione->prova = prova_EMF;
    else if (random <= 80)
        giocatore->posizione->prova = prova_spirit_box;
    else
        giocatore->posizione->prova = prova_videocamera;

    // Aggiorna il campo "oggetto_zona" della zona in modo casuale
    random = rand() % 100 + 1;
    if (random <= 20)
        giocatore->posizione->oggetto_zona = adrenalina;
    else if (random <= 40)
        giocatore->posizione->oggetto_zona = cento_dollari;
    else if (random <= 60)
        giocatore->posizione->oggetto_zona = coltello;
    else if (random <= 80)
        giocatore->posizione->oggetto_zona = calmanti1;
    else
        giocatore->posizione->oggetto_zona = nessun_oggetto;

    printf("Sei nella zona %d. Prova presente: %d. Oggetto presente: %d\n", giocatore->posizione->zona, giocatore->posizione->prova, giocatore->posizione->oggetto_zona);

    // Imposta il flag "turno_avanzato" a 1 per il giocatore corrente
    giocatore->turno_avanzato = 1;

    // Passa il turno al prossimo giocatore
    (*indice_giocatore_corrente)++;
    if (*indice_giocatore_corrente >= nplayers)
        *indice_giocatore_corrente = 0;

    // Verifica se l'indice del giocatore corrente è valido
    if (*indice_giocatore_corrente < 0 || *indice_giocatore_corrente >= nplayers)
    {
        printf("Errore: indice del giocatore corrente non valido.\n");
        exit(EXIT_FAILURE);
    }
    // Mostra il nome del giocatore corrente anzi non lo mostero per niente il giocatore corrente.
}

void azzera_turni(struct Giocatore *giocatori, int nplayers)
{
    for (int i = 0; i < nplayers; i++)
    {
        giocatori[i].turno_avanzato = 0;
    }
}

void passa_turno(struct Giocatore *giocatori, int nplayers, int *indice_giocatore_corrente, int turno_casuale)
{

    // Passa il turno al prossimo giocatore
    if (turno_casuale)
    {
        // Genera un indice casuale per il prossimo giocatore, escluso il giocatore corrente
        int prossimo_giocatore = rand() % (nplayers - 1);
        if (prossimo_giocatore >= *indice_giocatore_corrente)
            prossimo_giocatore++;
        // Aggiorna l'indice del giocatore corrente
        *indice_giocatore_corrente = prossimo_giocatore;
    }
    else
    {
        // Passa il turno al giocatore successivo
        (*indice_giocatore_corrente)++;
        if (*indice_giocatore_corrente >= nplayers)
            *indice_giocatore_corrente = 0;
    }

    // Azzera i turni di tutti i giocatori
    azzera_turni(giocatori, nplayers);

    // Verifica se l'indice del giocatore corrente supera il numero di giocatori
    if (*indice_giocatore_corrente < 0 || *indice_giocatore_corrente >= nplayers)
    {
        printf("Errore: indice del giocatore corrente non valido.\n");
        exit(EXIT_FAILURE);
    }

    // Mostra il nome del giocatore corrente
    printf("Turno del giocatore %s.\n", giocatori[*indice_giocatore_corrente].nome_giocatore);

    // Imposta il flag turno_avanzato a 1 per il giocatore corrente
    giocatori[*indice_giocatore_corrente].turno_avanzato = 1;
mostra_zaino(&giocatori[*indice_giocatore_corrente]);

}

void termina_turno(struct Giocatore *giocatore)
{

    if (!giocatore->turno_avanzato)
    {
        printf("Devi avanzare almeno una volta in questo turno prima di poter terminare il turno.\n");
        return;
    }

    // Aggiorna il campo turno nel Giocatore
    giocatore->turno_avanzato++;

    // Azzera il campo turno_avanzato nel Giocatore
    giocatore->turno_avanzato = 0;

    /// Mostra il messaggio di conferma
}

void stampa_giocatore(struct Giocatore *giocatori)
{
    printf("Giocatore %s:\n", giocatori->nome_giocatore);
    printf("Posizione: %d\n", giocatori->posizione->zona);
    printf("Salute mentale: %d\n", giocatori->sanita_mentale);
    mostra_zaino(giocatori);

}

void stampa_zona(struct Giocatore *giocatore, struct Zona_mappa *)
{
    struct Zona_mappa *zona = giocatore->posizione;
    printf("Zona attuale: %d\n", zona->zona);
    printf("Prova richiesta: %d\n", zona->prova);
    printf("Oggetto della zona: %d\n", zona->oggetto_zona);
    printf("Fantasma presente: %d\n", zona->fantasma_presente);
}

void raccogli_oggetto(struct Giocatore *giocatore)
{
    // Verifica se il giocatore ha posto nello zaino
    if (giocatore->n_oggetti_zaino == 4)
    {
        printf("Zaino pieno. Scegliere un'altra opzione.\n");
        return;
    }

    // Verifica se nella zona è presente un oggetto
    if (giocatore->posizione->oggetto_zona == nessun_oggetto)
    {
        printf("Non ci sono oggetti in questa zona. Scegliere un'altra opzione.\n");
        return;
    }
    // Aggiunge l'oggetto allo zaino del giocatore
    giocatore->zaino[giocatore->n_oggetti_zaino] = giocatore->posizione->oggetto_zona;
    giocatore->n_oggetti_zaino++;

    // Rimuove l'oggetto dalla zona
    giocatore->posizione->oggetto_zona = nessun_oggetto;

    printf("Oggetto raccolto. Zaino attuale:\n");
    mostra_zaino(giocatore);
}

// Funzione per calcolare la difficoltà del fantasma in base alla difficoltà della zona
int difficolta_fantasma(int difficulty_level)
{
    int diff_fantasma;
    switch (difficulty_level)
    {
    case principiante:
        diff_fantasma = 2;
        break;
    case intermedio:
        diff_fantasma = 5;
        break;
    case incubo:
        diff_fantasma = 10;
        break;
    default:
        diff_fantasma = 0;
        break;
    }
    return diff_fantasma;
}
// Funzione per verificare se la difficoltà della zona è media
int difficolta_principiante(int difficulty_level)
{
    return difficulty_level == principiante;
}

// Funzione per verificare se la difficoltà della zona è alta
int difficolta_intermedio(int difficulty_level)
{
    return difficulty_level == intermedio;
}

// Funzione per verificare se la difficoltà della zona è "Principiante"
int difficolta_incubo(int difficulty_level)
{
    return difficulty_level == incubo;

}

char *tipo_prova_string(enum Tipo_prova tipo_prova)
{
    switch (tipo_prova)
    {
    case prova_EMF:
        return "EMF";
    case prova_spirit_box:
        return "spirit_box";
    case prova_videocamera:
        return "videocamera";
    default:
        return "nessuna prova";
    }
}

void usa_oggetto(struct Giocatore *giocatore, int nplayers, int *indice_giocatore_corrente, struct Zona_mappa * zona)
{

    int oggetto_scelto;
    do
    {
        printf("scegli l'oggetto da usare:\n");
        printf("0. adrenalina\n");    // sale
        printf("1. cento_dollari\n"); // calamante
        printf("2. coltello\n");      // 100 dollari
        printf("3. calmanti1\n");
        printf("4. sale\n");
        scanf("%d", &oggetto_scelto);
    } while (oggetto_scelto < 0 || oggetto_scelto > 3);

    {
        switch (oggetto_scelto)
       {
           
        case adrenalina:
         printf("Hai usato l'adrenalina e puoi avanzare un'altra volta.\n");
        avanza(giocatore, nplayers, indice_giocatore_corrente, zona);        int nuova_zona = rand() % 5 + 1; // genera un numero casuale tra 1 e 5
        giocatore->posizione = &zona[nuova_zona - 1]; // imposta la posizione del giocatore sulla nuova zona
        avanza(giocatore, nplayers, indice_giocatore_corrente, giocatore->posizione);
        break;
        case cento_dollari:
            if (giocatore->n_oggetti_zaino >= 4)
            {
                printf("Lo zaino è già pieno, non puoi prendere un oggetto nuovo.\n");
                break;
            }
            if (trova_oggetto_nello_zaino(giocatore, cento_dollari))
            {
                rimuovi_oggetto_dallo_zaino(giocatore, cento_dollari);
                int random = rand() % 2;
                if (random == 0)
                {
                    giocatore->zaino[giocatore->n_oggetti_zaino] = sale;
                    printf("Hai usato i 100 dollari e al loro posto è comparso un sacchetto di Sale nello zaino.\n");
                }
                else
                {
                    giocatore->zaino[giocatore->n_oggetti_zaino] = calmanti;
                    printf("Hai usato i 100 dollari e al loro posto è comparso un flacone di Calmanti nello zaino.\n");
                }
                giocatore->n_oggetti_zaino++;
            }
            else
            {
                printf("Non hai i 100 dollari nello zaino!\n");
            }
            break;
        case coltello:
            if (trova_oggetto_nello_zaino(giocatore, coltello))
            {
                if (giocatore->sanita_mentale < 30)
                {
                    printf("Hai usato il coltello e hai ucciso tutti gli altri giocatori nella tua zona.\n");
                    uccidi_giocatore(giocatore, nplayers, indice_giocatore_corrente);
                }
                else
                {
                    printf("La tua sanità mentale è troppo alta per usare il coltello.\n");
                }
            }
            else
            {
                printf("Non hai il coltello nello zaino!\n");
            }
            break;
        case calmanti:
            if (trova_oggetto_nello_zaino(giocatore, calmanti))
            {
                giocatore->sanita_mentale += 40;
                printf("Hai usato i calmanti e la tua sanità mentale è aumentata di 40 punti.\n");
                rimuovi_oggetto_dallo_zaino(giocatore, calmanti);
            }
            else
            {
                printf("Non hai i calmanti nello zaino!\n");
            }
            break;

        case sale:
            printf("hai trovato il sale\n");

            break;
        default:
          if (trova_oggetto_nello_zaino(giocatore, oggetto_scelto)){
            printf("NON conosco questo oggetto, non so come usarlo\n");
          
          }else {
            printf("non ho questo oggetto nello zaino1\n");
          }
            
       }

        probabilita_decremento_salute_mentale(giocatore);
    }
}

void rimuovi_oggetto_dallo_zaino(struct Giocatore *giocatore, enum Tipo_oggetto_zona oggetto_da_rimuovere)
{
    for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
    {
        if (giocatore->zaino[i] == oggetto_da_rimuovere)
        {
            for (int j = i; j < giocatore->n_oggetti_zaino - 1; j++)
            {
                giocatore->zaino[j] = giocatore->zaino[j + 1];
            }
            giocatore->n_oggetti_zaino--;
            return;
        }
    }
}

void probabilita_decremento_salute_mentale(struct Giocatore *giocatore)
{

    if (rand() % 100 < 20)
    {

        giocatore->sanita_mentale -= 15;
        printf("la tua sanita mentale e diminuita del 15 punti.\n");
    }
}

void uccidi_giocatore(struct Giocatore *giocatore, int nplayers, int *indice_giocatore_corrente)
{
    int giocatore_da_uccidere;
    do
    {//uccide un giocatore a piaciento
        giocatore_da_uccidere = rand() % nplayers;
    } while (giocatore_da_uccidere == *indice_giocatore_corrente);

    giocatore[giocatore_da_uccidere].sanita_mentale = 0; // 0 può indicare il valore "Morto"
    printf("Hai usato il coltello e ucciso il giocatore %d.\n", giocatore_da_uccidere + 1);
}

bool cefantasma(struct Giocatore *giocatore)
{
    // genera un numero casuale tra 0 e 1
    int r = rand() % 2;

    // verifica se il giocatore ha usato l'oggetto "Sale"
    bool ha_usato_sale = false;
    for (int i = 0; i < giocatore->n_oggetti_zaino; i++)
    {
        if (giocatore->zaino[i] == sale)
        {
            ha_usato_sale = true;
            // Rimuovi il Sale dallo zaino del giocatore
            for (int j = i; j < giocatore->n_oggetti_zaino - 1; j++)
            {
                giocatore->zaino[j] = giocatore->zaino[j + 1];
            }
            giocatore->n_oggetti_zaino--;
            break;
        }
    }

    // applica l'effetto del "Sale" solo se il fantasma appare
    if (r == 0 || ha_usato_sale)
    {
        printf("Il fantasma non è comparso.\n");
        return false;
    }
    else
    {
        printf("Il fantasma è comparso.\n");
        giocatore->sanita_mentale -= 10;
        return true;
    }
}

void termina_gioco(struct Giocatore *giocatore_corrente)
{
    // Mostra il messaggio di uscita
    printf("Grazie per aver giocato!\n");

    // Chiede all'utente se vuole giocare di nuovo
    char scelta;
    do {
        printf("Vuoi giocare di nuovo? (s/n) ");
        scanf(" %c", &scelta);
    } while (scelta != 's' && scelta != 'n');

    // Se l'utente vuole giocare di nuovo, riavvia il gioco
    if (scelta == 's') {
        riavvia_gioco(giocatore_corrente, giocatore_corrente->nplayers);
    } else {
        // Termina il programma
        exit(EXIT_SUCCESS);
    }
}

void riavvia_gioco(struct Giocatore *giocatore, int nplayers)
{
    // Dealloca la memoria dinamica allocata per i giocatori e gli oggetti
    for (int i = 0; i < nplayers; i++)
    {
        free(giocatore[i].zaino);
    }
    free(giocatore);
    // Dealloca la memoria dinamica allocata per i giocatori e gli oggetti

    // Reinizializza le variabili per iniziare una nuova partita
    nplayers = 0;
    // altre variabili necessarie per una nuova partita

    // Chiede all'utente se vuole giocare di nuovo
    char scelta;
    do
    {
        printf("Vuoi giocare di nuovo? (s/n) ");
        scanf(" %c", &scelta);
    } while (scelta != 's' && scelta != 'n');

    if (scelta == 's')
    {
        // Chiama la funzione menu_gioco per iniziare una nuova partita
        gioca(giocatore);
    }
    else
    {
        termina_gioco(giocatore);
        printf("Arrivederci!\n");
        exit(0);
    }
}

/*
void play_music() {
    // Inizializza SDL e SDL_mixer
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    // Carica il file audio MP3
    Mix_Music *music = Mix_LoadMUS("music.mp3");
    if (!music)
    {
        printf("Errore durante il caricamento del file audio: %s\n", Mix_GetError());
        return;
    }
    // Riproduci il file audio
    Mix_PlayMusic(music, 0);
}



*/



















