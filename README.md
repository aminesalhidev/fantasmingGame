Nome del progetto : fantasming
junion Programmatore: amine salhi.
matricola :355106;

Breve descrizione del progetto per i giocatori che Giocheranno:

Un gruppo di esperti investigatori del paranormale viene incaricato di raccogliere prove riguardanti presenze sovrannaturali che si manifestano in luoghi infestati. Il loro obiettivo è trovare e documentare tre prove specifiche prima che il fantasma possa causare loro la loro morte. riusceranno a recuperare e portare al caravan tutte le prove richieste?: prova EMF , prova videocamera  e prova spirit box.


Per accedere al gioco, è necessario rispondere correttamente a una domanda di sicurezza. Si prega di notare che la password è già inclusa nel mio codice. 

ci siamo!!!

Benvenuto nel nostro avvincente gioco interattivo! Per assicurarti un'esperienza di gioco ottimale, è fondamentale seguire attentamente le istruzioni fornite per configurare adeguatamente la zona di gioco. Di seguito, troverai una guida dettagliata per procedere correttamente. 

    Inizia selezionando l'opzione  imposta_gioco(). A questo punto, ti verranno presentate 4 diverse opzioni:
    a.  inserisci_zona
    B. cancella_zona
    C. stampa_zona
    D. chiudi_zona

    La zona di gioco è generata automaticamente in modo casuale. Per visualizzare l'attuale configurazione della zona, scegli l'opzione  stampa_zona. Ricorda che è obbligatorio chiudere la mappa alla fine, utilizzando l'opzione  chiudi_zona. 

Nota: ti consigliamo di provare a cancellare la zona generata automaticamente e di crearne una nuova a tuo piacimento. La fortuna varia da persona a persona, e potresti scoprire degli oggetti utili che ti aiuteranno a vincere la partita.
Ti auguriamo buona fortuna e un'entusiasmante esperienza di gioco! 

Funzione void gioca();

La funzione "void gioca()" è stata sviluppata per gestire un gioco in cui è richiesto di inserire il numero di giocatori, con un limite massimo di quattro partecipanti. Successivamente, i giocatori devono impostare il livello di difficoltà del gioco, il quale influenzerà l'aggressività del fantasma presente nel gioco. 
Una volta generata una zona, questa sarà unica e condivisa tra tutti i giocatori, che combatteranno insieme in quest'area. Chiamando la funzione "avanza()", la zona verrà aggiornata con oggetti e miniprove casuali. 
I giocatori possono ritornare al Caravan solamente se hanno con sé una prova da depositare. È stata creata la funzione "passa_turno()" per consentire il passaggio del turno al giocatore successivo. Si prega di notare che il cambio di turno non avviene in modo automatico: il turno del giocatore termina solo quando viene chiamata la funzione "torna_caravan()". Lo stesso giocatore dovrà chiamare la funzione "passa_turno()" per cedere il turno al successivo partecipante. 



Ogni oggetto raccolto nel gioco possiede dei poteri speciali: 

    Sale: utilizzando il sale, qualora il fantasma dovesse apparire, non causerà alcuna riduzione della sanità mentale del giocatore. 
    Calmanti: incrementano la sanità mentale del giocatore di 40 punti. 
    100 dollari: utilizzando i dollari, si sostituiranno con un oggetto casuale tra calmanti e sale nello zaino del giocatore. 
    Coltello: se un giocatore impiega il coltello mentre la sua sanità mentale è inferiore a 30, eliminerà casualmente un altro giocatore (funzione "uccide_casualmente()"). 
    Adrenalina: impiegando l'adrenalina, il giocatore avrà la possibilità di avanzare ulteriormente nel gioco, chiamando nuovamente la funzione "avanza()". 



---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SECONDA PARTE DEL GIOCO(): 

La seconda parte del gioco è stata pensata per aumentare il piacere dell'utente (in fase di sviluppo). Si prega di notare che, se si desidera ascoltare musica  mentre si gioca a "Caccia ai fantasmi", è possibile rimuovere i commenti nelle righe di codice relative a "void_play_music" e nel file "gamelib.c" (extern void play_music) nel file "gamelib.c" rimuovere il commento che rende invisibile "play_music" nel main.c. 

Per eseguire il gioco nel terminale, digitare il seguente comando: 
gcc main.c gamelib.c -o gioco -lSDL2 -lSDL2_mixer
$ ./gioco

Attenzione: Il progetto ufficiale viene consegnato senza includere le parti sopra descritte. 

Buon divertimento! 

Sono lieto di presentare il progetto "Fantasming", creato da Amine Salhi (email:  amine.salhi@iomarsciano.it ). 



























