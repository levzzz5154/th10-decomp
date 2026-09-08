# Deterministic PE packaging

`matching2/tools/pack_asm_pe.py` takes the parent assembly build's complete
raw `.text` section and emits the supported PE layout. The normal build has
no retail executable argument and never opens the retail file. Its strict
inputs are:

```text
--text <raw .text buffer>       412672 bytes
--layout matching2/asm/pe_layout.json
--output <new executable path>
```

The text buffer must hash to
`c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`.
The packer rejects a missing, short, long, or byte-different buffer. It also
hash-checks every versioned non-code section and the reconstructed headers,
then requires the complete output to hash to
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The resulting file has four sections and no overlay:

| Section | RVA | raw offset | raw bytes | source |
| --- | ---: | ---: | ---: | --- |
| `.text` | `0x1000` | `0x400` | `412672` | parent assembled input |
| `.rdata` | `0x66000` | `0x65000` | `52224` | `data/rdata.bin` |
| `.data` | `0x73000` | `0x71a00` | `16896` | `data/data.bin` |
| `.rsrc` | `0x9a000` | `0x76200` | `5120` | `data/rsrc.bin` |

The section headers preserve the original virtual sizes, characteristics,
imports, resource directory, IAT, timestamp, Rich data, and PE metadata. The
header is rebuilt from the declarative fields in `pe_layout.json`; it is not a
copied retail header blob. The original DOS prefix is handled explicitly:

* `data/dos_header.bin` holds the 64-byte DOS header.
* `dos_stub.s` contains the 16-bit message-and-exit instructions and is
  assembled with `.code16` on each package build.
* `data/rich_metadata.bin` holds the Rich records and the zero padding up to
  `e_lfanew`.

The assembler output is required to be exactly 64 bytes and to match its
recorded hash before it is placed at prefix offset `0x40`. This makes the
small DOS runtime explicit rather than silently bundling executable bytes in a
metadata blob. It is still outside the Windows `.text` section because it is
part of the PE's DOS compatibility prefix.

Use `--verify /path/to/th10.exe` only as an explicit post-build oracle. The
packer first completes all normal strict checks and only then reads that path;
it verifies both the oracle's supported SHA-256 and whole-file equality.

For the parent assembly build, the expected invocation is:

```bash
python3 matching2/tools/pack_asm_pe.py \
  --text matching2/build/asm-baseline/full/text.bin \
  --output matching2/build/asm-baseline/full/th10.exe
```
