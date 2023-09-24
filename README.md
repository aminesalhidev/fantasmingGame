Breve Descrizione del Progetto per i Giocatori

Un gruppo di esperti investigatori del paranormale viene incaricato di raccogliere prove riguardanti presenze sovrannaturali che si manifestano in luoghi infestati. Il loro obiettivo è trovare e documentare tre prove specifiche prima che il fantasma possa causare loro la loro morte: prova EMF, prova videocamera e prova spirit box.
Accesso al Gioco

Per accedere al gioco, è necessario rispondere correttamente a una domanda di sicurezza. La password è già inclusa nel mio codice.
Guida per Configurare la Zona di Gioco

Benvenuto nel nostro avvincente gioco interattivo! Per assicurarti un'esperienza di gioco ottimale, è fondamentale seguire attentamente le istruzioni fornite per configurare adeguatamente la zona di gioco.

    Inizia selezionando l'opzione imposta_gioco(). Ti verranno presentate 4 diverse opzioni:
    a. inserisci_zona
    b. cancella_zona
    c. stampa_zona
    d. chiudi_zona

    La zona di gioco è generata automaticamente in modo casuale. Per visualizzare l'attuale configurazione della zona, scegli l'opzione stampa_zona. Ricorda che è obbligatorio chiudere la mappa alla fine, utilizzando l'opzione chiudi_zona.

    Nota: ti consigliamo di provare a cancellare la zona generata automaticamente e di crearne una nuova a tuo piacimento. La fortuna varia da persona a persona, e potresti scoprire degli oggetti utili che ti aiuteranno a vincere la partita.

Funzione "void gioca()"

La funzione "void gioca()" gestisce il gioco in cui devi inserire il numero di giocatori (massimo quattro) e impostare il livello di difficoltà, che influenzerà l'aggressività del fantasma nel gioco. Una volta generata la zona, i giocatori condivideranno questa area unica e utilizzeranno la funzione "avanza()" per aggiornarla con oggetti e miniprove casuali.
Oggetti con Poteri Speciali

Ogni oggetto raccolto nel gioco ha poteri speciali:

    Sale: Protegge dalla riduzione della sanità mentale in presenza del fantasma.
    Calmanti: Incrementa la sanità mentale del giocatore di 40 punti.
    100 dollari: Sostituisce con un oggetto casuale tra calmanti e sale nello zaino del giocatore.
    Coltello: Se usato con una sanità mentale inferiore a 30, elimina casualmente un altro giocatore (funzione "uccide_casualmente()").
    Adrenalina: Consente al giocatore di avanzare ulteriormente nel gioco, chiamando nuovamente la funzione "avanza()".

Seconda Parte del Gioco

La seconda parte del gioco offre ulteriore divertimento. Puoi rimuovere i commenti nel codice per ascoltare musica durante il gioco.
Esecuzione del Gioco

Per eseguire il gioco nel terminale, digita il seguente comando:

shell

gcc main.c gamelib.c -o gioco -lSDL2 -lSDL2_mixer
$ ./gioco

Attenzione: Il progetto ufficiale viene consegnato senza includere le parti sopra descritte.

Buon divertimento!
