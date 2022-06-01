#include "stdafx.h"
#include "exception_handlers.h"

EXCEPTION_DISPOSITION __declspec(naked) exception_handler_return_to_DR2(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext) 
{
	__asm {
                push    ebp
                mov     ebp, esp
                push    ebx
                push    eax
                push    ebx
                mov     eax, fs:0
                mov     ebx, [eax]
                mov     ebx, [ebx]
                mov     [eax], ebx
                pop     ebx
                pop     eax
                mov     eax, [ebp+16]
                pop     ebx
                mov     ecx, [eax+0x0C4]
                mov     edx, [ecx]
                add     ecx, 4
                mov     [eax+9Ch], edx  ; Context.Edi
                mov     edx, [ecx]
                mov     [eax+0x0A0], edx ; Context.Esi
                mov     ecx, [ecx+4]
                mov     [eax+0x0A4], ecx
                mov     ecx, [eax+0x0B4] ; Context.Ebp
                mov     edx, [ecx]
                add     ecx, 8
                mov     [eax+0x0C4], ecx ; Context.Esp
                mov     ecx, [eax+0x0C]  ; Context.Esp
                xor     ecx, 0x7FFFFFFF
                mov     [eax+0x0B4], edx
				mov     dword ptr [eax+0x18], 400h
                mov     [eax+0x0B8], ecx
                xor     eax, eax
                pop     ebp
                retn
	}
}


EXCEPTION_DISPOSITION __declspec(naked) return_handler_trampoline1(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext) 
{
	__asm {
                push    ebp             ; Jump to trampoline DR2
	}
	OutputDebugString(L"return_handler_trampoline1");
	__asm {
                mov     ebp, esp
                mov     eax, [ebp+0x10]
                push    ebx
                mov     ecx, [eax+0x0C4] ; CONTEXT.ESP
                mov     edx, [ecx]
                add     ecx, 4
                mov     [eax+0x9C], edx  ; CONTEXT.EDI = EDX = *CONTEXT.ESP = TOP OF STACK
                mov     edx, [ecx]
                mov     [eax+0x0A0], edx ; CONTEXT.ESI = EDX = *CONTEXT.ESP+4
                mov     ecx, [ecx+4]
                mov     [eax+0x0A4], ecx
                mov     ecx, [eax+0x0B4]
                mov     edx, [ecx]
                add     ecx, 4
                mov     [eax+0x0B4], edx ; CONTEXT.EBP = *CONTEXT.EBP
                mov     edx, [ecx]
                add     ecx, 4
                mov     [eax+0x0B8], edx ; CONTEXT.EIP = EDX = [CONTEXT.ESP+12]
                mov     [eax+0x0C4], ecx ; CONTEXT.ESP = [CONTEXT.ESP=12]
                mov     dword ptr [eax+0x18], 0x400 ; CONTEXT.DR7 = 400h (Disable HW breakpoints)
                push    eax
                push    ebx
                mov     eax, fs:0 ; Remove the SEH entry from the handler list
                mov     ebx, [eax]
                mov     ebx, [ebx]
                mov     [eax], ebx
                pop     ebx
                pop     eax
                xor     eax, eax
                pop     ebx
                pop     ebp
                retn
	}
}

EXCEPTION_DISPOSITION __cdecl return_handler_test_3(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext) 
{
	__asm {
		mov     eax, fs:0
        mov     ebx, [eax]
        mov     [eax], ebx
	}
	DWORD esp = ContextRecord->Esp;
	DWORD tmp1 = *(DWORD*)esp;
	DWORD tmp2 = *(DWORD*)(esp + 2);
	ContextRecord->Eip = tmp2;
	DWORD ebp  = *(DWORD*)ContextRecord->Ebp;
	ebp += 2; 
	ContextRecord->Esp = ebp;
	__asm {
		; Remove the SEH entry from the handler list
		push    eax
        push    ebx
        mov     eax, fs:0
        mov     ebx, [eax]
        mov     ebx, [ebx]
        mov     [eax], ebx
        pop     ebx
        pop     eax
        xor     eax, eax
	}
}

EXCEPTION_DISPOSITION __cdecl return_handler_to_trampoline_DR2(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext) 
{
	printf("return handler\n");
	OutputDebugString(L"return_handler_to_trampoline_DR2");
	__asm {
		mov     eax, fs:0
        mov     ebx, [eax]
        mov     ebx, [ebx]
        mov     [eax], ebx
        pop     ebx
        pop     eax
        mov     eax, ContextRecord
        pop     ebx
        mov     ecx, [eax+0C4h]			   ; ECX = Context.Esp
		mov     edx, [ecx]				   ; 
        add     ecx, 4					   ;  
		mov     [eax+9Ch], edx			   ; Context.Edi = *ESP
        mov     edx, [ecx]
        mov     [eax+0A0h], edx            ; Context.Esi + *(ESP+4)
        mov     ecx, [ecx+4]
        mov     [eax+0A4h], ecx			   ; Context.Ebx + *(ESP+8)
        mov     ecx, [eax+0B4h]			   ; Context.Ebp
        mov     edx, [ecx]				   ; Edx = *Ebp
        add     ecx, 8
        mov     [eax+0C4h], ecx			   ; Context.Esp = Ebp+12
        mov     ecx, [eax+0Ch]			   ; Context.Dr2
        xor     ecx, 7FFFFFFFh			   ; ECX = Context.Dr2 ^0x7FFFFFFF
        mov     [eax+0B4h], edx			   ; Context.Ebp = *(Context.Ebp)
        mov     dword ptr [eax+18h], 400h  ; Context.Dr7 = 0x400
        mov     [eax+0B8h], ecx			   ; Context.Eip = ECX ( Context.Dr2 ^0x7FFFFFFF )
		push    eax
        push    ebx
        mov     eax, fs:0 ; Remove the SEH entry from the handler list
        mov     ebx, [eax]
        mov     ebx, [ebx]
        mov     [eax], ebx
        pop     ebx
        pop     eax
        xor     eax, eax
	}
}

	 
EXCEPTION_DISPOSITION __cdecl return_handler_test(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext) 
{
	__asm {
		mov     eax, fs:0
        mov     ebx, [eax]
        mov     [eax], ebx
	}
	DWORD esp = ContextRecord->Esp;
	DWORD tmp1 = *(DWORD*)esp;
	ContextRecord->Edi = tmp1;	 
	DWORD ebp  = *(DWORD*)ContextRecord->Ebp;
	ebp += 2;
	ContextRecord->Esp = ebp;

	__asm {
		; Remove the SEH entry from the handler list
		push    eax
        push    ebx
        mov     eax, fs:0
        mov     ebx, [eax]
        mov     ebx, [ebx]
        mov     [eax], ebx
        pop     ebx
        pop     eax
        xor     eax, eax
	}
}

	 
__forceinline void do_return_handler() {
	__asm {
		mov		eax, fs:0
		mov		dword ptr [eax+4], offset return_handler_trampoline1
		pushf
		pop		eax
		or		eax, 0x100
		push	eax
		popf
	}
}