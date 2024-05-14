TARGET8 := aarch64
TARGET := aarch64-unknown-elf
KLDFLAGS := -no-pie -target $(TARGET) -ffreestanding -nostdlib -T kernel/link.ld -v
KCFLAGS := -target $(TARGET) -ffreestanding -nostdlib
KASFLAGS := -target $(TARGET) -ffreestanding

kernel8.img: k8.elf
	llvm-objcopy -O binary $< kernel8.img

k8.elf: obj/k8.o obj/stub8.o obj/uart1.o obj/mbox.o obj/delay.o obj/lfb.o obj/font.psf.o obj/mmu.o
	clang $(KLDFLAGS) -o $@ $^

obj/k8.o: kernel/k8.c
	mkdir -p obj
	clang $(KCFLAGS) $^ -c -o $@

obj/mmu.o: kernel/mmu.c
	mkdir -p obj
	clang $(KCFLAGS) $^ -c -o $@

obj/multicore.o: kernel/multicore.S
	mkdir -p obj
	clang $(KASFLAGS) $^ -c -o $@

obj/mbox.o: kernel/mbox.c
	mkdir -p obj
	clang $(KCFLAGS) $^ -c -o $@ 
	
obj/lfb.o: kernel/lfb.c
	mkdir -p obj
	clang $(KCFLAGS) $^ -c -o $@

obj/uart1.o: kernel/uart1.c
	mkdir -p obj
	clang $(KCFLAGS) $^ -c -o $@

obj/stub8.o: kernel/stub8.S
	mkdir -p obj
	clang $(KASFLAGS) $^ -c -o $@

obj/delay.o: kernel/delay.c
	mkdir -p obj
	clang $(KCFLAGS) $^ -c -o $@

#obj/mmio.o: kernel/mmio.c
#	mkdir -p obj
	#clang $(KCFLAGS) kernel/mmio.c -c -o obj/mmio.o

obj/font.psf.o: kernel/font.psf
	mkdir -p obj
	ld.lld -m aarch64elf -r -b binary -o $@ $^
	
clean:
	rm -f *.o *.elf *.img
	rm -rf obj
