#include <stdint.h>
#include <stddef.h>

#include "mmio.h"
#include "gpio.h"
#include "uart1.h"
#include "mbox.h"
#include "delay.h"
#include "lfb.h"
//#include "multicore.h"

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


void k8main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3){
	uart1_init();
	uart1_puts("rros alpha via k8\r\n");
	uart1_puts("[INFO] attempting to initialize FB\n");

	lfb_print(80, 80, "rros booting via k8");
	uart1_puts("Uwaa");
	
	while(1){
		uart1_putc(uart1_getc());
	}
}
