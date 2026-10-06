# Joystick binding reader: corrected native candidate

The complete ordinary C++ reader at `0x0044A190` is saved in
`reference/semantic_candidates/joystick_binding_reader_0044a190/`. It remains
unselected: its 832-byte body differs from retail's 833-byte body in 49
diagnostic instruction groups. The normalized full-body SHA-256 is
`f3e013202c75921bb381b1555e329b743d244f1800dde31522dd6b89804d844e`.
No difference is accepted or masked. Production still owns the assembly body.

## Recovered behavior

The live Ghidra MCP instance for `th10.exe` was verified, and its read-only
decompilation is retained in `evidence/ghidra_44a190.c`. Retail disassembly was
checked against that result. This corrects several errors in the September
800-byte candidate:

- `joyGetPosEx` uses stdcall. Its 52-byte JOYINFOEX is completely zeroed before
  setting the size and flags. Explicit ordinary `memset` reproduces the full
  13-word initialization; aggregate initialization was shortening it.
- DirectInput zeroes all 272 bytes of DIJOYSTATE2 before GetDeviceState. The old
  candidate did not initialize that buffer.
- Bound button indices address the 128-byte array at state +0x30. The old
  candidate addressed the beginning of the whole record. Every action reads
  the high bit: the shifted-and-masked expressions map that same bit into the
  appropriate action, rather than testing bits 6, 5 or 4 of the original byte.
- DirectInput axes are signed LONG values. Left/up require a value strictly
  below the negative signed threshold; right/down require a value strictly
  above the positive threshold. The old unsigned, inverted comparisons were
  wrong. Subtracting one from each inside-limit predicate preserves the
  observed SETGE/SETLE and decrement arithmetic.
- Poll failure makes an initial Acquire call, then up to 400 additional calls
  while the result is INPUTLOST. The counter limit is checked before the next
  result test, as in retail. There are at most 401 calls.
- The device object is reloaded after external API calls. A cached pointer
  across Poll would miss replacement of the global device slot. Separate
  snapshots for the WinMM device, retry index and state-query index also
  preserve the observed stack-argument read boundaries.

The header describes the complete standard WinMM and DirectInput records,
checks their sizes and relevant member offsets, and types the three COM
methods with their stdcall receiver argument. It contains no unrelated pointer
views of the state buffer. An eight-byte selection record preserves both
indices on the stack under MSVC fastcall, leaving the flags in ECX without an
invented unused EDX argument. Device-index storage is volatile to preserve
retail's stack reloads across the API boundaries. Action constants have names.

## Native measurement and behavioral validation

`measure.py` compiles with the production flags and performs a native link
before loading retail bytes. The ordinary mode is the default; `--ltcg` is a
separate control. A valid no-entry DLL module retains the real root with
`/INCLUDE`; no synthetic caller, extra entry function or byte patch is involved.
Two native image bases identify diagnostic address relocation. That comparison
is not a fixed-layout proof for production selection.

The earlier C-entry alias experiment produced a zero PE entry RVA despite a
valid function contribution. It was replaced by the no-entry module. The
differential runner starts at the real public function's MAP address and loads
the raw native PE without modifying its instructions.

`differential.py` executes retail and native machine code with scripted WinMM,
COM and security-cookie boundaries. All **718 cases pass**, comparing returned
flags and API order/receivers. Checks also require both zeroed buffers, valid
sizes, cookie handling, callee-saved registers and RET 8 stack cleanup. Cases
cover each button mapping, disabled and extreme indices, signed threshold
boundaries and extrema, WinMM unsigned arithmetic, API failures, acquisition
limits and device-slot replacement during Poll. This is bounded behavioral
evidence with scripted devices; it does not establish byte equality or exercise
real hardware.

The source and artifact hashes are in `receipt.json`; the test result is in
`differential_receipt.json`. Reproduce from the repository root:

```sh
python matching2/reference/semantic_candidates/joystick_binding_reader_0044a190/measure.py
python matching2/reference/semantic_candidates/joystick_binding_reader_0044a190/differential.py \
  --candidate matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06/results/saved_candidate/model.exe
```

The test requires Unicorn 2.1.2. This run installed it only into the ignored
experiment dependency directory; that directory is also searched by the test.

## Remaining compiler differences

The 0x154 frame, eight-byte stack alignment, full buffer initializations,
standard import/COM conventions and public argument cleanup are recovered.
Retail keeps the binding cursor in EBX and flags in ESI. The candidate assigns
them differently, spills flags during WinMM axis arithmetic, shares min/max
loads and sums differently, and selects different byte-extension registers.
Retry/failure epilogues and some temporary allocation also differ. Thus the
one-byte extent gap does not mean that only one instruction byte remains.

Controls include ordinary versus LTCG compilation, aggregate versus explicit
initialization, device-index storage and snapshot scopes, scalar versus record
indices, word versus dword flags, Windows LONG/DWORD types, direct array-field
access, threshold-read ordering, local result terms and structured retail exit
paths. Only measured controls are recorded in `source_controls.json`. The
structured exit paths are retained because they follow the recovered graph;
they bring the corrected model from 53 to 49 instruction groups. Standard
Windows scalar types and named action constants preserve that measured body.

