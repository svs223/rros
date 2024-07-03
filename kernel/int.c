#include <stddef.h>
#include <stdint.h>

#include "irq.h"

#define S_FRAME_SIZE			256 		// size of all saved registers 

#define SYNC_INVALID_EL1t		0 
#define IRQ_INVALID_EL1t		1 
#define FIQ_INVALID_EL1t		2 
#define ERROR_INVALID_EL1t		3 

#define SYNC_INVALID_EL1h		4 
#define IRQ_INVALID_EL1h		5 
#define FIQ_INVALID_EL1h		6 
#define ERROR_INVALID_EL1h		7 

#define SYNC_INVALID_EL0_64	    	8 
#define IRQ_INVALID_EL0_64	    	9 
#define FIQ_INVALID_EL0_64		10 
#define ERROR_INVALID_EL0_64		11 

#define SYNC_INVALID_EL0_32		12 
#define IRQ_INVALID_EL0_32		13 
#define FIQ_INVALID_EL0_32		14 
#define ERROR_INVALID_EL0_32		15

#include "uart1.h"

void handle_exc(uint64_t type, uint64_t esr, uint64_t elr, uint64_t spsr, uint64_t far){
  disable_irq();
  switch(type){
    case 0: uart1_puts("Synchronous"); break;
    case 1: uart1_puts("IRQ"); handle_irq(); enable_irq(); return; break;
    case 2: uart1_puts("FIQ"); break;
    case 3: uart1_puts("SError"); break;
  }



  uart1_puts(": ");

  switch(esr>>26) {
    case 0b000000: uart1_puts("Unknown"); break;
    case 0b000001: uart1_puts("Trapped WFI/WFE"); break;
    case 0b001110: uart1_puts("Illegal execution"); break;
    case 0b010101: uart1_puts("System call"); break;
    case 0b100000: uart1_puts("Instruction abort, lower EL"); break;
    case 0b100001: uart1_puts("Instruction abort, same EL"); break;
    case 0b100010: uart1_puts("Instruction alignment fault"); break;
    case 0b100100: uart1_puts("Data abort, lower EL"); break;
    case 0b100101: uart1_puts("Data abort, same EL"); break;
    case 0b100110: uart1_puts("Stack alignment fault"); break;
    case 0b101100: uart1_puts("Floating point"); break;
    default: uart1_puts("Unknown"); break;
  }

  if (esr>>26 == 0b100100 || esr>>26 == 0b100101){
    uart1_puts(", ");
    switch((esr>>2)&0x3){
      case 0: uart1_puts("Address size fault"); break;
      case 1: uart1_puts("Translation fault"); break;
      case 2: uart1_puts("Access flag fault"); break;
      case 3: uart1_puts("Permission fault"); break;
    }
    switch(esr&0x3){
      case 0: uart1_puts("at level 0"); break;
      case 1: uart1_puts("at level 2"); break;
      case 2: uart1_puts("at level 2"); break;
      case 3: uart1_puts("at level 3"); break;
    }
  }

  uart1_puts(":\n ESR_EL1 ");
  uart1_puth(esr>>32);
  uart1_puth(esr);
  uart1_puts(" ELR_EL1 ");
  uart1_puth(elr>>32);
  uart1_puth(elr);
  uart1_puts("\n SPSR_EL1 ");
  uart1_puth(spsr>>32);
  uart1_puth(spsr);
  uart1_puts(" FAR_EL1  ");
  uart1_puth(far>>32);
  uart1_puth(far);

  while(1);
}
