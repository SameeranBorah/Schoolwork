all: submarine

submarine: submarine.o sub_clnt.o sub_xdr.o
	gcc -o submarine submarine.o sub_clnt.o sub_xdr.o -lnsl
submarine.o: submarine.c
	gcc -c submarine.c
sub_clnt.o: sub_clnt.c
	gcc -c sub_clnt.c
sub_svc.o: sub_svc.c
	gcc -c sub_svc.c
sub_xdr.o: sub_xdr.c
	gcc -c sub_xdr.c
clean:
	rm -rf *.o *~ submarine sub_* sub.*
