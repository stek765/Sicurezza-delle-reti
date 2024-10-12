all: clientUDP.c serverUDP.c network.c
	gcc -o clientUDP clientUDP.c network.c -lpthread
	gcc -o serverUDP serverUDP.c network.c -lpthread
	

clean:
	rm -rf clientUDP
	rm -rf serverUDP