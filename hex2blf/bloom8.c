/* Copyright (c) 2015 Ryan Castellucci, All Rights Reserved */
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "bloom8.h"
#include "mmapf.h"

void dumpbh(char* s,uint32_t *h)
{
  printf("\n%s: ", s );
  for (int i=0;i<5;i++) printf("%x:",h[i]);
  printf("\n");
}

// see how far you must search bloom for magic cookie
uint64_t chk_bloom(unsigned char* bloom)
{
	  uint64_t i;

  for (  i=0;i<BLOOM_SIZE;i++) 
	if (bloom[i] ) return(i); // was == 0x1
  return(-1);
}

uint64_t chk_bloom2(unsigned char* bloom)
{ 
  uint64_t i;
  for ( i=BLOOM_SIZE-1;i>0;i--) if ( bloom[i] ) return(i);
  return(-1);
}

void bloom_set_hash160(unsigned char *bloom, uint32_t *H) { // *h, was uint32_t
//  unsigned int t;
//poc int32 to int64
 uint64_t t; // ok, becase h<=2**32
 //uint64_t  H;
 
 //H = *h & 0x1ffffffffULL; // mask off higher bit in long-long

//dumpbh("Begin",h);
//printf("Begin h0=%llx t(%llx)\n",h[0]);

  t = BH00(H); BLOOM_SET_BIT(t);
  
//printf("bh00(%llx)-t bloom[(N)] | (0x1ULL<<((N)&0x7ULL))) %llx %lld\n",H[0],(uint64_t)t, (0x1ULL<<((t)&0x7ULL)) );

  t = BH01(H); BLOOM_SET_BIT(t);
  t = BH02(H); BLOOM_SET_BIT(t);
  t = BH03(H); BLOOM_SET_BIT(t);
  t = BH04(H); BLOOM_SET_BIT(t);
  t = BH05(H); BLOOM_SET_BIT(t);
  t = BH06(H); BLOOM_SET_BIT(t);
  t = BH07(H); BLOOM_SET_BIT(t);
  t = BH08(H); BLOOM_SET_BIT(t);
  t = BH09(H); BLOOM_SET_BIT(t);
  
  t = BH10(H); BLOOM_SET_BIT2(t);
  t = BH11(H); BLOOM_SET_BIT2(t);
  t = BH12(H); BLOOM_SET_BIT2(t);
  t = BH13(H); BLOOM_SET_BIT2(t);
  t = BH14(H); BLOOM_SET_BIT2(t);
  t = BH15(H); BLOOM_SET_BIT2(t);
  t = BH16(H); BLOOM_SET_BIT2(t);
  t = BH17(H); BLOOM_SET_BIT2(t);
  t = BH18(H); BLOOM_SET_BIT2(t);
  t = BH19(H); BLOOM_SET_BIT2(t);

//printf("bh19(%llx)-t bloom[(N)] | (0x1ULL<<((N)&0x7ULL))) %llx %ld\n",H[0],(uint64_t)t, (0x1ULL<<((t)&0x7ULL)) );

//poc add more bits, 10 added
/*
  t = BH20(H); BLOOM_SET_BIT(t);
 
  t = BH21(H); BLOOM_SET_BIT(t);
  t = BH22(H); BLOOM_SET_BIT(t);
  t = BH23(H); BLOOM_SET_BIT(t);
  t = BH24(H); BLOOM_SET_BIT(t);

  t = BH25(H); BLOOM_SET_BIT(t);
  t = BH26(H); BLOOM_SET_BIT(t);
  t = BH27(H); BLOOM_SET_BIT(t);
  t = BH28(H); BLOOM_SET_BIT(t);
  t = BH29(H); BLOOM_SET_BIT(t);
*/
 //printf("bh29(%llx)-t bloom[(N)] | (0x1ULL<<((N)&0x7ULL))) %llx %ld\n",H[0],(uint64_t)t, (0x1ULL<<((t)&0x7ULL)) );

}

/*
int bloom_save(unsigned char *filename, unsigned char *bloom);
*/

/*  vim: set ts=2 sw=2 et ai si: */
