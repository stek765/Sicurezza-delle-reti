#include "network.h"

int main(void) {
    int request;
    int response;
    socketif_t socket;
    char hostAddress[MAXADDRESSLEN];
    int port;
    int somma = 0;
    
    socket = createUDPInterface(35000);
    
    do {
	    printf("[SERVER] Sono in attesa di richieste da qualche client\n");
	    UDPReceive(socket, &request, sizeof(request), hostAddress, &port);
    	
        if (request == 0){
            printf("\n\n[SERVER] Ho ricevuto il valore di terminazione host/porta: %s/%d\n", hostAddress, port);
            UDPSend(socket, &somma, sizeof(somma), hostAddress, port);
        }
    	printf("[SERVER] Sommo il numero %d\n", request);
    	somma += request;
    } while(true);
    
}

