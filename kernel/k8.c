#include <stdint.h>
#include <stddef.h>

#include "mmio.h"
#include "gpio.h"
#include "uart1.h"
#include "mbox.h"
#include "multicore.h"

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


void cr1maim(){
	uart1_init();
	uart1_puts("rros alpha via k8\r\n");

	mbox[0] = 8*4;
	mbox[1] = MBOX_REQUEST;

	mbox[2] = MBOX_TAG_GETSERIAL;
	mbox[3] = 8;
	mbox[4] = 8;
	mbox[5] = 0;
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	if(mbox_call(MBOX_CH_PROP)){
		uart1_puts("[INFO] serial: ");
		uart1_puth(mbox[6]);
		uart1_puth(mbox[5]);
		uart1_putc('\n');
	}


	while(1){
		uart1_putc(uart1_getc());
	}
}

void k8main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3){
	init_core1();

	while(1){
		asm volatile("wfe");
	}
}
