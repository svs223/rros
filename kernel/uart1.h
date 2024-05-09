#ifndef UART1_H
#define UART1_H

#include <stdint.h>

void uart1_init();
void uart1_putc(uint32_t);
void uart1_puts(char*);
char uart1_getc();
void uart1_puth(uint32_t);

#endif
