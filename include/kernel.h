#ifndef KERNEL_H
# define KERNEL_H

# define uint8_t    unsigned char
# define uint16_t   unsigned short
# define uint32_t   unsigned int

# define int8_t     char
# define int16_t    short
# define int32_t    int

void            kputchar(char c);
unsigned int    kprintf(char *str);
int	            kstrncmp(const char *s1, const char *s2, unsigned int n);
unsigned int    kstrlen(const char *s);
void	        *kmemset(void *s, int c, unsigned int n);
char            *kitoa(int n, char *dest);



#endif
