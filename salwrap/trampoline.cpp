#include "stdafx.h"
#include <Windows.h>
#include "exception_handlers.h"
#include "constants.h"
#include "globals.h"
#include "context.h"
#include "utils.h"

void trampoline1();

extern void *pbuf_trampoline0;
extern void *pbuf_trampoline1;
extern unsigned long *sp_callstack;
extern unsigned long trampoline_0_esp_global;

#define DEBUG 1


/*
	1. Push address of function pointer argument to call stack
	2. Call trampoline1 
		2.1 Copy trampoline1 to buffer
		2.2 Calculate return address in trampoline0 
		2.3 Return using exception handler
	3.1

	Note: Position independant code (printf etc does not work)
*/
void trampoline0(void *trampoline_fn) {
	void * pbuf_random_trampoline0;
	OutputDebugString(L"trampoline0");
	CONTEXT context;	 
	// Push function address to callstack
	OutputDebugString(L"Push to callstack");
	sp_callstack += 2;
	*sp_callstack = (unsigned long)trampoline_fn;
	*(sp_callstack+1) = 0x5f0;
	GetContext(&context);

	OutputDebugString(L"Copy trampoline0 buffer to new offset");
	unsigned long ptr_trampoline0_dt3 = context.Dr3 ^ XOR_KEY;
	pbuf_random_trampoline0 = (void*)((unsigned long)pbuf_trampoline0+2002);
	_memcpy((void*)pbuf_random_trampoline0, (void*)ptr_trampoline0_dt3, 2000);
//	unsigned long return_address_1 = 0; 
//	__asm {
//		lea		eax, ret_address_1
//		mov     return_address_1, eax
//	}
//	printf("Calling trampoline1\n");
//	OutputDebugString(L"Calling trampoline1");
//	__asm {		 
//		push    return_address_1
//		mov     eax, offset trampoline1
//		jmp		eax
//	}
//ret_address_1:
//	// Remove stack frame of trampoline1 
//	__asm {
//		add		esp, 4
//	}
//	OutputDebugString(L"After return trampoline1 via exception handler");
	void * return_address_2;
	__asm {
		lea		eax, ret_address_2
		mov     return_address_2, eax
	}
	OutputDebugString(L"Calculate return address in next trampoline0 buffer.");
	unsigned long rel_address_2_offset = (unsigned long)return_address_2 - (unsigned long)trampoline0;
	unsigned long va_return_address_2  = (unsigned long)pbuf_random_trampoline0 + rel_address_2_offset; 
	GetContext(&context);
	context.Dr2 = (unsigned long)va_return_address_2 ^ XOR_KEY; 
	context.Dr3 = (unsigned long)pbuf_random_trampoline0 ^ XOR_KEY;
	context.Dr6 = 0;
	SetContext(&context);
	DisableDebug(&context); 

	OutputDebugString(L"Jump to trampoline_fn.");
	__asm {
		sub		esp, trampoline_0_esp_global
		push	eax
		mov		eax, trampoline_fn
		jmp		eax
	}
ret_address_2:
	__asm {
		add		esp, trampoline_0_esp_global
	}
	OutputDebugString(L"Return from trampoline_fn.");
	OutputDebugString(L"Pop callstack.");
	sp_callstack = sp_callstack - 2;
	if(sp_callstack == callstack) {
		return;
	}
	/*unsigned long temp3, temp4;
	temp3 = *sp_callstack;
	temp4 = *(sp_callstack+1);
	_memcpy(pbuf_trampoline0, (void*)temp3, temp4);*/
	return;
}

void trampoline1() {					
	_try {
		OutputDebugString(L"trampoline1");
		//_memcpy(dest, source, length);
		do_return_handler();
	} _except(EXCEPTION_EXECUTE_HANDLER){
	}
}
 	 

__forceinline void VirtualProtectWrap(LPVOID *address, SIZE_T dwSize, PDWORD lpOldProtect) {
	VirtualProtect(address, dwSize, (DWORD)4, lpOldProtect);
}

void test_trampoline3() {
	_try {
		__asm {
			  mov     eax, fs:0       ; Register exception handler
			  mov     dword ptr [eax+4], offset return_handler_test_3
			  pushf
			  pop     eax
			  or      eax, 0x100
			  push    eax
			  popf
		}
	} _except(EXCEPTION_EXECUTE_HANDLER) {
		printf("test trampoline default exception handler\n");
	}
}

void test_trampoline2() {
	unsigned long temp1, temp2;
	__asm {
		lea		eax, return_address_1
		mov     temp1, eax
		lea     ebx, test_trampoline3
		mov     temp2, ebx
	}
	__asm {
		push    temp1
		jmp		ebx
		add     esp, 4
	}
	printf("%p %p\n", temp1, temp2);
return_address_1:
	printf("hello from return_address_1\n");
}
	



