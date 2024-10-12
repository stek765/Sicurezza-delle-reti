#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num1, num2, operatore;
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
    scanf("%d", &num1);
    
    // Invio del primo numero al server
    TCPSend(connection, &num1, sizeof(num1));
    
    printf("[CLIENT] Inserisci il secondo numero intero:\n");
    scanf("%d", &num2);
    
    // Invio del secondo numero al server
    TCPSend(connection, &num2, sizeof(num2));
    
    printf("[CLIENT] Scegli l'operazione:\n");
    printf("1 - Somma\n");
    printf("2 - Sottrazione\n");
    printf("3 - Moltiplicazione\n");
    printf("4 - Divisione\n");
    scanf("%d", &operatore);
    
    // Invio dell'operatore al server
    TCPSend(connection, &operatore, sizeof(operatore));
    
    // Ricezione del risultato dal server
    TCPReceive(connection, &risultato, sizeof(risultato));
    
    printf("[CLIENT] Risultato ricevuto dal server: %d\n", risultato);
    
    closeConnection(connection);
    
    return 0;
}
