#pragma once
#include <windows.h>

extern void trampoline1();
extern void trampoline0(void *trampolineB);
extern void test_trampoline();
extern void test_trampoline2();
extern __forceinline void _memcpy(void *buf_dst, void *buf_src, int buf_len); 
