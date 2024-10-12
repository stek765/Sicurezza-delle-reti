all: clientUDP_inc.c serverUDP_inc.c network.c
	gcc -o clientUDP clientUDP_inc.c network.c -I.
	gcc -o serverUDP serverUDP_inc.c network.c -I.
	

clean:
	rm -rf clientUDP
	rm -rf serverUDP
