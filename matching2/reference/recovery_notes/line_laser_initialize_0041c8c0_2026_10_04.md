# Moving line-laser initialization: exact C++ at 0x0041C8C0

Recovered the complete 442-byte virtual initializer in
`src/game/line_laser_initialize_0041c8c0.cpp`, replacing its naked assembly owner.
The receiver arrives in ECX, the parameter pointer is on the stack, and the
function returns zero with RET 4. There is no inline assembly in the new source.

Ghidra initially had no function at this address. Creating a function with
disassembly enabled produced a complete 442-byte body. Its decompilation and
the retail instructions confirm that this is the moving line-laser initializer:
the 0x1DC-byte parameter block is copied to +0x424, the state becomes 2, and
the beam at +0x600 and flare at +0x9AC are started and stepped. The startup
timer at +0x410 is set to 30, and geometry and polar velocity are initialized.
The initializer shares the recovered beam-laser initializer's script setup.

The parameter offsets matter: angle is +0x0C, length +0x14, length step +0x1C,
speed +0x20, colour +0x24, script +0x26, and flags +0x28. Size and sprite offsets
are checked at compile time. The remaining undocumented fields stay reserved.

The existing `entity_start_script_00404f30` native cluster now also selects this
initializer. Its two calls use the recovered script starter's private ESI/EAX
ABI. The polar setter at 0x0041F800 is a declared external thiscall dependency;
the animation tick remains the existing separately owned dependency. No
dependency bytes, constants, or output instructions are patched.

An ordinary inline startup-timer helper is necessary for the retail scheduling.
Its reset has the same final state as `FrameTimer::Set`, but stores elapsed
before previous. Expanding the reset directly into the initializer allowed
MSVC to move the timer flags load ahead of the final flare flag operations and
interleave the constant timer stores with the geometry copy. Keeping the reset
inside its helper restores the exact instruction order. The acceleration
assignment uses separate if/else stores; a float conditional expression emits
x87 loads instead of retail's immediate integer stores.

Three native candidates were measured. The first emitted 447 bytes. The second
had the required 442-byte extent but 109 different bytes. The inline-helper
candidate and the cleaned production source both have zero byte differences in
the complete retail window. Reproducible sources, native PE images, MAP files,
and SHA-256 comparisons are retained under
`matching2/build/experiments/line_laser_initialize_2026_10_04`.

Validation: the production probe reports all four selected cluster functions
EXACT (stage script start, entity script start, moving line laser, beam laser).
The normal full build passes its exact gate outside the three preexisting
equivalent C++ regions. Remaining assembly falls to 145 regions / 128,926 bytes;
ordinary exact C++ rises to 2,167 regions / 160,627 bytes.
`make EXACT=1` also passes: the complete 487,936-byte executable is byte-identical
to retail, with the three preexisting equivalent regions using their assembly
fallbacks. This does not imply completion of the inline-assembly-free objective.
