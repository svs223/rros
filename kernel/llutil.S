.global kput32
.global kget32
.global kget64
.global kput64
.global hang

kput32:
        str w1, [x0]
        ret

kput64:
        str x1, [x0]
        ret

kget32:
        ldr w0, [x0]
        ret

kget64:
        ldr x0, [x0]
        ret

hang:
        wfe
        b hang
        ret   
