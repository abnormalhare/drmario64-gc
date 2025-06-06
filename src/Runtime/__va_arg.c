#include "Runtime/__va_arg.h"

#undef __va_arg

/* 80361B14-80361BDC 35C454 00C8+00 0/0 3/3 0/0 .text            __va_arg */
void* __va_arg(va_list* v_list, unsigned char type) {
	char* addr;
	char* reg      = &v_list[0]->gpr;
	s32 g_reg      = v_list[0]->gpr;
	s32 maxsize    = 8;
	s32 size       = 4;
	s32 increment  = 1;
	s32 even       = 0;
	s32 fpr_offset = 0;
	s32 regsize    = 4;

    if (type == 4) {
        size = 16;
		addr                    = v_list[0]->input_arg_area;
		addr                    = (char*)(((u32)(addr) + ((size)-1)) & ~((size)-1));
		v_list[0]->input_arg_area = addr + size;
        return addr;
    }
	if (type == 3) {
		reg        = &(v_list[0]->fpr);
		g_reg      = v_list[0]->fpr;
		size       = 8;
		fpr_offset = 32;
		regsize    = 8;
	}
	if (type == 2) {
		size = 8;
		maxsize--;
		if (g_reg & 1)
			even = 1;
		increment = 2;
	}
	if (g_reg < maxsize) {
		g_reg += even;
		addr = v_list[0]->reg_save_area + fpr_offset + (g_reg * regsize);
		*reg = g_reg + increment;
	} else {
		*reg                    = 8;
		addr                    = v_list[0]->input_arg_area;
		addr                    = (char*)(((u32)(addr) + ((size)-1)) & ~((size)-1));
		v_list[0]->input_arg_area = addr + size;
	}
	if (type == 0)
		addr = *((char**)addr);

	return addr;
}
