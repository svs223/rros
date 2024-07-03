#include <stdint.h>
#include <stddef.h>

#include "mmio.h"
#include "gpio.h"
#include "uart1.h"
#include "mbox.h"
#include "mmu.h"
#include "irq.h"
#include "timer.h"

#define KERNEL_UART1_IO        ((volatile unsigned int*)0xFFFFFFFFFFE00040)
#define KERNEL_UART1_LSR       ((volatile unsigned int*)0xFFFFFFFFFFE00054)

void serprint(char *s){

	while(*s){		
		do{asm volatile("nop");}while(*KERNEL_UART1_LSR&0x20);
		*KERNEL_UART1_IO = *s++;
	}
}

void k8main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3){	
	uart1_init();
	v_init();
	timer_init();
	enable_ic();
	enable_irq();	

	uart1_puts("RROS Alpha via k8\r\n");

	while(1){
		uart1_putc(uart1_getc());
	}
}
