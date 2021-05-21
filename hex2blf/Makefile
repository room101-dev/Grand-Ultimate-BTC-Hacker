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
         -pedantic -std=gnu99  -g -ggdb -m64
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

hex2blf8.o: hex2blf8.c bloom8.c bloom8.h

blfchk8.o: blfchk8.c bloom8.c bloom8.h 

hexln.o: hexln.c

filehex.o: filehex.c

binchk.o: binchk.c 

%.o: %.c
	$(COMPILE) -c $< -o $@

hexln: hexln.o hex.o
	$(COMPILE) -static $^ $(LIBS) -o $@

blfchk: blfchk.o hex.o bloom.o mmapf.o hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@

hex2blf: hex2blf.o hex.o bloom.o mmapf.o 
	$(COMPILE) -g -O0 -static $^ $(LIBS) -lm -o $@

blfchk2: blfchk2.o hex.o bloom2.o mmapf.o hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@

hex2blf2: hex2blf2.o hex.o bloom2.o mmapf.o 
	$(COMPILE) -static $^ $(LIBS) -lm -o $@
	
hex2blf1: hex2blf1.o hex.o bloom1.o mmapf.o 
	$(COMPILE) -static $^ $(LIBS) -lm -o $@

blfchk1: blfchk1.o hex.o bloom1.o mmapf.o hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@
	
blfchk4: blfchk4.o hex.o bloom4.o mmapf.o hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@

hex2blf4: hex2blf4.o hex.o bloom4.o mmapf.o 
	$(COMPILE) -static $^ $(LIBS) -lm -o $@	

blfchk8: blfchk8.o hex.o bloom8.o mmapf.o hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@

hex2blf8: hex2blf8.o hex.o bloom8.o mmapf.o 
	$(COMPILE) -static $^ $(LIBS) -lm -o $@	


filehex: filehex.o hex.o
	$(COMPILE) -static $^ $(LIBS) -o $@


binchk: binchk.o hex.o  hsearchf.o
	$(COMPILE) -static $^ $(LIBS) -o $@

clean:
	rm -f $(BINARIES) $(OBJECTS)
