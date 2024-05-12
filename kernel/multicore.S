.section ".text"

#define RPI_CORE1 0xE0

.globl core1_stub
.globl wakeup_core

wakeup_core:
        mov x2, 0xd8
        ldr x1, =core1_stub
        str x1, [x2, x0, LSL #3]
        sev
        ret

core1_stub:
        ldr x1, =_start
        sub x1, x1, #1024      
        mov sp, x1

        bl cr1maim
        ret
