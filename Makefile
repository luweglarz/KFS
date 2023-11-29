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
			-m32 \
			-fno-omit-frame-pointer

SRCS := $(wildcard ./src/*.c)

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CC_FLAGS) -I./include -g -c $< -o $@ -ggdb

all: $(ISO_NAME)

$(EXEC_FILE): $(OBJS)
	@echo "$(GREEN)Compiling the elf file$(NC)"
	$(ASM) $(ASM_FLAGS) -g src/boot.s -o src/boot.o
	i386-elf-ld -melf_i386 -T linker/linker.ld src/boot.o $(OBJS) -g

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
	rm -f $(OBJS) src/boot.o
	rm -f $(EXEC_FILE)
	rm -rf iso
	rm -f $(ISO_NAME)

re: clean all
