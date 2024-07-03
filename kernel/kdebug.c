#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint64_t dbgc = 0;
bool dbg_swap = false;
bool dbg_err = false;
uint64_t dbgi = 1;

uint64_t dbg_getcntr(){
  return dbgc;
}

uint64_t dbg_getitr(){
  return dbgi;
}

void dbg_setitr(uint64_t i){
  dbgi = i;
}

void dbg_inc(){
  dbgc += dbgi;
}

void dbg_dec(){
  if(dbgc < dbgi){
    dbg_err = true;
    dbgc = 0;
  }else {
    dbgc -= dbgi;
  }
}

void dbg_tgl(){
  dbg_swap = dbg_swap == false ? true : false;
}

bool dbg_getswap(){
  return dbg_swap;
}

uint8_t dbg_safegetswap(){
  return dbg_swap ? 1 : 0;
}

void dbg_clrerr(){
  dbg_err = 0;
}

void dbg_seterr(uint64_t e){
  dbg_err = e;
}
