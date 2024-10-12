#include "network.h"
#include <stdio.h>
#include <stdlib.h>

#define TARGA "LN427PS"

int main(void) {

    connection_t connection;
    int risultato; 

    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 35000);
    
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
        return -1;
    }
    
    
    printf("[CLIENT] Invio targa [%s] in corso...\n", TARGA);
    
    // Invio targa al server
    TCPSend(connection, TARGA, sizeof(TARGA));
    
    // Ricezione del risultato dal server
    TCPReceive(connection, &risultato, sizeof(risultato));
    
    printf("[CLIENT] Risultato ricevuto dal server, numero di passaggi: %d\n", risultato);
    
    closeConnection(connection);
    
    return 0;
}
