# EH member callback dispatcher at `0x00462706`

The helper is represented in
`matching2/msvc/src/unidentified/CallMemberFunction0_00462706.cpp` as an
ordinary `__stdcall` C++ function. It receives the object pointer and a raw
member-function entry point, then invokes that entry point with the object in
ECX through an x86 `__thiscall` function pointer.

## Live Ghidra evidence

Target: `/th10.exe` (PE x86 little-endian), queried 2026-09-23.

- `get_function_by_address(0x00462706)` identifies `_CallMemberFunction0`,
  with body `0x00462706–0x0046270C` inclusive. Ghidra reports
  `void __stdcall _CallMemberFunction0(void*, void*)`.
- `get_function_xrefs(0x00462706)` reports one direct call, from
  `___DestructExceptionObject` at `0x00462FA1`.
- At `0x00462F9D`, the caller pushes the candidate function pointer from
  `[EAX+0x1C]+4`; at `0x00462F9E`, it pushes the object from `[EAX+0x18]`.
  There is no caller-side stack adjustment after the call. Thus the helper's
  effective arguments are `(object, function_pointer)`, and the helper must
  remove both words from the caller's stack.
- The helper's four instructions pop its return address into EAX, pop the
  object into ECX, exchange the remaining function pointer with the saved
  return address, and tail-jump through EAX. The target therefore runs with
  ECX holding the object and returns directly to the helper's caller. This is
  equivalent to a call through `void (__thiscall *)(void*)` in an ordinary
  `void __stdcall` wrapper, whose return cleans the two stack arguments.

## Integration

The manifest now binds the semantic entry to `_CallMemberFunction0_00462706@8`
and retains `_asm_CallMemberFunction0_00462706` at the same address for the
existing assembly caller. The shared header declares the canonical stdcall
signature with `(void* object, MemberFunction0_00462706 member_function)` and
keeps the raw legacy declaration for inline-assembly references.

The helper is directly called once and uses a normal x86 stdcall boundary;
unwind callbacks at nearby addresses are different: Ghidra shows them loading
data from the caller's live EBP, and xrefs to those entries point to EH data
rather than direct call instructions. Those callbacks were not changed.

No build, probe, or test was run, and byte-for-byte identity is not verified.
