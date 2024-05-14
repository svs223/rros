// k8 stub

// put this at the front
.section ".text.boot"

// k8 entry point

.global _start

_start:
        mrs x0, mpidr_el1
        and x0, x0, #0xff
        cbnz x0, 4f

        ldr x5, =_start

        mrs x1, CurrentEL
        cmp x1, 0b1000
        beq el2
        blo el1
        
el3:
        

el2:
        // enable generic timer
        msr sp_el1, x2
        mrs x0, cnthctl_el2
        orr x0, x0, #3
        msr cnthctl_el2, x0
        msr cntvoff_el2, xzr

        // enable aarch64
        mov x0, #(1 << 31)
        orr x0, x0, #(1 << 1)
        msr hcr_el2, x0
        mrs x0, hcr_el2

        mov     x2, #0x0800
        movk    x2, #0x30d0, lsl #16
        msr     sctlr_el1, x2

        //change execution level to el1
        mov x2, #0x3c4
        msr spsr_el2, x2
        adr x2, 0f
        msr elr_el2, x2
        eret
el1:
        
0:        
        // set stack
        mov sp, x5

        // clear bss
        ldr x5, =__bss_start
        ldr w6, =__bss_size

1:      cbz w6, 2f
        str xzr, [x5], #8
        sub w6, w6, #1
        cbnz w6, 1b

        
2:      bl k8main

4:
        wfe
        b 4b
        
