#pragma once

#include "stdafx.h"
#include <Windows.h>

EXCEPTION_DISPOSITION __cdecl exception_handler_return_to_DR2(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext);
	 
EXCEPTION_DISPOSITION __cdecl return_handler_to_trampoline_DR2(struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext);

EXCEPTION_DISPOSITION return_handler_trampoline1(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext);

EXCEPTION_DISPOSITION __cdecl return_handler_test_3(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext);

/*
	Use by function (f*) to perform a function call return.
	A function registers this function as its exception handler, then it
	triggers a single-step exception.

	- Context.Edi = *sp
	- Context.Esi = *(sp+1)
	- Context.Ebx = *(sp+2)
	- Context.Eip = Context.Dr2 (The EIP address where handler jumps to)
		
		
	to trampoline0:trampoline0_return_address_2 on a random buffer address.

*/
EXCEPTION_DISPOSITION __cdecl return_handler_to_trampoline_DR2(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext);

EXCEPTION_DISPOSITION __cdecl return_handler_test(
	 struct _EXCEPTION_RECORD *ExceptionRecord,
     void * EstablisherFrame,
     struct _CONTEXT *ContextRecord,
     void * DispatcherContext);
 
extern __forceinline void do_return_handler();
