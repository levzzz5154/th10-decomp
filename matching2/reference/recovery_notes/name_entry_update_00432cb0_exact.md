# High-score name entry, 0x00432CB0: byte-exact C++

The [maintained handler](../../msvc/src/game/title/name_entry_update.cpp)
matches 1,400/1,400 retail bytes: 1,384 bytes before the four phase-table
entries and 16 bytes of table. The [native title cluster](../../msvc/build_support/layout/ltcg/difficulty_select_update.json)
selects the whole compiler contribution at its retail address in both build
modes. It needs no assembly counterpart or permitted differences.

The dispatcher pushes the `Title*` itself. `TitleNameEntry` keeps that ABI;
`NameEntryScreen` borrows its incoming pointer slot only for the duration of
the inlined update. MSVC 7.1 then gives the back-layer animation handle a
separate stack slot. A plain copied room pointer reused the incoming slot,
shortened the body by eight bytes and shifted the phase targets. Making the
*public* entry take a reference instead was not equivalent: it changed what
the dispatcher had to pass.

The native comparison covers all 35 call sites, all four `ret 4` exits and
the four phase targets. The [keyboard differential test](../../tests/title_name_entry_shipped_differential.py)
also exercises all 91 cells, the seven-frame input delay and the persisted
bytes after a short name's NUL. The keyboard fixture does not exercise music
or animation setup; those paths are covered by the byte comparison.
