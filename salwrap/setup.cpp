#include "stdafx.h"
#include <Windows.h>
#include <time.h>
#include "constants.h"
#include "trampoline.h"
#include "globals.h"
#include "context.h"
int setup_buffers	() {
	printf("start_buffers()\n");
	CONTEXT context;
	srand(time(0));
	int rand_ = (rand() & 0xFFFF) + 16;
	trampoline_0_esp_global = 200;
	trampoline_0_pbuf = malloc(1520);

	pbuf_trampoline0 = malloc(8192);
	pbuf_trampoline1 = malloc(8192);
	_memcpy(pbuf_trampoline0, trampoline0, 1024);
//	context.Dr3 = (unsigned long)pbuf_trampoline0 ^ XOR_KEY;
	context.Dr3 = (unsigned long)trampoline0 ^ XOR_KEY;
	SetContext(&context);
	GetContext(&context);
	SetContext(&context, 0, 1, 0, ENABLE_DEBUG);
	DisableDebug(&context);
	GetContext(&context);
	GetContext(&context);
	return 0;
}

void setup_free() {
	free(pbuf_trampoline0);
	free(pbuf_trampoline1);
	free(trampoline_0_pbuf);
}
