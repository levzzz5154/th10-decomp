# SSE/XMM execution probe at `0x00458B1E`

## Live Ghidra evidence

The live `th10.exe` listing covers `0x00458B1E..0x00458B52` (53 bytes):

```text
00458b1e  push 0xc
00458b20  push 0x46ac08
00458b25  call 0x00454bbc          ; installs the MSVC SEH frame
00458b2a  and  [ebp-0x1c],0        ; exception result starts false
00458b2e  and  [ebp-0x4],0         ; active scope state
00458b32  movapd xmm0,xmm1         ; probe an XMM instruction
00458b36  mov   [ebp-0x1c],1       ; success result
00458b3d  jmp   0x00458b46
00458b3f  xor eax,eax              ; scope filter returns EXCEPTION_EXECUTE_HANDLER
00458b41  inc eax
00458b42  ret
00458b43  mov esp,[ebp-0x18]       ; exception-handler stack cleanup
00458b46  or    [ebp-0x4],-1
00458b4a  mov   eax,[ebp-0x1c]
00458b4d  call  0x00454bf7          ; restores the SEH frame
00458b52  ret
```

The scope-table bytes at `0x0046AC08` are `FFFFFFFF 00458B3F 00458B43`: one catch-all scope, filter at `0x00458B3F`, handler at `0x00458B43`. The zero-initialized result is changed to one only after `MOVAPD`. Thus the normal path returns one; an exception from the probe is accepted and returns zero. Ghidra's injected decompilation (`return 1`) omits this failure path.

Ghidra finds one caller, `FUN_00458B53`, at its call site `0x00458BB6`. That caller invokes the probe only when CPUID leaf 1 EDX bit 26 (SSE2) is set, then branches on EAX. It uses the result to decide whether to continue its processor-vendor/model checks. This makes the helper an OS/XMM-state execution check on an SSE2-capable CPU.

## C++ recovery

The source uses `_mm_setzero_pd()` and a volatile `__m128d` result inside MSVC `__try`/`__except(1)`. The intrinsic forces an XMM operation; the catch-all reproduces the retail success/fault result. The zero-argument cdecl ABI is preserved, with the observed status returned in EAX. The caller does not consume XMM state, and XMM registers are volatile under this ABI.

This source expresses the observable feature test, rather than forcing the exact `MOVAPD XMM0,XMM1` encoding. The manifest now promotes the 53-byte region to semantic C++ while retaining its previous assembly record, and the shared declaration returns the observed integer status. Exact code generation remains unchecked; no build or probe was run.
