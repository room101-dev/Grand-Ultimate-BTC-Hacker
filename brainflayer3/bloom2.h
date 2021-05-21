/*  Copyright (c) 2015 Ryan Castellucci, All Rights Reserved */
#ifndef __BRAINFLAYER_BLOOM_H_
#define __BRAINFLAYER_BLOOM_H_

#include <stdint.h>

/* 2^32 bits bloom filter can be up to 4gb or 32billion bits*/

//poc bump BLOOM_SIZE 2x
//#define BLOOM_SIZE (512*1024*1024)
#define BLOOM_SIZE (8UL*512*1024*1024)

//poc default int to long ( 1 to 1ULL )
// this is where it all happens, @500mb (N)>>3 is 2**32/8, but now its 2**32/2
//#define BLOOM_SET_BIT(N) (bloom[(N)>>3] = bloom[(N)>>3] | (0x1UL<<((N)&0x7UL)))
//#define BLOOM_SET_BIT(N) (bloom[(N)>>1] = bloom[(N)>>1] | (0x1UL<<((N)&0x7UL)))
#define BLOOM_SET_BIT(N) (bloom[(N)] = bloom[(N)] | (0x1UL<<((N)&0x7UL)))

//#define BLOOM_GET_BIT(N) ( ( bloom[(N)>>3]>>((N)&0x7UL) )&0x1UL)
//#define BLOOM_GET_BIT(N) ( ( bloom[(N)>>1]>>((N)&0x7UL) )&0x1UL)
#define BLOOM_GET_BIT(N) ( ( bloom[(N)]>>((N)&0x7UL) )&0x1UL)

#define BH00(N) (N[0])
#define BH01(N) (N[1])
#define BH02(N) (N[2])
#define BH03(N) (N[3])
#define BH04(N) (N[4])

#define BH05(N) (N[0]<<16|N[1]>>16)
#define BH06(N) (N[1]<<16|N[2]>>16)
#define BH07(N) (N[2]<<16|N[3]>>16)
#define BH08(N) (N[3]<<16|N[4]>>16)
#define BH09(N) (N[4]<<16|N[0]>>16)

#define BH10(N) (N[0]<< 8|N[1]>>24)
#define BH11(N) (N[1]<< 8|N[2]>>24)
#define BH12(N) (N[2]<< 8|N[3]>>24)
#define BH13(N) (N[3]<< 8|N[4]>>24)
#define BH14(N) (N[4]<< 8|N[0]>>24)

#define BH15(N) (N[0]<<24|N[1]>> 8)
#define BH16(N) (N[1]<<24|N[2]>> 8)
#define BH17(N) (N[2]<<24|N[3]>> 8)
#define BH18(N) (N[3]<<24|N[4]>> 8)
#define BH19(N) (N[4]<<24|N[0]>> 8)

//poc add another 10 bits 

#define BH20(N) (N[0]<<12|N[4]>> 20)
#define BH21(N) (N[1]<<12|N[3]>> 20)
#define BH22(N) (N[2]<<12|N[2]>> 20)
#define BH23(N) (N[3]<<12|N[1]>> 20)
#define BH24(N) (N[4]<<12|N[0]>> 20)

#define BH25(N) (N[0]<<20|N[4]>> 12)
#define BH26(N) (N[1]<<20|N[3]>> 12)
#define BH27(N) (N[2]<<20|N[2]>> 12)
#define BH28(N) (N[3]<<20|N[1]>> 12)
#define BH29(N) (N[4]<<20|N[0]>> 12)

void bloom_set_hash160(unsigned char *, uint32_t *);

inline unsigned int bloom_chk_hash160(unsigned char *bloom, uint32_t *h) {
  //unsigned int t;
//poc int32 to int64
  uint32_t t;
  t = BH00(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH01(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH02(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH03(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH04(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH05(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH06(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH07(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH08(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH09(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH10(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH11(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH12(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH13(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH14(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH15(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH16(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH17(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH18(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH19(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
//poc add more bits
/*
  t = BH20(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH21(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH22(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH23(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH24(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }

  t = BH25(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH26(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH27(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH28(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH29(h); if (BLOOM_GET_BIT(t) == 0) { return 0; }
*/
  return 1;
}

//#define bloom_new() malloc(536870912)
//unsigned char * bloom_load(unsigned char *);
//int bloom_save(unsigned char *, unsigned char *);

/*  vim: set ts=2 sw=2 et ai si: */
#endif /* __BRAINFLAYER_BLOOM_H_ */
