x86_64-elf		= ${HOME}/cross/bin/x86_64-elf
as				= $(x86_64-elf)-as
g++				= $(x86_64-elf)-g++
ld				= $(x86_64-elf)-ld

output_file		= xernel-64.elf

cpp_flags		= \
	-ffreestanding \
	-fmodules-ts \
	-fno-exceptions \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fno-rtti \
	-fPIE \
	-g \
	-Iinclude \
	-Iinclude/stl \
	-m64 \
	-march=x86-64 \
	-mabi=sysv \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-MMD \
	-MP \
	-std=c++20 \
	-Wall \
	-Wextra

ld_flags		= \
	-g \
	-nostdlib \
	-pie \
	-static \
	--no-dynamic-linker \
	-z text \
	-z max-page-size=0x1000 \
	-T src/linker.ld \

cpp_files		:= $(shell find -L . -type f -name '*.cpp')
asm_files		:= $(shell find -L . -type f -name '*.asm')
objects			:= $(cpp_files:.cpp=.cpp.o) $(asm_files:.asm=.asm.o)
headers			:= $(cpp_files:.cpp=.cpp.d) $(asm_files:.asm=.asm.d)


.PHONY: all 
all: $(output_file)

$(output_file): $(objects)
	$(ld) $(objects) $(ld_flags) -o $@

-include $(headers)

%.cpp.o: %.cpp
	$(g++) $(cpp_flags) -c $< -o $@

%.asm.o: %.asm
	$(as) $< -o $@

.PHONY: clean
clean:
	rm -fr $(output_file) $(objects) $(headers) iso_root/ xernel.iso
	
.PHONY: install-limine
install-limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1
	make -C limine

.PHONY: iso
iso: $(output_file)

	mkdir -p iso_root
	cp -v $(output_file) \
		src/limine.cfg \
		limine/limine-bios.sys \
		limine/limine-bios-cd.bin \
		limine/limine-uefi-cd.bin \
		iso_root/

	mkdir -p iso_root/EFI/BOOT
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/

	xorriso -as mkisofs -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o xernel.iso

	./limine/limine bios-install xernel.iso

.PHONY: run
run: iso
	qemu-system-x86_64 xernel.iso