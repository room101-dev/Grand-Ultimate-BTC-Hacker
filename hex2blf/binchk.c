/* Copyright (c) 2015 Ryan Castellucci, All Rights Reserved */
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include <arpa/inet.h> /* for ntohl/htonl */

#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "hex.h"
//#include "bloom.h"
//#include "mmapf.h"
#include "hash160.h"
#include "hsearchf.h"

#include <sys/stat.h>

int main(int argc, char **argv) {
  int ret;
  hash160_t hash;
  char *line = NULL;
  size_t line_sz = 0;
  unsigned char buf[128];
  unsigned char *bloom, *bloomfile, *hashfile;
  FILE *ifile = stdin, *ofile = stdout, *hfile = NULL;
  //mmapf_ctx bloom_mmapf;


	  int64_t i=0; // support > 2gb hashes in file

  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: %s  HASH_FILE\n", argv[0]);
    return 1;
  }
  
	printf("Processing Bin=%s\n", argv[1] );
	
	struct stat st; // support file-size print
	stat(argv[1], &st);
	int64_t size = st.st_size;
	printf("File Size %ld\n", size);	

  if (argc == 2) {
    hashfile = argv[1];
    hfile = fopen(hashfile, "r");
    
    if (hfile==0){
		fprintf(stderr, "failed to open bin file '%s'\n", argv[1]);
		return 1 ;
	}
  
	  while (getline(&line, &line_sz, ifile) > 0) {
		unhex(line, strlen(line), hash.uc, sizeof(hash.uc)); 

		  if (hfile && hsearchf(hfile, &hash)) {
			fprintf(ofile, "%s (positive)\n", hex(hash.uc, sizeof(hash.uc), buf, sizeof(buf)));
			//continue;
		  }

		i++;
	  }
  }
  

	printf("Processed %d\n", i );
  return 0;
}

/*  vim: set ts=2 sw=2 et ai si: */
