#include "stdafx.h"

__forceinline unsigned long GetOffset1() {
	unsigned long temp, output;
	__asm {
		rdtsc
		mov     temp, eax
		mov     eax, temp
		lea     ecx, [eax+eax*2]
		lea     edx, [eax+ecx*4]
		shl     edx, 4
		add     edx, eax
		shl     edx, 8
		sub     edx, eax
		lea     esi, [eax+edx*4+269EC3h]
		shr     esi, 10h
		and     esi, 7FFFh
		mov     output, esi
	}
	return output;
}

__forceinline unsigned long GetOffset2() {
	unsigned long temp, output;
	__asm {
		rdtsc
		mov     temp, eax
		mov     eax, temp
		imul    eax, 343FDh
		add     eax, 269EC3h
		shr     eax, 10h
		and     eax, 7FFFh
		mov     temp, eax
		mov     eax, temp
		xor     edx, edx
		mov     ecx, 7FFFh
		div     ecx
		mov     ecx, eax
		imul    ecx, 7FFFh
		mov     eax, temp
		xor     edx, edx
		mov     esi, 7FFFh
		div     esi
		imul    eax, 7AC1h
		add     ecx, eax
		mov     eax, temp
		xor     edx, edx
		mov     esi, 7FFFh
		div     esi
		add     ecx, edx
		mov     eax, temp
		xor     edx, edx
		mov     esi, 7FFFh
		div     esi
		mov     eax, edx
		imul    eax, 7AC1h
		xor     edx, edx
		mov     esi, 7FFFh
		div     esi
		add     ecx, eax
		and     ecx, 0FFFFFFF0h
		mov     output, ecx
	}
	return output;
}

__forceinline unsigned long GetOffset3() {
	unsigned long temp, output;
	__asm {
        rdtsc
        mov     temp, eax
        mov     eax, temp
        mov     esi, 7FFFh
        lea     ecx, [eax+eax*2]
        lea     edx, [eax+ecx*4]
        shl     edx, 4
        add     edx, eax
        shl     edx, 8
        sub     edx, eax
        lea     ecx, [eax+edx*4+269EC3h]
        xor     edx, edx
        shr     ecx, 10h
        and     ecx, 7FFFh
        mov     eax, ecx
        div     esi
        mov     eax, 20005h
        mov     esi, edx
        mul     ecx
        sub     ecx, edx
        shr     ecx, 1
        add     ecx, edx
        shr     ecx, 0Eh
        lea     eax, [ecx+ecx*4]
        lea     eax, [ecx+eax*4]
        shl     eax, 3
        sub     eax, ecx
        lea     edx, [eax+eax*2]
        lea     eax, [esi+esi*2]
        shl     eax, 4
        add     eax, esi
        lea     edi, [ecx+edx*2]
        shl     edi, 6
        lea     eax, [eax+eax*4]
        lea     ecx, [esi+eax*2]
        mov     eax, 20005h
        shl     ecx, 6
        add     ecx, esi
        add     esi, edi
        mul     ecx
        sub     ecx, edx
        shr     ecx, 1
        add     ecx, edx
		mov     output, ecx
	}
	return output;
}

__forceinline unsigned long GetOffset4() {
	unsigned long temp, output;
	__asm {
        rdtsc
        mov     temp, eax
        mov     ecx, temp
        imul    ecx, 343FDh
        add     ecx, 269EC3h
        shr     ecx, 10h
        and     ecx, 7FFFh
        mov     temp, ecx
        mov     eax, temp
        xor     edx, edx
        mov     ecx, 7FFFh
        div     ecx
        mov     ecx, eax
        imul    ecx, 7FFFh
        mov     eax, temp
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        imul    eax, 7AC1h
        add     ecx, eax
        mov     eax, temp
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        add     ecx, edx
        mov     eax, temp
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        mov     eax, edx
        imul    eax, 7AC1h
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        add     ecx, eax
        and     ecx, 0FFFFFFF0h
        mov     output, ecx
	}
	return output;
}

__forceinline unsigned long GetOffset5() {
	unsigned long temp, output;
	__asm {
        rdtsc
        mov     temp, eax
        mov     eax, temp
        mov     esi, 7FFFh
        lea     edx, [eax+eax*2]
        lea     ecx, [eax+edx*4]
        xor     edx, edx
        shl     ecx, 4
        add     ecx, eax
        shl     ecx, 8
        sub     ecx, eax
        lea     ecx, [eax+ecx*4+269EC3h]
        shr     ecx, 10h
        and     ecx, 7FFFh
        mov     eax, ecx
        div     esi
        mov     eax, 20005h
        mov     esi, edx
        mul     ecx
        sub     ecx, edx
        shr     ecx, 1
        add     ecx, edx
        shr     ecx, 0Eh
        lea     edx, [ecx+ecx*4]
        lea     eax, [ecx+edx*4]
        shl     eax, 3
        sub     eax, ecx
        lea     eax, [eax+eax*2]
        lea     edi, [ecx+eax*2]
        lea     eax, [esi+esi*2]
        shl     eax, 4
        add     eax, esi
        shl     edi, 6
        lea     ecx, [eax+eax*4]
        mov     eax, 20005h
        lea     ecx, [esi+ecx*2]
        shl     ecx, 6
        add     ecx, esi
        add     esi, edi
        mul     ecx
        sub     ecx, edx
		mov     output, ecx
	}
	return output;
}

__forceinline unsigned long GetOffset6() {
	unsigned long temp, output;
	__asm {
		rdtsc
        mov     temp, eax
        mov     edx, temp
		imul    edx, 343FDh
        add     edx, 269EC3h
        shr     edx, 10h
        and     edx, 7FFFh
        mov     temp, edx
        mov     eax, temp
        xor     edx, edx
        mov     ecx, 7FFFh
        div     ecx
        mov     ecx, eax
        imul    ecx, 7FFFh
        mov     eax, temp
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        imul    eax, 7AC1h
        add     ecx, eax
        mov     eax, temp
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        add     ecx, edx
        mov     eax, temp
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        mov     eax, edx
        imul    eax, 7AC1h
        xor     edx, edx
        mov     esi, 7FFFh
        div     esi
        add     ecx, eax
        and     ecx, 0FFFFFFF0h
        mov     output, ecx
	}
	return output;
}
 

