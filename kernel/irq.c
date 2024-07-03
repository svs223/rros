#include <stdint.h>
#include <stddef.h>

#include "kutil.h"
#include "irqdef.h"
#include "uart1.h"
#include "irq.h"

const uint32_t tinterval = 200000;
uint32_t curVal = 0;

void timer_init(){
  uart1_puts("[INFO] Initializing Timer\r\n");
  curVal = kget32(TIMER_CLO);
  curVal += tinterval;
  kput32(TIMER_C1, curVal);
  uart1_puts("[INFO] Timer initialized\r\n");
}

void handle_timer_irq(){
  curVal = curVal + tinterval;
  kput32(TIMER_C1, curVal);
  kput32(TIMER_CS, TIMER_CS_M1);
}



void handle_irq(){
//  uart1_putc('1');
  uint32_t irq_stat = kget32(IRQ_PENDING_1);
  
  switch(irq_stat){
    case (SYSTEM_TIMER_IRQ_1):
      handle_timer_irq();
      break;
  
    default:
      //uart1_puts("unknown irq");
      break;
  }
  
}

void enable_ic(){
  kput32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}
