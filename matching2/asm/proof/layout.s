.intel_syntax noprefix
.code32
.text
# link.exe places .text at RVA 0x1000 with the chosen section alignment.
# Unconverted gaps are synthetic INT3 fill, never counted as retail matches.
.org 0x00401ff0 - 0x00401000, 0xcc
.include "regions/entity_destructor.s"
.org 0x00427c70 - 0x00401000, 0xcc
.include "regions/frame_counter_interval.s"
# Reserve the remainder up to the next object's 16-byte-aligned anchor.
# symbols.s contributes a guarded marker at 0x00452422 for REL32 validation.
.org 0x00452420 - 0x00401000, 0xcc
