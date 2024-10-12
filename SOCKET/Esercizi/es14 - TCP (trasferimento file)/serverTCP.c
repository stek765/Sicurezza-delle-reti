#include "network.h"

int main() {
	char filename[MTU], c;
	socketif_t server;
	FILE *fptr1, *fptr2;
	int i;
	
	server = createTCPServer(35000);
	if (server < 0) {
		printf("[SERVER] Error: %i\n", server);
		return -1;
	}
	
	while(1) {
		fptr1 = acceptConnectionFD(server);
		
		i = 0;
		filename[i] = fgetc(fptr1);
		while(filename[i]!='\0') {
			i++;
			filename[i] = fgetc(fptr1);
		}   
		
		printf("[SERVER] Nome del file richiesto: %s\n", filename);
		
		// apertura file fptr2 in lettura
		fptr2 = fopen(filename, "r");
		if (fptr2 == NULL) {
			printf("[SERVER] Errore apertura file %s \n", filename);
			fclose(fptr1);
			continue;
		}
		
		// lettura primo byte dalla fptr2
		c = fgetc(fptr2);
		while (c != EOF) {
			// scrittura del byte nella fptr1
			fputc(c, fptr1);
			fflush(fptr1);
			c = fgetc(fptr2);
		}
		
		printf("[SERVER] File inviato\n");
		
		fclose(fptr2);        
		fclose(fptr1);
	}
	return 0;
}
