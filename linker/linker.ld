OUTPUT_FORMAT(elf32-i386)
OUTPUT(kfs.elf)
ENTRY(start_kernel)

SECTIONS {
    . = 0x00100000; 

    .text ALIGN (0x1000) :
    {
        *(.multiboot_header)
        *(.text)
    }
}