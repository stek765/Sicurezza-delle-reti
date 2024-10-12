all: clientUDP.c serverUDP.c network.c
	gcc -o clientUDP clientUDP.c network.c -I.
	gcc -o serverUDP serverUDP.c network.c -I.
	

clean:
	rm -rf clientUDP
	rm -rf serverUDP