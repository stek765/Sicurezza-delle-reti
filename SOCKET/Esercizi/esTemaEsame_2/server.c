#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num1, num2, operatore;
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
        
        printf("[SERVER] Connessione instaurata\n");
        
        // Ricezione del primo numero dal client
        TCPReceive(connection, &num1, sizeof(num1));
        printf("[SERVER] Ricevuto primo numero: %d\n", num1);
        
        // Ricezione del secondo numero dal client
        TCPReceive(connection, &num2, sizeof(num2));
        printf("[SERVER] Ricevuto secondo numero: %d\n", num2);
        
        // Ricezione dell'operatore dal client
        TCPReceive(connection, &operatore, sizeof(operatore));
        printf("[SERVER] Ricevuto operatore: %d\n", operatore);
        
        // Esecuzione dell'operazione richiesta
        switch (operatore) {
            case 1: // Somma
                risultato = num1 + num2;
                break;
            case 2: // Sottrazione
                risultato = num1 - num2;
                break;
            case 3: // Moltiplicazione
                risultato = num1 * num2;
                break;
            case 4: // Divisione
                if (num2 != 0)
                    risultato = num1 / num2;
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
        
        // Invio del risultato al client
        printf("[SERVER] Invio risultato: %d\n", risultato);
        TCPSend(connection, &risultato, sizeof(risultato));
        
        // Chiusura della connessione
        closeConnection(connection);
    }
    
    close(socket);
    return 0;
}
