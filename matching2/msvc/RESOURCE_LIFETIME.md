# Resource-file lifetime recovery

The maintained C++98 implementation is
[`src/platform/resource_lifetime.cpp`](src/platform/resource_lifetime.cpp), with
shared buffer cleanup in
[`buffer_file_lifetime.inl`](include/th10/platform/buffer_file_lifetime.inl).

| Newly selected ordinary C++ | Retail address | Bytes |
| --- | --- | ---: |
| `ResourceFile::~ResourceFile` | `0x00436680` | 49 |
| `ResourceFile::Open` | `0x004366C0` | 168 |
| Total added | | 217 |

This raises ordinary-C++ coverage from 44 regions / 1,462 bytes to 46 regions /
1,679 bytes. The existing 30-byte resource deleting-destructor entry is **not**
new recovery. Constructors emitted only to make the virtual entries available
are not selected or counted either.

## Evidence and contract

The preserved disassemblies are
[`00436680.asm`](../../decompiled/ghidra_full/functions/00436680.asm) and
[`004366C0.asm`](../../decompiled/ghidra_full/functions/004366C0.asm).
The existing callers and vtables establish ordinary x86 `thiscall`: `this` in
ECX, two stack arguments and `ret 8` for `Open`, and a byte result in AL.
The destructor has no stack arguments. `BufferFile` occupies 16 bytes: vptr at
0, byte count at 4, current position at 8, and owned allocation at 12.

`Open` ignores its mode argument. It closes the previous buffer, locates a
module-local RCDATA resource (type 10), loads and locks it, allocates its reported
size, copies the bytes, and makes the copy the new read position.

| Path | Behavior after the initial close |
| --- | --- |
| Find or load fails | Close/reset again; return 1 |
| Lock fails | Call `FreeResource(NULL)`, close/reset, return 1 |
| Allocation fails | Close/reset; no `FreeResource`; return 1 |
| Success, including a non-null zero-size allocation | Copy, set position, call `FreeResource(loaded)`, return 1 |
| Destruction | Free a non-null owned buffer once, clear fields, perform base destruction |

These are retail quirks, not recommended API behavior. In particular, the
return value cannot distinguish a load failure from success. The shared failure
label preserves the original control-flow sharing without embedding instructions.

## Compiler boundary and remaining assembly

MSVC 13.10.6030 uses the unchanged project flags. Resource destruction inlines
the buffer destructor and `Close`; the buffer deleting-destructor entry must
still call its own out-of-line destructor. The shared inline definitions express
that difference with a translation-unit-local `noinline` attribute. Their
cleanup bodies remain identical ordinary C++.

Ordinary constructor definitions make the compiler emit virtual lifetime
entries. They are **not** ABI replacements for the retail constructors at
`0x00436380` and `0x00436640`, which take `this` in EAX and remain assembly.
The normalizer selects only the manifest's whole sections; no generated
constructor bytes enter the executable.

The resource loader's virtual close and destructor's buffer cleanup are C++.
The fixed retail heap entries (`malloc` at `0x00452706`, `free` at `0x00452422`,
and the deleting destructor's `operator delete` at `0x004524A1`) remain assembly.
Win32 resource APIs resolve through the preserved import table. Buffer open and
seek, custom-register constructors, and the unrelated palette routine are not
claimed as recovered. RNG and seek compiler probes did not achieve exact output
and did not change the maintained implementations or progress counts.

## Verification

`make test` compiles the actual maintained resource implementation as C++98 and
runs scripted Win32/heap boundaries. It checks every failure stage with and
without an existing buffer, exact cleanup order, copied bytes and ownership,
integer resource names, 0/1/4/37-byte resources, repeated close, reopen, and
polymorphic destruction. It also checks the ten new relocation records and
rejects mutations to resource IAT/destructor call operands.

The native contract harness does not establish the retail x86 ABI; the fresh
MSVC fixed-address build does. That build checks every selected extent and
resolved relocation, all 412,672 `.text` bytes, and the complete 487,936-byte
executable. The expected executable SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
