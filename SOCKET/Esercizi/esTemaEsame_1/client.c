#include "network.h"
#include <stdio.h>
#include <stdlib.h>

// Definizione di una struttura per i dati da inviare al server
typedef struct {
    int num1;
    int num2;
    int operatore;
} DatiCalcolo;

int main(void) {
    DatiCalcolo dati;
    int risultato;
    connection_t connection;
    
    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 35000);
    
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
        return -1;
    }
    
    // Input dei dati da parte dell'utente
    printf("[CLIENT] Inserisci il primo numero intero:\n");
    scanf("%d", &dati.num1);
    
    printf("[CLIENT] Inserisci il secondo numero intero:\n");
    scanf("%d", &dati.num2);
    
    printf("[CLIENT] Scegli l'operazione:\n\n");
    printf("1 - Somma\n");
    printf("2 - Sottrazione\n");
    printf("3 - Moltiplicazione\n");
    printf("4 - Divisione\n\n");
    scanf("%d", &dati.operatore);
    
    // Invio dei dati al server in un unico messaggio
    TCPSend(connection, &dati, sizeof(dati));
    
    // Ricezione del risultato dal server
    TCPReceive(connection, &risultato, sizeof(risultato));
    
    printf("[CLIENT] Risultato ricevuto dal server: %d\n", risultato);
    
    closeConnection(connection);
    
    return 0;
}
