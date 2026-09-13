# Archive-loader callers: 0x0040CD20 and 0x0043A1C0

2026-09-13. Two complete caller contributions are now ordinary C++98:
95 bytes of script loading and parsing, and 207 bytes of executable checksum
calculation. Both call the existing 360-byte `Archive_LoadFile` at
`0x0044B360`, whose filename arrives in EAX with the two remaining parameters
on the stack (`RET 8`).

`load_archive_file.json` now uses schema 2. The three maintained sources compile
separately with `/GL` into one native `/LTCG` invocation. `ScriptFileLoader::Load`
is the real entry; `ComputeExecutableChecksum` is the sole extra root.
The archive loader is neither rooted nor exported. Its former synthetic
context is removed, and the shared declaration lives in
`include/th10/platform/archive_file.hpp`.

The script caller empties the shared filename buffer, appends the supplied
name using the compiler's `strcat` intrinsic, loads it from the archive, and
maps the parser's negative result to -1. It matched on the first two-function
native probe, including the EAX filename call at `0x0040CD62`.

The checksum caller obtains the module filename, loads the executable from
disk, sums all complete dwords except the last, frees the buffer, and records
the sum and file size. Its first source spelling used an early return after a
failed filename query. The complete compiler contribution was 199 bytes,
versus retail's 207: the first instruction difference was a short forward
`JNE` at `0x0043A1E8` instead of retail's six-byte `JE` to the final error
return. This moved the checksum loop and changed cookie-check scheduling.
Putting the work inside the successful-query branch and leaving its failure
return at the end produced the exact 207-byte contribution, including the
native loop alignment and security-cookie calls. No manual padding or opcode
replacement is involved.

Focused production probe:

```
python3 matching2/tools/matching/probe.py \
  --source src/script/fun_0040cd20_0040cd20.cpp \
  --output matching2/build/probe_archive_callers
```

All three contributions pass the complete extent, native address, internal
call-edge, and byte comparison gates. Body SHA-256 values:

```
0040CD20  95   42454be0370dc96d15cc76cdcb565b774a08db45c55496bc946331f52c5115f8
0043A1C0  207  61132401168b6000eec5fea17d3d868c579e2ceeb921649396e88875cbdf7aa2
0044B360  360  e5c582565fa1219981c8e4b4ae48b1538af2fe669f954175b390c320f45b3d9a
```

The report is `matching2/build/probe_archive_callers/clusters/load_archive_file/report.json`.
The pre-promotion whole-image baseline also passed independently.

`make verify MSVC_ARGS='--jobs 32'` passes for the promoted batch: the complete
487,936-byte executable retains SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Progress is 438 ordinary-C++ regions / 23,090 bytes, with 2,147 assembly
regions / 365,892 bytes. Net recovery: 2 regions / 302 bytes.
