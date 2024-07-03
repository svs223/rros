TARGET8 := aarch64
TARGET := aarch64-unknown-elf
KLDFLAGS := -no-pie -target $(TARGET) -ffreestanding -nostdlib -nostartfiles -T kernel/link.ld -v -Ikinclude
KCFLAGS := -target $(TARGET) -mgeneral-regs-only -ffreestanding -nostdlib -mstrict-align -Ikinclude
KASFLAGS := -target $(TARGET) -ffreestanding

BUILDDIR := obj
KSRCDIR := kernel

CFILES := $(wildcard $(KSRCDIR)/*.c)
HFILES := $(wildcard $(KSRCDIR)/*.h)
SFILES := $(wildcard $(KSRCDIR)/*.S)
OFILES := $(CFILES:$(KSRCDIR)/%.c=$(BUILDDIR)/%_c.o)
OFILES += $(SFILES:$(KSRCDIR)/%.S=$(BUILDDIR)/%_S.o)

kernel8.img: $(BUILDDIR)/k8.elf disas.txt
	llvm-objcopy -O binary $< kernel8.img

disas.txt: $(BUILDDIR)/k8.elf
	llvm-objdump -d $(BUILDDIR)/k8.elf > disas.txt

$(BUILDDIR)/k8.elf: $(OFILES) obj/font.psf.o
	clang $(KLDFLAGS) -o $@ $^

$(BUILDDIR)/%_c.o: $(KSRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	clang $(KCFLAGS) $^ -c -o $@

$(BUILDDIR)/%_S.o: $(KSRCDIR)/%.S
	mkdir -p $(BUILDDIR)
	clang $(KASFLAGS) $^ -c -o $@

obj/font.psf.o: kernel/font.psf
	mkdir -p obj
	ld.lld -m aarch64elf -r -b binary -o $@ $^
	
clean:
	rm -f *.o *.elf *.img disas.txt
	rm -rf obj

run: kernel8.img
	qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel $<

debug: kernel8.img disas.txt
	qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel $< -d int
