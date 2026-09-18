# 0x0041C880 - node-list walk with a two-argument virtual dispatch

2026-09-18. Found by `screen_regions.py --entry eax --calls`. 54 bytes; the
object arrives in EAX, two further arguments on the stack.

```
mov ecx,[eax+18h]        ; node = this->field_018
push ebp; mov ebp,[esp+8]      ; argument 1
push edi; xor edi,edi
test ecx,ecx; je end
push ebx; mov ebx,[esp+14h]    ; argument 2
push esi
loop:
  cmp [ecx+0Ch],1
  mov esi,[ecx+8]              ; next
  je  skip
  mov edx,[ecx]
  push ebx
  push ebp
  call [edx+20h]               ; virtual slot 8, both arguments forwarded
skip:
  ...
```

Modelled as a class with nine virtuals (the dispatched one eighth) that is never
instantiated - which, per `virtual_dispatch_without_vtable.md`, emits no vtable -
plus the list walk, and driven through the cluster because the object arrives in
EAX. The model **compiles to 45 bytes against retail's 54**, so the walk or the
call's argument setup differs; the comparison stopped at the layout because the
declared size (54) is not the emitted one (45).

This is the first region where a *two-argument* virtual dispatch was modelled;
the call itself lands on the right slot, so the remaining gap is in the walk.

## Accumulator rewrite: 58 bytes, head matches, convention differs

The byte comparison showed what the first model was missing: retail **sums the
virtual call's return value** (`xor edi,edi` before the loop, `add edi,eax` after
the call, `mov eax,edi` before the epilogue) and returns it, while the first model
discarded it. Modelling `int Walk(void* first, void* second)` with
`total += ...->Slot8(first, second);` and `return total;` moves the extent from 45
to **58 bytes against retail's 54**, and the head now matches structurally
instruction for instruction.

Two differences remain: the early-exit path is laid out inline in the model where
retail branches past it, and the model's return is `ret 4` where retail's is
`ret 8` - the whole-program pass re-chose the member's convention, so the two
stack arguments are no longer both on the stack. That convention is the lever for
the next attempt; the body, the dispatch and the accumulation are all right.
