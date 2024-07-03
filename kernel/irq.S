.global enable_irq
.global disable_irq
.global nhandle_irq

nhandle_irq:
//        ldr x0, =irqmsg
  //      bl uart1_puts

        mov x0, 0
        mov x1, 0
        mov x2, 0
        mov x3, 0
        mov x4, 0
        mov x5, 0
        mov x6, 0
        mov x7, 0
        mov x8, 0
        
        b handle_irq
        eret        


enable_irq:
        msr daifclr, #2
        ret
        
disable_irq:
        msr daifset, #2
        ret        

.section ".rodata"

irqmsg:
        .ascii "IRQ Found...\0"
