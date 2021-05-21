/*  Copyright (c) 2015 Ryan Castellucci, All Rights Reserved */
#ifndef __BRAINFLAYER_BLOOM_H_
#define __BRAINFLAYER_BLOOM_H_

#include <stdint.h>

uint64_t chk_bloom(unsigned char* );
uint64_t chk_bloom2(unsigned char* );


/* 2^32 bits bloom filter can be up to 4gb or 32billion bits*/

//poc bump BLOOM_SIZE 2x
//#define BLOOM_SIZE (512*1024*1024)
//#define BLOOM_SIZE (2*512*1024*1024)
//#define BLOOM_SIZE (4ULL*512*1024*1024)
//#define BLOOM_SIZE (8ULL*512*1024*1024)
#define BLOOM_SIZE (16ULL*512*1024*1024)

//poc default int to long ( 1 to 1ULL )
// this is where it all happens, @500mb (N)>>3 is 2**32/8, but now its 2**32/2
//#define BLOOM_SET_BIT(N) (bloom[(N)>>3] = bloom[(N)>>3] | (0x1UL<<((N)&0x7UL)))
//#define BLOOM_SET_BIT(N) (bloom[(N)>>1] = bloom[(N)>>1] | (0x1UL<<((N)&0x7UL)))
//#define BLOOM_SET_BIT(N) (bloom[(N)] = bloom[(N)] | (0x1ULL<<((N)&0x7ULL)))
#define BLOOM_SET_BIT(N) ( bloom[(N)] = bloom[(N)] | (0x1ULL<<((N)&0x7ULL)) )
#define BLOOM_SET_BIT2(N) ( bloom[(N+ 0x100000000ULL)] = bloom[(N+ 0x100000000ULL)] | (0x1ULL<<((N)&0x7ULL)) )


//#define BLOOM_GET_BIT(N) ( ( bloom[(N)>>3]>>((N)&0x7UL) )&0x1UL)
//#define BLOOM_GET_BIT(N) ( ( bloom[(N)>>1]>>((N)&0x7UL) )&0x1UL)
//#define BLOOM_GET_BIT(N) ( ( bloom[(N)]>>((N)&0x7ULL) )&0x1ULL)
#define BLOOM_GET_BIT(N)  ( bloom[(N)]>>((N)&0x7ULL) & 0x1ULL ) 
#define BLOOM_GET_BIT2(N)  ( bloom[(N+ 0x100000000ULL)]>>((N)&0x7ULL) & 0x1ULL ) 

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

#define BH10(N) (uint64_t)(N[0]<< 8|N[1]>>24) //+ 0x100000000ULL // + 2^32, in set-bit, get-bit
#define BH11(N) (uint64_t)(N[1]<< 8|N[2]>>24) 
#define BH12(N) (uint64_t)(N[2]<< 8|N[3]>>24) 
#define BH13(N) (uint64_t)(N[3]<< 8|N[4]>>24) 
#define BH14(N) (uint64_t)(N[4]<< 8|N[0]>>24) 

#define BH15(N) (uint64_t)(N[0]<<24|N[1]>> 8) 
#define BH16(N) (uint64_t)(N[1]<<24|N[2]>> 8) 
#define BH17(N) (uint64_t)(N[2]<<24|N[3]>> 8) 
#define BH18(N) (uint64_t)(N[3]<<24|N[4]>> 8) 
#define BH19(N) (uint64_t)(N[4]<<24|N[0]>> 8)

// the following was to slow doing everything in 64bit
/*
#define BH00(N) (N[0]&0x1 | (uint64_t)N[4]<<1)
#define BH01(N) (N[1]&0x1 | (uint64_t)N[3]<<1)
#define BH02(N) (N[2]&0x1 | (uint64_t)N[2]<<1)
#define BH03(N) (N[3]&0x1 | (uint64_t)N[1]<<1)
#define BH04(N) (N[4]&0x1 | (uint64_t)N[0]<<1)

#define BH05(N) ((uint64_t)N[0]<<1| N[1]&0x1)
#define BH06(N) ((uint64_t)N[1]<<1| N[2]&0x1)
#define BH07(N) ((uint64_t)N[2]<<1| N[3]&0x1)
#define BH08(N) ((uint64_t)N[3]<<1| N[4]&0x1)
#define BH09(N) ((uint64_t)N[4]<<1| N[0]&0x1)

#define BH10(N) (uint64_t)(N[0]<< 8|N[1]>>24)<<1
#define BH11(N) (uint64_t)(N[1]<< 8|N[2]>>24)<<1
#define BH12(N) (uint64_t)(N[2]<< 8|N[3]>>24)<<1
#define BH13(N) (uint64_t)(N[3]<< 8|N[4]>>24)<<1
#define BH14(N) (uint64_t)(N[4]<< 8|N[0]>>24)<<1

#define BH15(N) (uint64_t)(N[0]<<24|N[1]>> 8)<<1
#define BH16(N) (uint64_t)(N[1]<<24|N[2]>> 8)<<1
#define BH17(N) (uint64_t)(N[2]<<24|N[3]>> 8)<<1
#define BH18(N) (uint64_t)(N[3]<<24|N[4]>> 8)<<1
#define BH19(N) (uint64_t)(N[4]<<24|N[0]>> 8)<<1
*/

//poc add another 10 bits, this is to populate the high 1/2 of the 8gb pool
/*
#define BH20(N) ((uint64_t)(N[0]|N[4])<<1)
#define BH21(N) ((uint64_t)(N[1]|N[0])<<1)
#define BH22(N) ((uint64_t)(N[2]|N[1])<<1)
#define BH23(N) ((uint64_t)(N[3]|N[2])<<1)
#define BH24(N) ((uint64_t)(N[4]|N[3])<<1)

#define BH25(N) ((uint64_t)(N[0]<<16|N[1]>>16)<<1)
#define BH26(N) ((uint64_t)(N[1]<<16|N[2]>>16)<<1)
#define BH27(N) ((uint64_t)(N[2]<<16|N[3]>>16)<<1)
#define BH28(N) ((uint64_t)(N[3]<<16|N[4]>>16)<<1)
#define BH29(N) ((uint64_t)(N[4]<<16|N[0]>>16)<<1)
*/

void bloom_set_hash160(unsigned char *, uint32_t *); // was uint32_t

inline unsigned int bloom_chk_hash160(unsigned char *bloom, uint32_t *H) {
  //unsigned int t;
//poc int32 to int64
  uint64_t t;

  
  t = BH00(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH01(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH02(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH03(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH04(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH05(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH06(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH07(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH08(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH09(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  // high 1/2 of 8gb bloom
  t = BH10(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH11(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH12(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH13(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH14(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH15(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH16(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH17(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH18(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
  t = BH19(H); if (BLOOM_GET_BIT2(t) == 0) { return 0; }
//poc add more bits for 8gb++
/*
  t = BH20(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH21(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH22(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH23(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH24(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }

  t = BH25(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH26(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH27(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH28(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
  t = BH29(H); if (BLOOM_GET_BIT(t) == 0) { return 0; }
*/
  return 1;
}

//#define bloom_new() malloc(536870912)
//unsigned char * bloom_load(unsigned char *);
//int bloom_save(unsigned char *, unsigned char *);

/*  vim: set ts=2 sw=2 et ai si: */
#endif /* __BRAINFLAYER_BLOOM_H_ */
