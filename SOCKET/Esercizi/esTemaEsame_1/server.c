#include "network.h"
#include <stdio.h>
#include <stdlib.h>

// Definizione di una struttura per i dati ricevuti dal client
typedef struct {
    int num1;
    int num2;
    int operatore;
} DatiCalcolo;

int main(void) {
    DatiCalcolo dati;
    int risultato;
    socketif_t socket;
    connection_t connection;
    
    socket = createTCPServer(35000);
    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
        return -1;
    }
    
    printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");
    
    while (1) {
        connection = acceptConnection(socket);
        if (connection < 0) {
            perror("[SERVER] Errore durante l'accettazione della connessione");
            continue;
        }
        
        printf("[SERVER] Connessione instaurata, leggo messaggio intero\n");
        
        // Ricezione dei dati dal client in un unico messaggio
        TCPReceive(connection, &dati, sizeof(dati));
        
        // Esecuzione dell'operazione richiesta
        switch (dati.operatore) {
            case 1: // Somma
                risultato = dati.num1 + dati.num2;
                break;
            case 2: // Sottrazione
                risultato = dati.num1 - dati.num2;
                break;
            case 3: // Moltiplicazione
                risultato = dati.num1 * dati.num2;
                break;
            case 4: // Divisione
                if (dati.num2 != 0)
                    risultato = dati.num1 / dati.num2;
                else {
                    printf("[SERVER] Errore: divisione per zero\n");
                    risultato = 0; // O gestione errore personalizzata
                }
                break;
            default:
                printf("[SERVER] Errore: operatore non riconosciuto\n");
                risultato = 0; // O gestione errore personalizzata
                break;
        }
        printf("[SERVER] Calcolo eseguito->[%d], invio dati...\n", risultato);
        // Invio del risultato al client
        TCPSend(connection, &risultato, sizeof(risultato));
        
        // Chiusura della connessione
        closeConnection(connection);
    }
    
    close(socket);
    return 0;
}

