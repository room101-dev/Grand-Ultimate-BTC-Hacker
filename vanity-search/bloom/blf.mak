HEADERS = bloom.h  hash160.h bloom2.h hex.h fsearch.h mmapf.h bloom4.h bloom1.h
OBJ_MAIN =  hex2blf.o blfchk.o  hexln.o filehex.o hex2blf2.o blfchk2.o bloom2.o hex2blf4.o blfchk4.o hex2blf1.o
OBJ_UTIL = hex.o bloom.o mmapf.o hsearchf.o  dldummy.o bloom1.o bloom2.o bloom4.o
OBJ_ALGO = $(patsubst %.c,%.o,$(wildcard algo/*.c))
OBJECTS = $(OBJ_MAIN) $(OBJ_UTIL) $(OBJ_ALGO)
BINARIES = hexln hex2blf blfchk  filehex hex2blf2 blfchk2 hex2blf4 blfchk4 hex2blf1 \
blfchk1 binchk
LIBS = -lssl -lrt -lcrypto -lz -lgmp
# was -O3 debug is -O0, -g enables debug
CFLAGS = -O3 \
         -flto -funsigned-char -falign-functions=16 -falign-loops=16 -falign-jumps=16 \
         -Wall -Wextra -Wno-pointer-sign -Wno-sign-compare \
         -pedantic -std=gnu99  -g -ggdb
COMPILE = gcc $(CFLAGS) 

all: $(BINARIES)

hex2blf.o: hex2blf.c bloom.c bloom.h

hex2blf1.o: hex2blf1.c bloom1.c bloom1.h

blfchk.o: blfchk.c bloom.c bloom.h 

blfchk1.o: blfchk1.c bloom1.c bloom1.h

hex2blf2.o: hex2blf2.c bloom2.c bloom2.h

blfchk2.o: blfchk2.c bloom2.c bloom2.h 

hex2blf4.o: hex2blf4.c bloom4.c bloom4.h

blfchk4.o: blfchk4.c bloom4.c bloom4.h 



hex2blf4: hex2blf4.o hex.o bloom4.o mmapf.o 
	$(COMPILE) -static $^ $(LIBS) -lm -o $@	
blfchk4: blfchk4.o hex.o bloom4.o mmapf.o hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@
