#include "vga.h"

void kputchar(char c){
    if (vga_area_head == (unsigned short*)(VGA_AREA + (VGA_WIDTH * VGA_HEIGHT)))
        return ;
    *vga_area_head = VGA_ASCII(BLUE_COLOUR, 0, c);
    vga_area_head++;
 }

unsigned int kprintf(char *str){
    int cnt = 0;

    while (*str != '\0'){
        if (*str == '\n'){
            vga_area_head = (unsigned short*)VGA_JMP_LINE;
            str++;
            continue ;
        }
        kputchar(*str);
        str++;
        cnt++;
    }
    return (cnt);
 }

int	kstrncmp(const char *s1, const char *s2, unsigned int n){
	unsigned int i = 0;

	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

unsigned int kstrlen(const char *s){
	unsigned int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

void	*kmemset(void *s, int c, unsigned int n){
	unsigned char	*ptr = (unsigned char *)s;
	unsigned int	i = 0;

	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

static int	number_size(int nb)
{
	int	size;

	size = 0;
	if (nb <= 0)
	{
		size++;
		if (nb < 0)
			nb = nb * -1;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char *kitoa(int n, char *dest){
	unsigned int size = number_size(n);
    char         *ret_addr = dest;
    char         *itr_addr = dest;

    itr_addr[size--] = '\0';
	if (n == 0)
		itr_addr[0] = '0';
	if (n < 0)
	{
		itr_addr[0] = '-';
		n = n * -1;
	}
	while (n != 0)
	{
		itr_addr[size] = (n % 10) + '0';
		n = n / 10;
		itr_addr--;
	}
	return (ret_addr);
}

void outb(unsigned short port, unsigned char val)
{
	kprintf("bien\n");
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

unsigned char inb(unsigned short port)
{
    unsigned char ret;
    kprintf("ok\n");
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}
