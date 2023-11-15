#ifndef ISR_H
# define ISR_H

typedef struct registers
{
   unsigned long ds; 
   unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax; 
   unsigned long int_no, err_code;   
   unsigned long eip, cs, eflags, useresp, ss;
} registers_t;

#endif
