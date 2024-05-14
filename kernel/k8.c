#include <stdint.h>
#include <stddef.h>

#include "mmio.h"
#include "gpio.h"
#include "uart1.h"
#include "mbox.h"
#include "mmu.h"
//#include "multicore.h"

#define KERNEL_UART1_IO        ((volatile unsigned int*)0xFFFFFFFFFFE00040)
#define KERNEL_UART1_LSR       ((volatile unsigned int*)0xFFFFFFFFFFE00054)

#define AUX_ENABLE      ((volatile unsigned int*)(MMIO_BASE+0x00215004))
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

void warn(){
	uart1_puts("Hi from core 2!");
}

void serprint(char *s){
	for(uint64_t i; s[i] != '\0'; i++){
		*KERNEL_UART1_IO = s[i];
	}
}

void k8main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3){
	char *kmsg = "done bitch\n";
	
	uart1_init();

	uart1_puts("rros alpha via k8\r\n");
	uart1_puts("[INFO] initializing mmu\n");
	
	mmu_init();
	
	serprint("hello\n");
	
	uart1_puts("[INFO] initialized mmu\n");
	
	serprint("hej\r\n");
	
	while(1){
		uart1_putc(uart1_getc());
	}
}
