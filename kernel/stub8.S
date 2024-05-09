// k8 stub

// put this at the front
.section ".text.boot"

// k8 entry point

.global _start

_start:
        // set stack
        ldr x5, =_start
        mov sp, x5

        // clear bss
        ldr x5, =__bss_start
        ldr w6, =__bss_size

1:      cbz w6, 2f
        str xzr, [x5], #8
        sub w6, w6, #1
        cbnz w6, 1b

2:      bl k8main

3:
        wfe
        b 3b
