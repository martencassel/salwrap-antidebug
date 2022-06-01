#include "stdafx.h"
#include "utils.h"
#include "constants.h"
#include "globals.h"
#include "setup.h"
#include <Windows.h>
#include "context.h"
#include "trampoline.h"
#include "exception_handlers.h"

void func15() {
	OutputDebugString(L"start of func15.");
	unsigned long temp1, temp2;
	CONTEXT context;
	_try {
		GetContext(&context);
		GetContext(&context);
		SetContext(&context);
		DisableDebug(&context);
		__asm {
  		    mov     ecx, fs:0
  		    mov     dword ptr [ecx+4], offset exception_handler_return_to_DR2
			pushf
			pop		eax
			or		eax, 0x100
			push	eax
			popf
		}

	} _except(EXCEPTION_EXECUTE_HANDLER){
		printf("trampoline1 default exception handler\n");
	}
	OutputDebugString(L"end of func15.");
}

void func1() {
	OutputDebugString(L"start of func1.");

	unsigned long temp1, temp2;
	CONTEXT context;
	_try {
		GetContext(&context); 
		__asm {
			mov		ecx, context.Dr3
			push	offset func15
			xor		ecx, XOR_KEY
			call    ecx
			add		esp, 4
		}
		__asm {
  		    mov     ecx, fs:0
  		    mov     dword ptr [ecx+4], offset exception_handler_return_to_DR2
			pushf
			pop		eax
			or		eax, 0x100
			push	eax
			popf
		}
	} _except(EXCEPTION_EXECUTE_HANDLER){
		printf("trampoline1 default exception handler\n");
	}
	OutputDebugString(L"end of func1.");
}

void start_trampolines() {
	OutputDebugString(L"start_trampolines.");
	CONTEXT context;
	GetContext(&context);
	//setup_buffers();
	pbuf_trampoline0 = malloc(8192);
	_memcpy(pbuf_trampoline0, trampoline0, 2000);
	context.Dr3 = (unsigned long)pbuf_trampoline0 ^ XOR_KEY;

	SetContext(&context);
	GetContext(&context);
	context.Dr0 = 0;
	context.Dr1 = 1;
	context.Dr2 = 0;
	SetContext(&context);
	DisableDebug(&context);
	__asm {
		mov		ecx, context.Dr3
		push	offset func1
		xor     ecx, XOR_KEY
		call	ecx
		add		esp, 4
	}
	GetContext(&context);
	GetContext(&context);

	free(pbuf_trampoline0);

	OutputDebugString(L"end of start_trampolines.");
}