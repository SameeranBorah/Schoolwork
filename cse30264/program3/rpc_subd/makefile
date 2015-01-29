all: rpc_subd
	
rpc_subd: rpc_subd.o sub_svc.o sub_xdr.o
	gcc -o rpc_subd rpc_subd.o sub_svc.o sub_xdr.o -lnsl

rpc_subd.o: rpc_subd.c
	gcc -c rpc_subd.c

sub_svc.o: sub_svc.c
	gcc -c sub_svc.c
sub_xdr.o: sub_xdr.c
	gcc -c sub_xdr.c
clean:
	rm -rf rpc_subd *.o *~ sub_* sub.*
