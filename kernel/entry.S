.macro kernel_entry

stp x1, x2, [sp, #-16]!
stp x3, x4, [sp, #-16]!
stp x5, x6, [sp, #-16]!
stp x7, x8, [sp, #-16]!
stp x9, x10, [sp, #-16]!
stp x11, x12, [sp, #-16]!
stp x13, x14, [sp, #-16]!
stp x15, x16, [sp, #-16]!
stp x17, x18, [sp, #-16]!
stp x0, x19, [sp, #-16]!

.endm

.macro kernel_exit

ldp x0, x19, [sp], #16
ldp x17, x18, [sp], #16
ldp x15, x16, [sp], #16
ldp x13, x14, [sp], #16
ldp x11, x12, [sp], #16
ldp x9, x10, [sp], #16
ldp x7, x8, [sp], #16
ldp x5, x6, [sp], #16
ldp x3, x4, [sp], #16
ldp x1, x2, [sp], #16

.endm
