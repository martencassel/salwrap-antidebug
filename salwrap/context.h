#pragma once
 
#define CURRENT_THREAD	0xFFFFFFFE
#define DISABLE_DEBUG	0x11110400

__forceinline void GetContext(LPCONTEXT lpContext) {
	// Get breakpoints registers
	lpContext->ContextFlags = CONTEXT_DEBUG_REGISTERS;
#if DEBUG == 1
	fakeContext.ContextFlags= CONTEXT_DEBUG_REGISTERS;
	lpContext->Dr0 = fakeContext.Dr0;
	lpContext->Dr1 = fakeContext.Dr1;
	lpContext->Dr2 = fakeContext.Dr2;
	lpContext->Dr3 = fakeContext.Dr3;
#else
	GetThreadContext((HANDLE)CURRENT_THREAD,lpContext);
#endif
}

__forceinline void SetContext(LPCONTEXT lpContext) {
	lpContext->ContextFlags = CONTEXT_DEBUG_REGISTERS;
#if DEBUG == 1
	fakeContext.ContextFlags= CONTEXT_DEBUG_REGISTERS;
	fakeContext.Dr0 = lpContext->Dr0;
	fakeContext.Dr1 = lpContext->Dr1;
	fakeContext.Dr2 = lpContext->Dr2;
	fakeContext.Dr3 = lpContext->Dr3;
#else
	if(!SetThreadContext((HANDLE)CURRENT_THREAD, lpContext)) {
		printf("SetThreadContext failed in SetContxt!\n");
	}
#endif
	printf("SetContext End\n");
}

__forceinline void SetContext(LPCONTEXT lpContext, DWORD Dr0, DWORD Dr1, DWORD Dr2, DWORD Dr3, DWORD Dr7) {
	printf("SetContext Start\n");
	lpContext->ContextFlags = CONTEXT_DEBUG_REGISTERS;
	lpContext->Dr0 = Dr0;
	lpContext->Dr1 = Dr1;
	lpContext->Dr2 = Dr2;
	lpContext->Dr3 = Dr3;
	lpContext->Dr7 = Dr7;
#if DEBUG == 1
	fakeContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	fakeContext.Dr0 = lpContext->Dr0;
	fakeContext.Dr1 = lpContext->Dr1;
	fakeContext.Dr2 = lpContext->Dr2;
	fakeContext.Dr3 = lpContext->Dr3;
	fakeContext.Dr7 = lpContext->Dr7;
#else
	if(!SetThreadContext((HANDLE)CURRENT_THREAD, lpContext)) {
		printf("SetThreadContext failed in SetContxt!\n");
	}
#endif
	printf("SetContext End\n");
}

__forceinline void SetContext(LPCONTEXT lpContext, DWORD Dr0, DWORD Dr1, DWORD Dr2, DWORD Dr7) {
	printf("SetContext Start\n");
	lpContext->ContextFlags = CONTEXT_DEBUG_REGISTERS;
	lpContext->Dr0 = Dr0;
	lpContext->Dr1 = Dr1;
	lpContext->Dr2 = Dr2;
	lpContext->Dr7 = Dr7;
#if DEBUG == 1
	fakeContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	fakeContext.Dr0 = lpContext->Dr0;
	fakeContext.Dr1 = lpContext->Dr1;
	fakeContext.Dr2 = lpContext->Dr2;
	fakeContext.Dr7 = lpContext->Dr7;
#else
	if(!SetThreadContext((HANDLE)CURRENT_THREAD, lpContext)) {
		printf("SetThreadContext failed in SetContxt!\n");
	}
#endif
	printf("SetContext End\n");
}

__forceinline void DisableDebug(LPCONTEXT lpContext) {
	// Disable breakpoints registers
	lpContext->Dr7 = DISABLE_DEBUG;
#if DEBUG == 1
	fakeContext.Dr7 = DISABLE_DEBUG;
#else
	if(!SetThreadContext((HANDLE)CURRENT_THREAD, lpContext)) {
		printf("SetThreadContext\n");	
	}
#endif
}

