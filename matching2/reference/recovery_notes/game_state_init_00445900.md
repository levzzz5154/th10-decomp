# GameStateInit recovery note — `0x00445900`

Status: semantic candidate attempted and rejected by the exact gate. The
production source was restored to the retail inline-asm body; `regions.json`
still classifies this region as `asm_GameStateInit_00445900`, `0x00445900`,
size `2315` (`0x90b`). No manifest integration was made.

## Evidence and extent

- `standalone_readiness.json`, `function_registry.json`, and `coverage.json`
  describe the legacy semantic function as `GameStateInit`, size `2336`
  (`0x920`). This is 21 bytes larger than the maintained manifest extent.
- Current Ghidra/IDA bytes show the meaningful retail body ending at
  `0x00446208` with `ret 4`; the manifest range is
  `0x00445900..0x0044620B` (exclusive end). The legacy size therefore reaches
  beyond the maintained region and must not be used as a conversion extent.
- Retail entry bytes are
  `6a ff 68 a5 57 46 00 64 a1 00 00 00 00 50 64 89 25 00 00 00 00 51 53 55`:
  it installs the SEH chain before saving registers and obtains the arena from
  `[esp+1c]`. The final sequence restores `fs:[0]`, adds `0x10`, and returns
  with `ret 4`.

## Recovered behavior

The sole caller pushes the game-state arena and calls the constructor. Retail
then performs these operations in this order:

1. Calls the EH vector constructor iterator at `0x0045252D` for `0x1000`
   entities at `state+0x68`, element stride `0x3ac`, using constructor
   `0x00402050` and destructor `0x00401ff0`.
2. At `state+0x3ad130`, clears bit 0 of the nine dwords at relative offsets
   `0x6c, 0xb0, 0xfc, 0x128, 0x174, 0x1b0, 0x1fc, 0x228, 0x378`, clears
   `0xeb` dwords, and writes `0xffff` to relative word offset `0x384`.
3. Constructs the secondary `0x14`-element vector at `state+0x72dae4`, again
   with stride `0x3ac` and the same constructor/destructor pair.
4. Clears `0x1cc918` dwords (`0x732460` bytes) from the arena base. This full
   clear is what the retail bytes show; the archived legacy source's
   arena-size-dependent tail clear is not an exact model.
5. Seeds the absolute matrix globals. The sixteen identity values (`1.0f`,
   bit pattern `0x3f800000`) are at `0x4978b4, 0x49789c, 0x497884,
   0x49786c, 0x497888, 0x4978a4, 0x4978b8, 0x4978bc, 0x497920, 0x497904,
   0x4978e8, 0x4978cc, 0x4978f0, 0x497910, 0x497928, 0x49792c`. The eight
   zero values are at `0x497870, 0x497874, 0x49788c, 0x4978a0, 0x4978d4,
   0x4978d8, 0x4978f4, 0x49790c`.
6. Initializes arena bookkeeping: dwords at `+0x3ada74` and `+0x3ada64`
   become zero; bytes `+0x3ada68`, `+0x3ada69`, `+0x3ada6a`, and
   `+0x3ada6b` become zero; dword `+0x3ada60` becomes one; byte `+0x3ada6c`
   becomes `0xff`; and dwords at `+0` and `+4` become `0xffffffff`.
7. Walks the `0x1000` entity slots at `state+0x68`, adding `0x3ac` each
   iteration and calling `0x00401DE0`. The caller supplies each entity in
   `EDX`; the first call inherits zero in `ECX` from the preceding clear and
   the caller does not reinitialize `ECX` between calls, preserving the
   callee's custom register carry behavior.
8. Allocates and registers twenty `0x24`-byte scheduler records. The two
   primary records are `(callback,index)`
   `(0x4485d0,0x1a)` and `(0x4485e0,8)`. The eighteen secondary records are
   `(0x4485f0,9), (0x448600,0xb), (0x448610,0xd), (0x448620,0xf),
   (0x4486a0,0x10), (0x4486b0,0x11), (0x4486c0,0x12), (0x4486d0,0x13),
   (0x4486e0,0x15), (0x4486f0,0x16), (0x448700,0x18), (0x448710,0x1a),
   (0x448720,0x1c), (0x448730,0x21), (0x448740,0x24), (0x448770,0x29),
   (0x4487c0,0x2a), (0x448810,0x2d)`. Each record clears its callback fields,
   self-links at `+0x14`, stores the arena at `+0x20`, sets flags with `OR 3`,
   and calls primary `0x00449AE0` or secondary `0x00449B70`.
9. Loads the device pointer from `0x00491c30`, loads its vtable, pushes zero
   followed by the device pointer, and calls `[vtable+0x170]`. This is a
   dynamic-call ABI with the device as `this` and one zero stack argument.
   The function returns the original arena pointer in `EAX`.

## Bounded native-LTCG attempt

The task-local candidate used readable arena/task layouts and a separate
compiler-context driver. It included the existing semantic
`src/game/scheduler_tasks.cpp` read-only as a bounded dependency, so native
LTCG could see the observed scheduler convention (task in `ESI`, priority in
`EDI`, scheduler pointer on the stack). The entity initializer at `0x00401DE0`,
allocator/vector helpers, absolute matrix/device data, and the final vtable
call were fixed retail externals. The candidate explicitly supplied the
entity `EDX` setup and the dynamic vtable call.

The candidate compiled successfully. In the native linked image its selected
body was placed at `0x00445900`, but its contribution was only `0x318` bytes
(792), not the required `0x90b` bytes. Its body SHA-256 was
`1937900de496bde3c90560536440d760236404c63232435077588260be8f5af6`.
The first bytes were
`55 8b ec 51 53 8b 5d 08 56 57 68 f0 1f 00 00 68 50 20 00 00 68 00 10 00`,
so the first mismatch is exactly at `0x00445900`: native C++ begins with
`push ebp; mov ebp,esp`, while retail begins with its SEH installation
`push 0xffffffff; push 0x4657a5; mov eax,fs:[0]`.

The native link itself reached PE generation, but the shared validator could
not consume the generated map because the additional scheduler TU emitted an
empty default `.text` contribution (`invalid MAP contribution on line 8`).
That validator/tooling issue is secondary: the PE map and direct byte read
already prove the body extent and entry mismatch, so this candidate cannot be
promoted. Shared Python tooling was not changed.

## Closest compiler shape and next dependency

The semantic shape is now established, but the current compiler context cannot
reproduce the retail frameless/manual-SEH entry, the carry-sensitive
`0x00401DE0` call loop, or the retail unrolled scheduler record setup in the
same 2315-byte contribution. The next dependency to recover is
`0x00401DE0` (`InitializeEntity`): document its `EDX` entity input and `ECX`
carry/output contract, then retry only with a context that can preserve the
retail SEH stack layout at `0x00445900`. Until that custom entry/register shape
is available, the exact production asm is the correct retained implementation.
