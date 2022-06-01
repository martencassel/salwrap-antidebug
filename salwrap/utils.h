#pragma once
#include "stdafx.h"
#include <windows.h>

__inline void PrintContext(LPCONTEXT lpContext) {
	printf("Debug Register: \n");
	printf("DR0: 0x%X  \n", lpContext->Dr0);
	printf("DR1: 0x%X  \n", lpContext->Dr1);
	printf("DR2: 0x%X  \n", lpContext->Dr2);
	printf("DR3: 0x%X  \n", lpContext->Dr3);
	printf("DR7: 0x%X  \n\n", lpContext->Dr7);
}

__forceinline void _memcpy(void *buf_dst, void *buf_src, int buf_len) {
	__asm {
		mov		esi, buf_src
		mov		edi, buf_dst
		mov		ebx, buf_len
		cmp     edi, esi		  
        jbe     short loc1    
        lea     eax, [esi+ebx] 
        cmp     edi, eax
        jnb     short loc1
        mov     esi, eax
        lea     eax, [edi+ebx]
        mov     edi, eax
        cmp     ebx, 4
        jb      short loc2
        mov     eax, edi
        and     eax, 3
        test    eax, eax
        jz      short loc3
        sub     ebx, eax
loc4:
		dec     esi
        dec     edi
        mov     cl, [esi]
        mov     [edi], cl
        dec     eax
        jnz     short loc4
loc3:
        cmp     ebx, 4
        jb      short loc2
        sub     esi, 4
        sub     edi, 4
        mov     ecx, ebx
        shr     ecx, 2
        std
        rep movsd
        cld
        add     esi, 4
        add     edi, 4
        and     ebx, 3
        jz      short loc_21281E3
loc2:
        dec     esi
        dec     edi
        mov     cl, [esi]
        mov     [edi], cl
        dec     ebx
        jnz     short loc2
loc1:
        cmp     ebx, 4
        jb      short loc_21281DF
        mov     eax, edi
        and     eax, 3            ; gets zero
        jz      short loc_21281D3
        mov     ecx, 4
        sub     ecx, eax
        sub     ebx, ecx
        rep movsb
        cmp     ebx, 4
        jb      short loc_21281DF
loc_21281D3:                            
        mov     ecx, ebx		; it runs here
        shr     ecx, 2
        rep movsd
        and     ebx, 3
        jz      short loc_21281E3
loc_21281DF:                            
        mov     ecx, ebx
        rep movsb
loc_21281E3:
	}
}
