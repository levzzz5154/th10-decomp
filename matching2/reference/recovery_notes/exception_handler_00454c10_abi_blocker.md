# `0x00454C08`: original EH3 runtime section

Ghidra separates an eight-byte `VC20XC00` prefix at `0x00454C08`, the
`__except_handler3` entry at `0x00454C10`, and
`__seh_longjmp_unwind@4` at `0x00454CF6`. These are one 265-byte `.text`
section (number 1) of the toolkit's
`libcmt.lib/build/intel/mt_obj/exsup3.obj`, not three independently compiled
game functions. Its 241 non-relocation bytes match retail; all six REL32
fields resolve to the original exception-runtime functions. A focused
`probe.py --source lib/libcmt.lib/build/intel/mt_obj/exsup3.obj` comparison
verifies the complete section and relocations.

The section has no function symbol at offset zero. Its static `.text`
section symbol is selected via the unit's `.text`/`.r000001` aliases and
exported as `_crt_exsup3_text_base_00454c08`; the original
`__except_handler3` symbol remains at +8, with a private alias to avoid
colliding with the manifest's existing absolute binding. The original
`__seh_longjmp_unwind@4` symbol remains at +238. The two obsolete naked
transcriptions are no longer build inputs. The linker incorporates the
toolkit's unmodified section, so there is no need to invent a C++ signature
for its private SEH frame/register convention.
