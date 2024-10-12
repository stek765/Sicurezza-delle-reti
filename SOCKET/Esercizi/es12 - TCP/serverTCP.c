#include "network.h"

int main(void) {
    int request, response;
    socketif_t socket;
    connection_t connection;
    
    socket = createTCPServer(35000);
    if (socket < 0){
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    }
    else
    {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");    
        // il server accetterà il secondo client solo dopo aver completato il trattamento della 
        // connessione del primo client. Questo è dovuto al fatto che la funzione acceptConnection è bloccante
        connection = acceptConnection(socket);
        
        printf("[SERVER] Connessione instaurata\n");
        
        int somma = 0;
        do {
	        TCPReceive(connection, &request, sizeof(request));
        	printf("[SERVER] Ho ricevuto la seguente richiesta dal client: %d\n", request);
       		somma += request;
		} while(request != 0);
		
        printf("[SERVER] Invio la risposta al client\n");
        TCPSend(connection, &somma, sizeof(somma));
        
        closeConnection(connection);
    }
}

