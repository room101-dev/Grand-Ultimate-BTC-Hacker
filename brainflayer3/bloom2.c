/* Copyright (c) 2015 Ryan Castellucci, All Rights Reserved */
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "bloom.h"
#include "mmapf.h"

void dumpbh(char* s,uint32_t *h)
{
  printf("\n%s: ", s );
  for (int i=0;i<5;i++) printf("%lx:",h[i]);
  printf("\n");
}

void bloom_set_hash160(unsigned char *bloom, uint32_t *h) {
//  unsigned int t;
//poc int32 to int64
 uint32_t t;

//dumpbh("Begin",h);
//printf("Begin h=%ld\n",h[0]);

  t = BH00(h); BLOOM_SET_BIT(t);
//printf("bh00-t bloom[(N)>>1] | (0x1UL<<((N)&0x7UL))) %lx %lx %ld\n",t,(t)>>1, (0x1UL<<((t)&0x7UL)) );

  t = BH01(h); BLOOM_SET_BIT(t);
  t = BH02(h); BLOOM_SET_BIT(t);
  t = BH03(h); BLOOM_SET_BIT(t);
  t = BH04(h); BLOOM_SET_BIT(t);
  t = BH05(h); BLOOM_SET_BIT(t);
  t = BH06(h); BLOOM_SET_BIT(t);
  t = BH07(h); BLOOM_SET_BIT(t);
  t = BH08(h); BLOOM_SET_BIT(t);
  t = BH09(h); BLOOM_SET_BIT(t);
  t = BH10(h); BLOOM_SET_BIT(t);
  t = BH11(h); BLOOM_SET_BIT(t);
  t = BH12(h); BLOOM_SET_BIT(t);
  t = BH13(h); BLOOM_SET_BIT(t);
  t = BH14(h); BLOOM_SET_BIT(t);
  t = BH15(h); BLOOM_SET_BIT(t);
  t = BH16(h); BLOOM_SET_BIT(t);
  t = BH17(h); BLOOM_SET_BIT(t);
  t = BH18(h); BLOOM_SET_BIT(t);
  t = BH19(h); BLOOM_SET_BIT(t);

/*
//poc add more bits, 10 added
  t = BH20(h); BLOOM_SET_BIT(t);

//printf("bh20-t bloom[(N)>>1] | (0x1UL<<((N)&0x7UL))) %ld %ld %ld\n",t,(t)>>1, (0x1UL<<((t)&0x7UL)) );

  t = BH21(h); BLOOM_SET_BIT(t);
  t = BH22(h); BLOOM_SET_BIT(t);
  t = BH23(h); BLOOM_SET_BIT(t);
  t = BH24(h); BLOOM_SET_BIT(t);

  t = BH25(h); BLOOM_SET_BIT(t);
  t = BH26(h); BLOOM_SET_BIT(t);
  t = BH27(h); BLOOM_SET_BIT(t);
  t = BH28(h); BLOOM_SET_BIT(t);
  t = BH29(h); BLOOM_SET_BIT(t);
*/
}

/*
int bloom_save(unsigned char *filename, unsigned char *bloom);
*/

/*  vim: set ts=2 sw=2 et ai si: */
