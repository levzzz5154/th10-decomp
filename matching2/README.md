# Documented matching reimplementation

This tree contains readable C++ reconstructions of game functions. Compile with
the original MSVC 7.1 code-generation settings:

```bash
mkdir -p build
WINEDEBUG=-all wine "$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe" \
  /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
  "/I$(winepath -w include)" "/Fo$(winepath -w build/entity.obj)" \
  "$(winepath -w src/core/entity.cpp)"
```

Compare a single COFF COMDAT function against its original virtual address with
the relocation-aware comparison tool:

```bash
python3 tools/compare_obj.py build/entity.obj Entity_Destructor 0x401FF0
python3 tools/compare_obj.py build/entity.obj Entity_Constructor 0x402050
python3 tools/compare_obj.py build/entity.obj Entity_Init 0x401DE0
python3 tools/compare_obj.py build/entity.obj DestroyEntityList 0x438A30
```

The comparison length is the compiled function's section size. Relocation
operands are excluded because their final values are assigned by the linker.

Current MSVC 7.1 results for `entity.cpp`:

| Function | Comparable bytes | Result |
|---|---:|---:|
| `Entity_Destructor` | 30 | 100% |
| `Entity_Constructor` | 88 | 100% |
| `DestroyEntityList` | 43 | 100% |
| `Entity_Init` | 273 | partial; exact first 45 bytes |

`Entity_Init` is functionally reconstructed, but MSVC currently schedules its
register restores and callee-save pops differently after the entity clear.
