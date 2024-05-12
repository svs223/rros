#include <stddef.h>
#include <stdint.h>

#include "gpio.h"

#define PAGESIZE 4096

// Granularity 
#define PT_PAGE 0b11
#define PT_BLOCK 0b01

// Accessibility
#define PT_KERNEL (0<<6) // Privledged
#define PT_USER  (1<<6) // Unprivledged
#define PT_RW (0<<7)
#define PT_RO (1<<7)
#define PT_AF (1<<10)
#define PT_NX (1UL<<54)

// Sharablity
#define PT_OSH (2<<8) // Outer sharibility
#define PT_ISH (3<<8) // Inner sharibility

// Defined in MAIR reg
#define PT_MEM (0<<2) // normal memory
#define PT_DEV (1<<2) // device MMIO
#define PT_NC  (2<<2) // Non-cacheable

#define TTBR_CNP 1

extern volatile uint8_t _data;
extern volatile uint8_t _end;

void mmu_init(){
  uint64_t data_page = (uint64_t)&_data/PAGESIZE;
  uint64_t r, b, *paging = (uint64_t*)&_end; 

  // Create MMU page tables at _end
  paging[0] = (uint64_t)((uint8_t*)&_end+2*PAGESIZE) |
    PT_PAGE |
    PT_AF   |
    PT_USER |
    PT_ISH  |
    PT_MEM;


  paging[2*512]=(uint64_t)((uint8_t*)&_end+3*PAGESIZE) |
    PT_PAGE |
    PT_AF   |
    PT_USER |
    PT_ISH  |
    PT_MEM;

  b=MMIO_BASE>>21;

  
}
