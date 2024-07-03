#ifndef KDEBUG_H
#define KDEBUG_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint64_t dbg_getcntr(void);

uint64_t dbg_getitr(void);
void dbg_setitr(uint64_t);
void dbg_inc(void);
void dbg_dec(void);

void dbg_tgl(void);
bool dbg_getswap(void);
uint8_t dbg_safegetswap(void);

uint64_t dbg_geterr();
void dbg_clrerr();
void dbg_mrkerr(uint64_t);

#endif
