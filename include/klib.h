#ifndef KERNEL_H
# define KERNEL_H

# define uint8_t    unsigned char
# define uint16_t   unsigned short
# define uint32_t   unsigned int

# define int8_t     char
# define int16_t    short
# define int32_t    int

 #include "vga.h"

void            kputchar(char c, int color, int bright);
unsigned int    kprintf(char *str, int color, int bright);
int	            kstrncmp(const char *s1, const char *s2, unsigned int n);
unsigned int    kstrlen(const char *s);
void	        *kmemset(void *s, int c, unsigned int n);
char            *kitoa(int n, char *dest, char *base);
void	        *kmemcpy(void *dst, const void *src, unsigned int n);
void            print_stack_kernel(unsigned int max_frames);

int	main(void);

static inline void outb(unsigned short port, unsigned char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static inline void outw(uint16_t value, uint16_t port) {
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

struct stackframe {
	struct stackframe *ebp;
	unsigned long eip;
};

struct data {
	unsigned int addr;
	char *name;
};
typedef struct data data_t;

#endif
