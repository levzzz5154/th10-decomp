# 0x00401630 GameThread_AppendFormatted - decoded, blocked by the same EAX call

2026-09-18. From the `--entry none` prime class. 85 bytes, stack-only entry, and
the body is ordinary formatted output:

```
sub esp,204h                                   ; 0x200-byte buffer + cookie
mov eax,[data_00473660] / mov ecx,[esp+20Ch] / xor eax,esp / mov [esp+200h],eax
lea eax,[esp+210h] / push eax                  ; va_list
push ecx                                       ; the format, arg1
lea edx,[esp+8] / push edx                     ; the buffer
call vsprintf_004524a6                         ; vsprintf(buffer, format, args)
mov ecx,[esp+214h] / add esp,0Ch               ; arg2, read after the call
lea eax,[esp]                                  ; the buffer, in EAX
call GameThread_AppendRecord_00401530
mov ecx,[esp+200h] / xor ecx,esp / call security_check_cookie_00458ea5
add esp,204h / ret
```

which is:

```cpp
void GameThread_AppendFormatted(const char* format, int flags, ...) {
    char buffer[0x200];
    va_list args;
    va_start(args, flags);
    vsprintf(buffer, format, args);
    va_end(args);
    GameThread_AppendRecord(flags, buffer);     // flags in ECX, buffer in EAX
}
```

Everything here is compiler-generated from ordinary C++ and both callees are
already in `asm_symbols.hpp` (`asm_vsprintf_004524a6`,
`asm_GameThread_AppendRecord_00401530`), so the `vsprintf` call and the whole
`/GS` frame come out verbatim. The blocker is `AppendRecord`: the first argument
travels in **ECX** - which a `__fastcall` prototype does provide - and the second
in **EAX**, which no prototype provides. That makes this the fourth call site in
this session with an EAX-carried argument, after the two dummy registrations at
`0x00420B10`/`0x00420C00` and `Recovery_ReplaceExtensionWav_00420A90`; all four
target `AnimationManager_RegisterResource` or a sibling helper, so the pattern is
systemic rather than a one-off.

The region is recorded rather than landed for the same reason as the others: a
prototype that puts the buffer in EDX instead of EAX would be byte-exact (the
whole call is a `call rel32` either way) but would hand the callee the wrong
argument, which this project does not accept.
