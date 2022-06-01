#pragma once
#include "stdafx.h"
#include <Windows.h>
/*
	Globals
*/
extern void *trampoline_0_pbuf;
extern unsigned long trampoline_0_esp_global;
extern void *pbuf_trampoline0;
extern void *pbuf_trampoline1;
extern unsigned long callstack[100];
extern unsigned long * sp_callstack;

extern CONTEXT fakeContext;
