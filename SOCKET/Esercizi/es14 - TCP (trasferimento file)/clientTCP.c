#include "network.h"

int main() {
	FILE *fptr1, *fptr2;
	char filename[100], c;
	
	printf("[CLIENT] Inserire il nome del file:\n");
	scanf("%s", filename);
	
	fptr1 = createTCPConnectionFD("localhost", 35000);
	
	for(int i = 0; filename[i] != '\0'; i++) {
		fputc(filename[i],fptr1);
	}
	fputc('\0',fptr1);
	
	// apertura del file destinazione in scrittura
	fptr2 = fopen(filename, "w");
	if (fptr2 == NULL) {
		printf("[CLIENT] Errore apertura file %s\n", filename);
		return 1;
	}
	
	// lettura primo byte dalla sorgente
	c = fgetc(fptr1);
	while (c != EOF) {
		// scrittura del byte nella destinazione
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}
	
	printf("[CLIENT] Contenuto trasferito su %s\n", filename);
	
	fclose(fptr2);
	fclose(fptr1);
	return 0;
}
