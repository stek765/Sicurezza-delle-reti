#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#define MAX_ENTRIES 100

typedef struct {
    char targa[8];  
    int passaggi;
} ServerTelepass;

ServerTelepass tabella[MAX_ENTRIES];  // Array per memorizzare le targhe e i passaggi
int numEntries = 0;  // Numero corrente di voci nella tabella

int main(void) {
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
        
        printf("[SERVER] Connessione instaurata\n");
        
        // Ricezione targa
        ServerTelepass nuovoRecord;
        TCPReceive(connection, nuovoRecord.targa, sizeof(nuovoRecord.targa));
        nuovoRecord.targa[7] = '\0';  
        
        printf("[SERVER] Ricevuto targa: %s\n", nuovoRecord.targa);
        
        // Controllo se la targa è già presente nella tabella
        int trovato = 0;
        for (int i = 0; i < numEntries; i++) {
            if (strcmp(tabella[i].targa, nuovoRecord.targa) == 0) {
                // Targa trovata, aggiorno il numero di passaggi
                tabella[i].passaggi++;
                printf("[SERVER] Targa trovata: aggiorno numero passaggi a %d\n", tabella[i].passaggi);
                TCPSend(connection, &tabella[i].passaggi, sizeof(tabella[i].passaggi));
                trovato = 1;
                break;
            }
        }
        
        if (!trovato) {
            // Targa non trovata, la aggiungo alla tabella
            if (numEntries < MAX_ENTRIES) {
                tabella[numEntries] = nuovoRecord;
                tabella[numEntries].passaggi = 1;  // Inizializzo il numero di passaggi a 1
                printf("[SERVER] Targa non trovata: inserito nuovo record con numero passaggi 1\n");
                TCPSend(connection, &tabella[numEntries].passaggi, sizeof(tabella[numEntries].passaggi));
                numEntries++;
            } else {
                printf("[SERVER] Tabella piena, impossibile aggiungere nuove voci\n");
                
            }
        }
        
        closeConnection(connection);
    }
    
    close(socket);
    return 0;
}
