#include "stdafx.h"
#include <Windows.h>
#include "constants.h"

void *trampoline_0_pbuf;
void *pbuf_trampoline0;
void *pbuf_trampoline1;
unsigned long trampoline_0_esp_global;
unsigned long callstack[100];
unsigned long * sp_callstack = callstack;
 
#ifdef DEBUG
CONTEXT fakeContext;
#endif