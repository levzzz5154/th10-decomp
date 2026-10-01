# Exact file opening and path resolution

The complete **239-byte FileHandle opener** and **121-byte path resolver** now compile as readable C++ without inline assembly. Their maintained probe matches all **360 bytes**. The whole executable remains exact across **487,936 bytes**.

This follows the [runtime/helper checkpoint](runtime_and_helpers_2026-10-01.md): the seven new complete recoveries total **1,974 bytes**. Current progress is **1,861 semantic functions / 99,947 bytes**, with **437 assembly functions / 222,951 bytes** remaining. Five semantic functions retain inline x87; excluding their complete extents leaves **1,856 fully assembly-free functions / 95,496 bytes**. The full decompilation goal remains incomplete.

## FileHandle::Open — 0x00435370

`matching2/msvc/src/platform/file_handle_open_00435370.cpp` first calls virtual Close, then scans the mode to its first lowercase `r`, `w`, or `a`. Read selects access `0x80000000`, disposition 3. Write deletes the original input path, ignores the result, and selects access `0x40000000`, disposition 2. Append selects write access, disposition 4, and later seeks to the end. An unsupported mode returns false. The selected character is read again before resolving the path, preserving effects of intervening calls.

The resolver fills the original 260-byte stack buffer. CreateFileA receives sharing 1, null security and template, and attributes `0x08000080`. Its handle is stored even when invalid. Only -1 means failure; zero is accepted. Append calls SetFilePointer with distance zero and origin 2, ignoring its result. The result is canonical AL zero/one. The native thiscall receiver remains ECX with path/mode on the stack and RET 8. The full compiler-generated security-cookie frame and genuine cookie check at `0x00458EA5` match.

Separate cursor/current-character variables and a shared selection label reproduce the original mode-selection code without assembly. The maintained typed FileHandle and Windows declarations are reused unchanged.

## Path resolver — 0x00435610

`matching2/msvc/src/platform/file_resolve_path_00435610.cpp` receives source EAX and destination ECX, with plain RET. A colon anywhere in the input selects a forward NUL-inclusive copy. Otherwise GetModuleFileNameA fills the output with capacity 260, the genuine CRT strrchr finds the last backslash, the output is truncated after it, and the source is appended.

The original missing-separator behavior is preserved: clear output[0], then still write zero through address 1. The C++ uses integer-address arithmetic and retains the unconditional store. Native MSVC strcpy/strcat intrinsics reproduce the original byte-copy branch and the forward DWORD/tail append, including their overlap and fault behavior. These behaviors are established by the identical native body under the pinned compiler; the standard library's portable overlap contract does not extend them to other compilers.

The resolver is separately selected as a complete recovered function in the opener's native cluster. It contributes its own 121-byte region, with its original source owner retained. The old opener's sole-owner assembly file is removed; both old ASM aliases and previous region records remain available.

## Verification

The [checkpoint evidence](file_open_and_resolve_2026-10-01.evidence.json) independently checks both native MAP extents, full body identity, four direct calls, four Win32 IAT targets, RET 8/plain RET, and the missing-separator stores. It verifies all 3,916 current project-file hashes and 3,065 native input-hash records, the contiguous 412,672-byte `.text` partition, source ownership/coverage, and the exact whole executable. It also rechecks the five preceding recoveries against this newer build's native MAP extents and complete bodies, confirming their source hashes are unchanged. No reference bytes enter compilation, no bytes are masked, and extraction changes neither instruction bytes nor address operands. Formatting and the explanatory source comment were followed by the maintained probe and whole build.

```sh
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
python3 matching2/build/experiments/file_open_and_resolve_2026_10_01/verify_checkpoint.py
git diff --check
```

All **1,910 maintained build units** passed. The EXE SHA-256 remains `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`; `.text` remains `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`. Fresh Ghidra analyses, plate-comment readbacks, maintained probe, build logs, manifest/report snapshots, and the audit script are retained under `matching2/build/experiments/file_open_and_resolve_2026_10_01`. The independent agent's frozen paired production proof is linked by hash in the checkpoint evidence.
