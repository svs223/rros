#include <stddef.h>
#include <stdint.h>

//#include "mmio.h"
#include "gpio.h"

#define AUX_ENABLE      ((volatile uint32_t*)(MMIO_BASE+0x00215004))
#define AUX_MU_IO       ((volatile unsigned int*)(MMIO_BASE+0x00215040))
#define AUX_MU_IER      ((volatile unsigned int*)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR      ((volatile unsigned int*)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR      ((volatile unsigned int*)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR      ((volatile unsigned int*)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR      ((volatile unsigned int*)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR      ((volatile unsigned int*)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  ((volatile unsigned int*)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL     ((volatile unsigned int*)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT     ((volatile unsigned int*)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD     ((volatile unsigned int*)(MMIO_BASE+0x00215068))

void uart1_init(){
  register uint32_t r;
  
  *AUX_ENABLE |= 1;
  *AUX_MU_CNTL = 0;
  *AUX_MU_LCR = 3; // 8 bits
  *AUX_MU_MCR = 0;
  *AUX_MU_IER = 0;
  *AUX_MU_IIR = 0xC6; // disable inturrupts
  *AUX_MU_BAUD = 270; // 115200 baud rate

  // map uart1 to gpio
  r = *GPFSEL1;
  r&=~((7<<12)|(7<<15)); // gpio14, gpio15
  r|=(2<<12)|(2<<15);    // alt5

  *GPFSEL1 = r;
  *GPPUD = 0;

  r=150; while(r--) { asm volatile("nop"); }
  *GPPUDCLK0 = (1<<14)|(1<<15);
  r=150; while(r--) { asm volatile("nop"); }
  *GPPUDCLK0 = 0;        // flush GPIO setup
  *AUX_MU_CNTL = 3;      // enable Tx, Rx
}

void uart1_putc(uint32_t c){
  do {asm volatile("nop");}while(!(*AUX_MU_LSR&0x20));
  *AUX_MU_IO = c;
}

void uart1_puts(char *s){
  for(uint32_t i = 0; s[i] != '\0'; i++){
    uart1_putc(s[i]);
  }
}

char uart1_getc(){
  char r;
  do{asm volatile("nop");}while(!(*AUX_MU_LSR&0x01));
  r=(char)(*AUX_MU_IO);

  return r;
}

void uart1_puth(uint32_t h){
  uint32_t n;
  int32_t c;

  for(c=28; c>=0; c-=4) {
    // highest tetrad
    n=(h>>c)&0xF;
    n+=n>9?0x37:0x30;
    uart1_putc(n);
  } 
}
