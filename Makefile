RED := \033[0;31m
GREEN := \033[0;32m
NC := \033[0m

EXEC_FILE = kfs.elf

ISO_NAME = kfs.iso

ASM = nasm

ASM_FLAGS = -f elf32

CC = i386-elf-gcc

CC_FLAGS = 	-fno-builtin \
			-fno-exceptions \
			-fno-stack-protector \
			-fno-rtti \
			-nostdlib \
			-nodefaultlibs \
			-ffreestanding  \
			-m32 

OBJS := $(wildcard *.o)

all: $(ISO_NAME)

$(EXEC_FILE):
	@echo "$(GREEN)Compiling the elf file$(NC)"
	$(ASM) $(ASM_FLAGS) src/boot.s -o boot.o
	$(CC) $(CC_FLAGS) -I./include -g -c src/main.c -o main.o -ggdb
	ld -melf_i386 -T linker/linker.ld boot.o main.o

$(ISO_NAME): $(EXEC_FILE)
	@echo "$(GREEN)Building the ISO image$(NC)"
	mkdir -p iso/
	cp -R boot/ iso/
	cp kfs.elf iso/boot
	grub-mkrescue -o $(ISO_NAME) iso

run-iso: $(ISO_NAME)
	@echo "$(GREEN)Running the Kernel...$(NC)"
	qemu-system-i386 -cdrom $(ISO_NAME)

run-iso-debug: $(ISO_NAME)
	qemu-system-i386 -s -S -cdrom $(ISO_NAME)

clean:
	rm -f $(OBJS)
	rm -f $(EXEC_FILE)
	rm -rf iso
	rm -f $(ISO_NAME)

re: clean all