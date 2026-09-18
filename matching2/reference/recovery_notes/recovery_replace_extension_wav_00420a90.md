# 0x00420A90 Recovery_ReplaceExtensionWav - nearly all readable C++

2026-09-18. From the `--entry none` prime class (no register read before writing
one). 120 bytes, two stack arguments, and the body is almost entirely
compiler-generated from ordinary C++:

```
sub esp,104h                     ; frame
mov eax,[data_00473660] / xor eax,esp / mov [esp+100h],eax    ; the /GS cookie
...inlined strcpy into the 0x100-byte buffer...
lea eax,[esp] / push 2Eh / push eax / call strrchr_00452930   ; strrchr(buffer, '.')
mov byte [eax+1],77h / [eax+2],61h / [eax+3],76h              ; ".wav"
push <out> / push 1 / lea edx,[esp+8] / mov eax,492590h
call AnimationManager_RegisterResource_0043e460
mov ecx,[esp+100h] / xor ecx,esp / mov eax,1
call security_check_cookie_00458ea5                          ; the /GS check
```

So the recovered source is:

```cpp
int Recovery_ReplaceExtensionWav_00420a90(int unused, const char* source, void* out) {
    char buffer[0x100];
    strcpy(buffer, source);                 // inlined by the compiler, delta form
    char* dot = strrchr(buffer, '.');
    dot[1] = 'w'; dot[2] = 'a'; dot[3] = 'v';
    AnimationManager_RegisterResource(0x00492590, buffer, out, 1);
    return 1;
}
```

Everything except the `RegisterResource` call is plain C++ that the compiler
generates verbatim - the inlined strcpy, the strrchr call (bindable through the
manifest's `symbols` table as `_asm_strrchr_00452930`), the three byte stores, the
`/GS` prologue and epilogue. The call itself is the obstacle: the caller sets
**EAX = 0x00492590** and **EDX = the buffer**, pushes **out** and **1**, and leaves
ECX unset, which is the same convention the two dummy registrations at
`0x00420B10`/`0x00420C00` use - and no prototype produces an argument in EAX.

Two ways forward, both already precedented in this project: declare the callee
with the closest `__fastcall` prototype and measure the delta (one probe run), or
write the call as a four-line inline `__asm` block inside otherwise readable C++,
exactly as the landed `0x00443B60` does for its `fsincos` sequences. Here the
trade is favourable - the asm would be a few lines of a body that is otherwise
pure C++ - which is why this region is recorded as an open candidate rather than a
blocked one.

The sibling `0x00420B80` (125 bytes) has the same structure - inlined strcpy,
strrchr, the three `.wav` stores - so whatever lands here lands there too.
