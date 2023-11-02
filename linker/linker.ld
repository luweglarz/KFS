OUTPUT_FORMAT(elf32-i386)
OUTPUT(kfs.elf)
ENTRY(start_kernel)

SECTIONS {
    . = 0x00100000; 

    .multiboot_header ALIGN (0x1000) :
    {

    }

    .text ALIGN (0x1000) :
    {
        *(.text)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss ALIGN (0x1000) :
    {
        *(.bss)
    }
}