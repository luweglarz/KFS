#ifndef KERNEL_H
# define KERNEL_H

# define uint8_t    unsigned char
# define uint16_t   unsigned short
# define uint32_t   unsigned int

# define int8_t     char
# define int16_t    short
# define int32_t    int

void            kputchar(char c, int color, int bright);
unsigned int kprintf(char *str, int color, int bright);
int	            kstrncmp(const char *s1, const char *s2, unsigned int n);
unsigned int    kstrlen(const char *s);
void	        *kmemset(void *s, int c, unsigned int n);
char            *kitoa(int n, char *dest);

static inline void outb(unsigned short port, unsigned char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
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

#endif