No production source, manifest, compiler or matching tool changed. A fresh
read-only audit confirms that the existing 487,936-byte production executable
still equals retail byte for byte, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Exact ordinary C++ coverage remains 61.3%; the overall goal is incomplete.


## Compiler allocation and genuine caller controls

A fresh read-only compiler trace establishes an allocation constraint rather
than another source-spelling guess. The retained tool is
`reference/compiler_traces/regalloc/trace_joystick_globals.py`; the raw successful
trace and a compact summary are in the candidate's `evidence/` directory. It
fingerprints MSVC c2.dll, observes global ChoosePhysReg/Spill and the later
Riscify boundary through debugger breakpoints, then detaches normally. It does
not override allocation choices or write compiler data. The three traced
compiles each produced the same complete raw COFF function as the saved
candidate: 832 bytes, SHA-256
`8f943159cbbc0a6733f16bb7559296db93c47d4c2fb9337249d089ab6ed7209f`.
This is equality of the complete unresolved object body; it does not use the
COFF reader's relocation-ignore set.

The binding cursor's candidate has priority 57 and equal zero costs for EBX
and ESI; the allocator chooses ESI. The flags candidate has priority 25 and
only EBX available. Higher-priority WinMM arithmetic temporaries have already
selected ESI and EDI. The trace supports investigating the real liveness and
arithmetic graph. It does not establish that renaming source variables or
forcing register choices would recover retail. The initial `named` run read
the wrong block-head offset and is excluded as IR evidence; the retained
`riscify` dump uses the corrected block head at +0x1C and contains 37 blocks.
Raw operand fields are preserved without asserting undocumented opcode names.

Fresh Ghidra xrefs to `0x0044A190` identify calls at `0x0044A8B8` and
`0x0044AC96`. The complete callers at `0x0044A5F0` and `0x0044A9D0` are already
selected C++, contrary to the older reconnaissance note. Their legacy source
contains unused formal arguments; the second also has a compiler-only
synthetic context. The new control copies their complete keyboard sampling,
mask packing, repeat counters and edge publication, removes unused inputs,
and links both actual callers directly to the complete joystick reader. No
synthetic caller or extra behavior is added. The 44A5F0 Ghidra decompilation is
retained; the lookup at 44A9D0 returned "No function found" and is retained as
an error record, not a successful decompilation. The latter caller is checked
against its existing source and retail bytes.

The reviewable scalar-stdcall control is retained under
`caller_graph_stdcall/`. Its three-argument declaration tests the possibility
that LTCG originally chose retail's private ABI. It is an experiment, not a
claim about the recovered original signature. LTCG instead places the binding
index in ECX and flags on the stack, producing an unequal 852-byte reader.
Its two full callers produce 853 and 850 bytes, also unequal. Neither this
control nor the fastcall value-record graph supplies a promotion proof.
Ordinary compilation of the value-record graph preserves the canonical
832-byte reader, while the callers still differ. A void-return caller control,
motivated by Ghidra's 44A5F0 result, also remains unequal. Reproduce the retained
complete scalar graph with:

```sh
python matching2/reference/semantic_candidates/joystick_binding_reader_0044a190/caller_graph_stdcall/measure.py retained_genuine_callers_stdcall --ltcg
```

The callers establish Escape at action bit 0x008 and Control at 0x100. The
canonical reader now uses those names instead of the previous Skip/Extra
labels, including its binding fields. A fresh ordinary compile preserves its
complete normalized-body SHA-256 and 49 diagnostic groups. All 718 differential
cases pass again with the same observation digest. PE artifact hashes are
refreshed for this actual build; linker timestamps can change the container
hash while its function body remains identical.

The control ledger now records **51 measured controls**, including the prior
24. New inline axis methods, a separate genuine axis translation unit, binding
snapshots, division spellings, standard WinMM import, caps references, signed
ternaries and word axis terms reproduce the same reader. Volatile caps
snapshot controls grow it to 885/898 bytes; disabling global optimization grows
it to 1537 bytes; size optimization shortens it to 736 bytes. These are not
improvements merely because their diagnostic group counts sometimes fall.
Free-function `__thiscall` fails compilation with C4234 and is recorded
separately from measurements. Prepared but unbuilt variants are not counted.

A fresh whole-file comparison still confirms the 487,936-byte production
executable equals retail with the SHA-256 reported above. Current progress is
2,252 exact ordinary C++ regions / 197,229 bytes (**61.3%** of recoverable code),
8 equivalent C++ regions / 33,176 bytes, and **62 inline-assembly regions /
91,078 bytes**. No production selection changes in this follow-up. The next
compiler constraint is recovering the full arithmetic/read graph that gives
retail's binding and flag live ranges, while preserving the actual caller ABI.
