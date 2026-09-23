# CRT runtime helper fragments: ABI audit

## Result

No source promotion is justified for the six reviewed fragments. In live Ghidra
(`th10.exe`), `get_function_by_address` found no function at any requested entry,
and `get_xrefs_to` reported no incoming references at those entries. The byte
ranges below were independently disassembled with `disassemble_bytes`. With no
entry-level caller evidence, the apparent register inputs cannot be safely
replaced by ordinary C++ parameters. The range at `0x00457A52` contains a
separate Ghidra function at `0x00457A5F`; it also has no reported callers and
does not resolve the surrounding private state.

| Entry and byte range | Observed behavior | ABI / boundary blocker |
| --- | --- | --- |
| `0x004575A1..0x004575BE` (30 bytes) | Walks four-byte callback entries from ESI to the stack end pointer, calls non-null callbacks, and stops on a nonzero callback result. | Begin is supplied in EAX and end at `[ESP+4]`; the fragment has no Ghidra function or incoming reference. The nearby `__initterm` at `0x00457589` has callers, but they target `0x00457589`, not this entry. |
| `0x004577A2..0x004577CD` (44 bytes) | Searches 12-byte records from the EDX base for the ESI key, using the count at `0x00473654`; returns the matching record in EAX or zero. | Inputs are in EDX and ESI, with no stack arguments. No function or incoming reference identifies the call sites or the record type. |
| `0x00457A24..0x00457A3B` (24 bytes) | Tests the EAX character with `_isdigit`; otherwise folds ASCII case and maps `A`–`F` to values 10–15, then returns in EAX. | EAX is the input and return register. The fragment has no Ghidra function or incoming reference, so a standard callable signature is unconfirmed. |
| `0x00457A52..0x00457A7B` (42 bytes) | The first nine bytes return for `-1` or tail-jump to `_ungetc`. At `0x00457A5F`, a separate routine increments state through ESI, reads through `__inc`, skips whitespace, and returns the first non-space character. | Ghidra identifies only the inner body (`0x00457A5F..0x00457A7B`) as `uint __thiscall FUN_00457a5f(void * this, FILE * param_1)`; it reports no references or callers. The machine code also depends on ESI state, which that prototype does not describe. The prefix at `0x00457A52` has no function or incoming reference. |
| `0x0045972A..0x00459775` (76 bytes) | Walks pointer slots from `0x00499200` to `0x00499300`; for each non-null table, visits 0x24-byte records up to table+0x480, calls the target at `0x004660BC` for records with a nonzero field at +8, frees the table, and clears its slot. | The body appears parameterless and saves/restores ESI/EDI, but Ghidra reports no function or incoming reference. The record schema and indirect target type at `0x004660BC` are also unresolved. |
| `0x0045A77E..0x0045A7B3` (54 bytes) | Converts the signed value in EAX to decimal digits at the buffer in `*EDI`, decrements the count at `[ESI]`, updates `*EDI`, and reverses the emitted bytes. | EAX, ESI, and EDI carry live inputs/state. Ghidra reports no function or incoming reference, so its parameter and return contract cannot be established. |

The maintained naked definitions remain in the matching
[`unassigned_*.cpp`](../../msvc/src/unidentified/) files. No manifest or shared
symbol-header changes were made. No build, probe, or test was run.
