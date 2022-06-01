
/*

	trampoline0							uses trampoline_0_global_var1 
	func23								uses strncpy, invokes callback functions
	func26								invokes callback function

	49 rdtsc blocks
	12									jmp     eax			( return (func24,func6,func9,func8_,func12,func13,func18,func24), (trampoline0 (2x)),  


										or      eax, 100h					31 functions
	347 GetThreadContext calls
	401 SetThreadContext calls
	253 references to Context.Dr0		34 Context.Dr0=eax
										21 cmp [ebp+Context.Dr0], 1
	247	references to Context.Dr1
	142 references to Context.Dr2		   mov [ebp+Context.Dr2], ecx           
	269 references to Context.Dr3
	44  references to Context.Dr6
	250 references to Context.Dr7
*/