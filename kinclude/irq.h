#ifndef IRQ_H
#define IRQ_H

extern void enable_irq();
extern void disable_irq();

extern void v_init();

void enable_ic(); 
void handle_irq();

#endif
