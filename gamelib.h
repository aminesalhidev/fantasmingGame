#ifndef H_GAMELIB
#define H_GAMELIB



#define TROVATO -1 // o qualsiasi altro valore che preferisci


extern void rimuovi_oggetto_dallo_zaino();
extern _Bool trova_oggetto_nello_zaino();
// Dichiarazione della funzione cefantasma
extern _Bool cefantasma();

//extern void play_music();
extern void imposta_gioco();
extern void gioca();
extern void termina_gioco();
extern void inserisci_zona();
extern void stampa_mappa();
extern void chiudi_mappa();
extern void cancella_zona();
extern void scelta_menu();
extern void avanza();
extern void torna_caravan();
extern void stampa_giocatore();
extern void stampa_zona();
extern void avanza();
extern void raccogli_prova();
extern void raccogli_oggetto();
extern void usa_oggetto();
extern void passa_turno();
extern void termina_turno(); 
extern void svuota_zaino();
extern int controllo_prova();
extern void deposita_prova();
extern void uccidi_giocatore();
extern void probabilita_decremento_salute_mentale();
extern void riavvia_gioco();
extern void verifica_vittoria();
extern void avere_prova();
extern void rimuovi_prova_dallo_zaino();
extern void controlla_situazione_giocatore();
extern void mappacircolare();


enum Tipo_Difficolta { principiante, intermedio, incubo };
enum Tipo_oggetto_iniziale { EMF, spirit_box, videocamera, calmanti, sale };
enum Tipo_oggetto_zona { adrenalina, cento_dollari, coltello, calmanti1, nessun_oggetto };
enum Tipo_zona {  cucina, soggiorno, camera, bagno, garage, seminterrato };
enum Tipo_prova { prova_EMF, prova_spirit_box, prova_videocamera, nessuna_prova };


struct Zona_mappa *genera_mappa();

struct Zona_mappa {
    enum Tipo_Difficolta difficulty_level;
    enum Tipo_zona zona;
    enum Tipo_prova prova;
    enum Tipo_oggetto_zona oggetto_zona;
    struct Zona_mappa* prossima_zona;
    int fantasma_presente;
    int probabilità_fantasma;
    int oggetti_caravan[3];
    struct Giocatore* giocatore;
    struct Zona_mappa* caravan;
};


// Dichiarazioni delle funzioni
struct Giocatore *crea_giocatore(const char *nome_giocatore, struct Zona_mappa *posizione_iniziale);
struct Posizione *crea_posizione(/* parametri */);


struct Giocatore {
    struct Giocatore* successivo;
    char nome_giocatore[10];
    unsigned char sanita_mentale;
    struct Zona_mappa* posizione;
    unsigned char zaino[4];
    int crea_giocatore;
    int caravan;
    int  fantasma;
    int turno_avanzato;
    int ha_raccolto_prova;
    int n_oggetti_zaino; // Aggiunto campo     int n_oggetti_zaino
    int nplayers;
    int n_prove_raccolte;  // nuovo membro
    int ha_vinto;
    int probabilità_fantasma;
    enum Tipo_prova prove_trovate[3];
    int vivo;
    int Morto;
    int prove_raccolte;
    int ha_perso;
    int zaino_attuale;
  

};

struct Oggetto {
    char nome_oggetto[20];
    enum Tipo_oggetto_iniziale tipo_oggetto;
    struct Oggetto *prossimo_oggetto;
    int oggetto_da_cercare;
   
};
// Dichiarazioni delle funzioni
int difficolta_principiante(int difficulty_level);
int difficolta_intermedio(int difficulty_level);
int difficolta_incubo(int difficulty_level);


#endif
