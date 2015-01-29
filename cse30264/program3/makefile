all: rpcGen

rpcGen: sub.x
	rpcgen sub.x
	cp sub.h submarine 
	cp sub.h rpc_subd
	cp sub_svc.c submarine 
	cp sub_svc.c rpc_subd
	cp sub_xdr.c submarine 
	cp sub_xdr.c rpc_subd
	mv sub_clnt.c submarine
	

clean:
	rm sub.h* sub_* 
