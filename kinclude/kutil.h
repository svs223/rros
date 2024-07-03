#ifndef KUTIL_H
#define KUTIL_H

#include <stdint.h>

extern void kput32(uint64_t, uint32_t);
extern uint32_t kget32(uint32_t);
extern void hang(void);

int8_t get_el(void);
//inline void nop(void);

#endif
