# 0x0041F8D0 - startup resource loader: decoded, needs three bound callees

2026-09-18. Found by `screen_regions.py --entry ecx`. 82 bytes, **no entry
registers at all** - the first instruction writes EDX, so the function takes no
arguments and a plain translation unit could host it if its three callees were
reachable. Full listing:

```
mov edx,[data_00491c10]
push 46D254h; mov ecx,6
call asm_Recovery_LoadCachedResource_00447280     ; success -> next
test eax,eax; jne L2
push 46CB68h; jmp fail                            ; message for id 6
L2:
mov edx,[data_00491c10]
push 46CD88h; mov ecx,7
call asm_Recovery_LoadCachedResource_00447280     ; success -> ok
test eax,eax; jne ok
push 46CD54h                                      ; message for id 7
fail:
mov ecx,474F70h
call asm_TextLog_Append_0044b810
add esp,4
or eax,-1
ret
ok:
xor eax,eax
ret
```

So: load cached resource **6** and then **7**; on each failure log the matching
message through the text log at `0x00474F70` and return **-1**; on success return
**0**. Both messages and both name pointers are literal addresses the compiler can
emit as immediates, and the two `LoadCachedResource` calls are ECX/EDX/stack
(`id`, manager, name) - a `__fastcall` declaration plus a `relative_code` binding.

`TextLog_Append` is the interesting one: it wants **ECX plus one stack
argument**, which no free-function prototype produces. That shape is a
`__thiscall` member, so declaring a member on a log type and calling
`((TextLog_0041f8d0*)0x474F70)->Append(message)` reproduces it, with the member's
decorated name bound to `0x0044B810` in the layout. That trick generalises to
every ECX-plus-stack callee in the remaining assembly.

Classified as a cluster target because all three callees are assembly; the model
itself is written out in this note and ready to drive.

## Attempted through the cluster: layout cannot resolve the function

The model from this note was compiled in a throwaway copy. The object contains
exactly the expected symbols -

```
?Recovery_LoadStartupResources_0041f8d0@@YAHXZ     (the function, cdecl)
?Append@TextLog_0041f8d0@@QAEXPAX@Z                (the log member, undefined)
@asm_Recovery_LoadCachedResource_00447280@12       (the resource loader, undefined)
```

so the declarations and the three layout bindings are right - yet the cluster
stopped with `size=0 … must resolve to one exact symbol` and a context whose
emitted extent was 120 bytes rather than the declared 40. The model file must be
declared `__cdecl` explicitly, because the project compiles with `/Gz` and a free
function without a convention otherwise gets a `@0`-suffixed stdcall name. What
remains is a layout/context issue in the cluster, not the recovered code.

## Second attempt: `__declspec(noinline)` fixed the inlining, sizes still off

Without `noinline` the whole-program pass inlined the function into the synthetic
context, which is why the symbol never appeared in the map and the context was 120
bytes wide. Adding it produces a clean split - function `0x5B` (91) at
`0x0041F8D0`, context `0x21` (33) - but the layout still fails the entry check,
because the machinery places the context on its own alignment: with a declared
context address of `0x0041F940` the map shows it at `0x0041F950`, sixteen bytes
later. So a context address for this cluster has to be read back from a first
build rather than computed as `align(address + size + 31)`.

Also tried in the same run: the shared-message form

```cpp
    void* message;
    if (load(6, manager, name6) == 0)        message = (void*)0x0046CB68;
    else if (load(7, manager, name7) == 0)   message = (void*)0x0046CD54;
    else                                     return 0;
    ((TextLog_0041f8d0*)0x00474F70)->Append(message);
    return -1;
```

which matches retail's shared `jmp fail` structure and emitted 91 bytes against
retail's 82 - nine over, so it is not the final shape either.
