OBJS     = bankserver.o bankclient.o SimpleL_pointer.o TStoixeioyListas.o
SOURCE   = bankserver.c bankclient.c SimpleL_pointer.c TStoixeioyListas.c
HEADER   = Pointer_List.h TStoixeioyListas.h
CC       = gcc
FLAGS    = -g -c

# -g for  debugging  mode ; -c for  objects  file  creation

all: bankserver  bankclient

bankserver: bankserver.o SimpleL_pointer.o TStoixeioyListas.o
	$(CC) -o bankserver bankserver.o SimpleL_pointer.o TStoixeioyListas.o -lpthread

bankclient: bankclient.o
	$(CC) -o bankclient bankclient.o

bankserver.o: bankserver.c
	$(CC) $(FLAGS) bankserver.c

SimpleL_pointer.o: SimpleL_pointer.c
	$(CC) $(FLAGS) SimpleL_pointer.c

TStoixeioyListas.o: TStoixeioyListas.c
	$(CC) $(FLAGS) TStoixeioyListas.c

bankclient.o: bankclient.c
	$(CC) $(FLAGS) bankclient.c

# clean  house
clean:
	rm -f $(OBJS) bankserver bankclient
