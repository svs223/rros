.section ".text"

#define RPI_CORE1 0xE0

.global init_core1

core_stub:
        b cr1maim
        ret

init_core1:
        ldr x1, =core_stub
        ldr x2, #RPI_CORE1
        str x1, [x2]
        ret
