// salwrap.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#include "globals.h"
#include "context.h"
#include "trampoline.h"
#include "constants.h"
#include "setup.h"
#include "functions.h"

using namespace std;


//void trampoline1(void *dest, void *source, int length);
void trampoline1();
int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{
	printf("code: %x\n", code);
    return EXCEPTION_EXECUTE_HANDLER;
}


 
unsigned long GetAddress(CONTEXT *context, void * addr) {
	return (unsigned long)(addr) - (unsigned long)(&context);
}

void PrintOffsets(CONTEXT *context) {
	// 0xC8
	printf("&context.Dr0: %p\n", GetAddress(context, &context->Dr0));
	// 0xB8
	printf("&context.Ebp: %p\n", GetAddress(context, &context->Ebp));
	// 0xBC
	printf("&context.Eip: %p\n", GetAddress(context, &context->Eip));
	// 0x
	printf("&context.Esp: %p\n", GetAddress(context, &context->Esp));
}

int _tmain(int argc, _TCHAR* argv[])
{
	start_trampolines();
	//setup_free();
	getchar();
	return 0;
}


void test1() {
	_try {
		printf("trampoline1\n");
		OutputDebugString(L"trampoline1");
		__asm {
 
		}

	} _except(EXCEPTION_EXECUTE_HANDLER){
		printf("trampoline1 default exception handler\n");
	}
}
