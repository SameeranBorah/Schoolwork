all: test_client rendezvous_server

test_client: test_client.c network_connections.h constants.h
	gcc -g -pthread test_client.c -o test_client

rendezvous_server: rendezvous_server.c network_connections.h constants.h
	gcc -g -pthread rendezvous_server.c -o rendezvous_server

clean:
	rm rendezvous_server test_client *.o *~
