#include <stddef.h>
#include <stdint.h>

#include "gpio.h"
#include "mmio.h"

volatile uint32_t __attribute__((aligned(16))) mbox[36];

#define VIDEOCORE_MBOX  (MMIO_BASE+0x0000B880)
#define MBOX_READ ((volatile uint32_t*)(VIDEOCORE_MBOX+0x0))
#define MBOX_POLL ((volatile uint32_t*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SNDR ((volatile uint32_t*)(VIDEOCORE_MBOX+0x10))
#define MBOX_STAT ((volatile uint32_t*)(VIDEOCORE_MBOX+0x14))
#define MBOX_CONF ((volatile uint32_t*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRIT ((volatile uint32_t*)(VIDEOCORE_MBOX+0x20))
#define MBOX_RESP 0x80000000
#define MBOX_FULL 0x80000000
#define MBOX_EMTY 0x40000000

// Make a mailbox call. 0 -> failure, nonzero -> success
int32_t mbox_call(uint8_t ch){
  uint32_t r = (((unsigned int)((unsigned long)&mbox)&~0xF) | (ch&0xF));

  // wait until we can write to mailbox
  do{asm volatile("nop");}while(*MBOX_STAT & MBOX_FULL);

  // write the address of our message to mailbox w/ channel ident
  *MBOX_WRIT = r;

  // time to wait for a response
  while(1){

    // is there a response?
    do{asm volatile("nop");}while(*MBOX_STAT & MBOX_EMTY);
    
    // is there a response to OUR message?
    if (r == *MBOX_READ) 
      // is it a valid respose?
      return mbox[1] == MBOX_RESP;
   
  }

  // error
  return 0;
}
