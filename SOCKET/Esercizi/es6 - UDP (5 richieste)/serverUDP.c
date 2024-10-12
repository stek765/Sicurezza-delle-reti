#include "network.h"

int main(void) {
    socketif_t socket;
    char response[]="Sono il server: ho ricevuto correttamente il tuo messaggio!\n";
    char request[MTU];
    char hostAddress[MAXADDRESSLEN];
    int port;
    
    socket = createUDPInterface(10000);
    
    for (int i = 1 ; i <= 5 ; i++) {
      printf( "[SERVER] Sono in attesa di richieste da qualche client \n");
      UDPReceive(socket,request,MTU,hostAddress,&port);
    
      printf("[SERVER] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, port);
      printf("[SERVER] Contenuto: %s\n", request);
      UDPSend(socket,response,strlen(response),hostAddress,port);
      
      printf("[SERVER] Ho soddisfatto la richiesta numero: %d!\n", i);
	}
    
}

