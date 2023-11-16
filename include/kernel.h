#ifndef KERNEL_H
# define KERNEL_H

void            kputchar(char c);
unsigned int    kprintf(char *str);
int	            kstrncmp(const char *s1, const char *s2, unsigned int n);
unsigned int    kstrlen(const char *s);
void	        *kmemset(void *s, int c, unsigned int n);
char            *kitoa(int n, char *dest);
void		outb(unsigned short port, unsigned char val);
unsigned char	inb(unsigned short port);



#endif
