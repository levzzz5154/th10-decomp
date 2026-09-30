# Replay pool allocation and append at 0x0042AA50

## Current result

The maintained 139-byte region remains assembly. A fresh, readable C++ model
now reproduces its complete 139-byte extent, private entry convention, and all
instructions except the ordering of two six-byte instructions. The final normal
production probe reports six differing bytes, first at `0x0042AA6F` (+0x1F).
This candidate must not be promoted yet.

The earlier D3304 annotation's 139/139 and no-difference result refers to the
retail assembly overlay. Its assertion that ordinary C++ cannot preserve this
private ABI is superseded by this native LTCG measurement: the freshly compiled
C++ function takes the selector in ESI, the list owner at `[ESP+4]`, returns its
embedded link in EAX, and executes `RET4` without any assembly shim.

The scratch project and evidence are in
`matching2/build/experiments/replay_pool_append_0042aa50_2026_09_27`.
`probe_final.json` is the full normal comparison; `measured_residual.json`
records exact extents, differing offsets, input hashes, and normalization
invariants. `proposal.json` contains no proposed regions because the comparison
fails. No maintained input was edited.

## Recovered behavior and layout

The function allocates `0x6284` bytes with the retail public cdecl operator-new
entry at `0x00452493`. Its inline constructor clears the entire allocation,
initializes two moving cursors, and initializes an embedded doubly linked node.
It selects the owner's stage head at `owner + 0x3C + stage * 12`, walks forward
until the tail, inserts the new node after it, and returns that embedded link.
The allocation's null branch is retained. The source follows retail's later
embedded-member calculation and list insertion rather than adding an early
allocation-failure return.

The typed layout has these independently observed offsets:

| Offset | Field |
| --- | --- |
| +0x0000 | 3,600 six-byte input records, each containing three 16-bit words |
| +0x5460 | Cursor into the input-record buffer, initially allocation base |
| +0x5464 | 3,600 auxiliary one-byte records |
| +0x6274 | Cursor into the byte-record buffer, initially +0x5464 |
| +0x6278 | Embedded node: pool pointer, next pointer, previous pointer |

The owner view contains eight stage-list heads beginning at +0x3C and ending
at +0x9C. Compile-time checks cover total allocation size, record size, both
cursor offsets, the byte-buffer start, embedded link offset, and owner head extent.
The function introduces no selector range check because retail has none.

Fresh Ghidra MCP evidence for `th10.exe`, retained in the scratch directory:

- Target decompilation and complete disassembly at `0x0042AA50` establish the
  allocation, clear, cursor assignments, list traversal, and link insertion.
- Caller `0x00428F60`, call at `0x00428F89`, loads ESI from `0x00474C7C`, pushes
  EBX, and stores the returned EAX link at owner +0x9C.
- Caller `0x004297D0`, call at `0x004298DE`, loads ESI from owner +0x1D0 and
  pushes EDI. It writes byte records through +0x6274 and increments that cursor.
- Caller `0x0042A450`, call at `0x0042A49B`, again passes the global selector
  through ESI and the EBX owner on the stack.
- The writer at `0x00429B60` traverses heads from owner +0x40, increments by
  twelve, and tests against eight at `0x00429CD1`. It subtracts allocation base
  from +0x5460 and divides by six to count the primary records.

## Compiler evidence and residual

The model uses a normal noinline stdcall C++ function with explicit selector
and owner parameters. A 19-byte synthetic forwarding caller lets native LTCG
choose the observed private convention. The caller, zero-filled layout gaps,
and absolute binding for the public allocator are unselected compiler context;
only the complete 139-byte body is compared as candidate recovered code.
There are no private callee anchors and no partial retail-code dependencies.

The retained final native body is SHA-256
`aa7457b7aa7ca4171bb2782f0bb4b5ead0623b1d749569239119b9df25b15016`.
The oracle body is SHA-256
`97d7f4265e073bb1258956d8823e61470c7ecc5c623ccffb1fd3c1602d0209dc`.
Both the native PE and selected COFF region preserve complete 139-byte extents.
The report proves zero instruction-byte changes, zero address-operand changes,
zero masks, and `reference_bytes_used_for_build: false`.

The sole instruction-order discrepancy is:

| Retail order | Candidate order |
| --- | --- |
| Store allocation base at +0x5460 | Compute allocation +0x5464 in EAX |
| Compute allocation +0x5464 in EAX | Store allocation base at +0x5460 |

All subsequent instructions and all preceding instructions match. The six
nonmatching byte offsets are +0x1F, +0x20, +0x21, +0x25, +0x26, and +0x27.

A bounded set of source-sequencing and declaration/context variants is retained
in `variant_results.json`. A compiler barrier after the first cursor store
fixes the store/LEA order, but swaps memset's XOR-EAX and MOV-ECX preparations,
leaving seven different bytes at +0x14. A barrier after memset leaves thirteen
bytes different. Pointer-expression changes, a typed eight-head view, and a
recognized word-clear loop retain the closest 139-byte/six-byte residual.
A loop caller expands the callee to 147 bytes; using memset's returned pointer
expands it to 148 bytes. These rejected variants do not support promotion.

The next concrete lever is the constructor's zero-and-cursor scheduling, ideally
through the typed input/byte-buffer initialization or a genuine replay caller
cluster that preserves the already proven ESI/stack convention. There is no
remaining ABI impossibility claim to solve. No instruction-order rewrite,
encoded-byte mask, inline assembly, naked function, or synthetic register shim
was used in this candidate.
