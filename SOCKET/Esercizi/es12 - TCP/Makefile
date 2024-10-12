all: clientTCP.c serverTCP.c network.c
	gcc -o clientTCP clientTCP.c network.c -I.
	gcc -o serverTCP serverTCP.c network.c -I.
	

clean:
	rm -rf clientTCP
	rm -rf serverTCP
