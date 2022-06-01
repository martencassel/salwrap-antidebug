# salwrap-antidebug

This repo contains an implementation of the anti-debug techniques used in the reference document.

https://media.defcon.org/DEF%20CON%2016/DEF%20CON%2016%20presentations/DEF%20CON%2016%20-%20newger.pdf


# Debug View

```
[2692] start_trampolines.
[2692] trampoline0
[2692] Push to callstack
[2692] Copy trampoline0 buffer to new offset
[2692] Calculate return address in next trampoline0 buffer.
[2692] Jump to trampoline_fn.
[2692] start of func1.
[2692] trampoline0
[2692] Push to callstack
[2692] Copy trampoline0 buffer to new offset
[2692] Calculate return address in next trampoline0 buffer.
[2692] Jump to trampoline_fn.
[2692] start of func15.
[2692] Return from trampoline_fn.
[2692] Return from trampoline_fn.
[2692] Return from trampoline_fn.
[2692] Pop callstack.
[2692] end of start_trampolines.
```
