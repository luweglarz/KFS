#include "vga.h"
#include "kscreen.h"
#include "keyboard.h"

extern void print_stack_kernel(unsigned int MaxFrames);
extern void start_kernel(void);

data_t fdata[] = {
	[0].addr = (unsigned int)&main,
	[0].name = "main",
	[1].addr = (unsigned int)&start_kernel,
	[1].name = "start_kernel"
};



void kputchar(char c, int color, int bright){
	if (vga_area_head == (uint16_t*)(VGA_AREA + (VGA_WIDTH * VGA_HEIGHT)))
		return ;
	*vga_area_head = VGA_ASCII(color, bright, c);
	move_cursor(ARROW_RIGHT);
}

unsigned int kprintf(char *str, int color, int bright){
	int cnt = 0;

	while (*str != '\0'){
		if (*str == '\n'){
			vga_area_head = (uint16_t*)VGA_JMP_LINE;
			str++;
			continue ;
		}
		kputchar(*str, color, bright);
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

void	*kmemcpy(void *dst, const void *src, unsigned int n) {
	unsigned int i;

	i = 0;
	if(src && dst)
	{
		while (i < n) {
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return dst;
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

int right_function_name(unsigned int raddr, data_t *data, int len)
{
	unsigned int mem = 0;
	int ret = 0;
	for (int i = 0; i < len; i++)
	{
		if (data[i].addr > mem && data[i].addr < raddr)
		{
			mem = data[i].addr;	
			ret = i;
		}
	}
	if (raddr - mem >= 45)
		ret = -1;
	return ret;
}

void names_resolver(unsigned int return_addr)
{
	int ret = 0;
	ret = right_function_name(return_addr, fdata, 2);

	if(ret != -1)
		kprintf(fdata[ret].name, LIGHT_GRAY_COLOR, 1);
	else
		kprintf("?????", LIGHT_GRAY_COLOR, 1);
}

void print_stack_kernel(unsigned int MaxFrames)
{
	struct stackframe *stk;
	char buff[255];
	MaxFrames = 10;
	asm volatile ("movl %%ebp,%0" : "=r"(stk) ::); // put ebp in stk struct
	kprintf("Stack trace. \n", LIGHT_GRAY_COLOR, 1);
	for(unsigned int frame = 0; stk && frame < MaxFrames; ++frame)
	{
		kprintf(kitoa(stk->eip, buff), LIGHT_GRAY_COLOR, 1);
		kprintf(" : ", LIGHT_GRAY_COLOR, 1);
		names_resolver(stk->eip);
		kprintf("\n", LIGHT_GRAY_COLOR, 1);
		stk = stk->ebp;
	}
}
