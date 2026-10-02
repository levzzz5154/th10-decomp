# Archive index loader `0x00434F70`: native recovery

2026-10-02. Maintained promotion verified.

The complete readable C++ loader is maintained and verified: all 350 retail
bytes match at the original address, SHA-256
`9675b8ea548c4a78296c51cbe9b9dc03f45d5917a95f8c5901170a8bec1c5f53`.
The maintained native probe and whole-executable byte gate pass.
The maintained probe is recorded in `matching2/build/archive_index_20261002/maintained_probe.json`; whole-image proof is in `whole_verification.json` and `whole-exe.log` in the same lab. The rebuilt 487,936-byte EXE is byte-for-byte identical to retail, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. The source audit now records 2,102 asm-free regions / 136,389 bytes, with 218 bodies / 186,742 bytes still containing assembly. Six older semantic bodies retain 4,525 bytes of inline assembly and receive no asm-free credit.
Only Index350 receives new credit; existing owners and source paths are unchanged.

Initializing the actual unpacked buffer before the missing-file guard fixes
the previous 351-byte model. Its later declaration allowed MSVC to sink the
zero initialization past Open argument pushes. The earlier declaration
preserves the exact prologue and failure paths without barriers, volatile,
synthetic callers, added arguments, or instruction rewrites.

## Genuine graph and alias provenance

The complete real zero-argument version loader at `0x00420100` calls disk
Open108 at `0x00434C30`, which calls LoadIndex350. Native LTCG derives archive
receiver ESI, path stack, AL result, and `RET 4`. The complete actual cipher
co-compiles with Index and Read281, deriving AL key and five stack arguments/
`RET 20`. External decoder and recovered parser declarations retain their
independently proved four-stack-input/`RET 16` and three-stack-input/`RET 12`
contracts.

The FileHandle vtable alias at `0x0046F230` explicitly uses
`reference_scope: compiled_graph`. Its sole literal reference is in complete
exact Open108, an unselected genuine caller emitted from `cluster.obj` in
`.text$a02open`. The reviewed validator checks compiler origin, complete
contribution, actual reference bytes, and retail alias payload. This opt-in
changes only where alias-reference proof may be found; the default
selected-body rule remains unchanged. No instruction/address bytes are
modified or masked, and the reference bytes are not used to build code.

| Complete production body | Natural bytes | Matching positions |
| --- | ---: | ---: |
| LoadIndex, selected | 350 | 350 |
| Disk Open | 108 | 108 |
| Close | 86 | 86 |
| Read | 281 | 281 |
| Find | 53 | 53 |
| String duplicate | 47 | 47 |
| Cipher, unselected | 323 | 226 |
| File loader | 360 | 360 |
| Log append | 201 | 201 |
| Version caller, unselected | 174 | 143 |

All rows are complete natural sections at their original addresses. Cipher
and Version remain unmatched; every unselected dependency receives zero new
credit. No extra constructor, destructor, or EH code is emitted. Behavior
remains the previously characterized model, including its callback reloads,
short-read handling, header mutations, and cleanup. The earlier 623 scenarios
are historical semantic evidence, not newly run byte proof.

## Retained evidence

`matching2/build/archive_index_20261002/frozen_original_project` preserves the
original unchanged-ownership graph. `frozen_original_native_receipt.json`
pins all 21 compiler input hashes and original native PE/map;
`verify_frozen_original.py` rechecks those hashes and all ten complete
contributions against retail. Its verification report intentionally retains
zero credit because that receipt predates maintained promotion.

The separate `archive_index_00434f70_compiled_graph.json` adds only the reviewed
alias scope; `compiled_graph_manifest_delta.json` pins that change.
`ready_original_proposal.json` lists the exclusive source/layout/helpers.
Historical source-split scratch is excluded from promotion.

Validator receipts are retained under
`matching2/build/experiments/anchor_alias_validation_20261002`:
`real_native_validation.json` and `final_archive_probe.json`. They include
complete Open108 provenance, exact Index350, and seven rejected real PE/MAP
negative cases. The independent clean graph at
`unpacked_before_guard_layout/native-bi088cp5` also proves Index350 and its
private ABI without `/FORCE`; a second agent audited its PE/map.

All 41 focused validator tests pass, including default compatibility and rejection cases. The tool change invalidated the unit cache once: this gate compiled 1,610 units and extracted 150 library members with zero failures. Normal incremental builds retain the existing cache mechanism. Reproduce the maintained gates with:

```sh
python3 matching2/tools/matching/probe.py --project matching2/msvc \
  --source src/archive/dat_archive_load_index_00434f70.cpp \
  --output matching2/build/archive_index_20261002/reprobe
make MSVC_ARGS='--verify /home/levzzz/Games/th10Decomp/matching2/build/oracle/th10.exe'
```
