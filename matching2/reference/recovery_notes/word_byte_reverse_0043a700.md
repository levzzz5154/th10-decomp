# Word byte reversal at 0x0043A700

Ghidra decompilation confirms a 37-byte `RET 4` function that reverses the
four bytes of its stack argument. Earlier MSVC 13.10 source probes compared
several readable forms and retained the exact assembly when those candidates
missed. The maintained source now contains a direct masked-shift C++ model;
that candidate has not been built or byte-verified.

Ghidra decompiles a 37-byte `RET 4` function that reverses the four bytes of
its stack argument. Retail reserves one local word with `push ecx`, loads the
argument once, copies it to ECX and EDX, shifts those copies by 24 and 16,
writes CL, DL, AH, and AL into the local word, then returns it in EAX.

Readable C++ union, byte-array, aggregate-initializer, and pointer-alias
versions were compiled in earlier attempts. Straight scalar shifts made MSVC
reuse the argument's stack slot and emit a 42-byte body. Addressing the
argument's bytes forced a separate local slot but emitted a 34-byte body using
two source loads and different shift order. A volatile argument forced the
retail `push ecx` prologue but repeated argument loads, yielding a 48-byte
body. Mixed pointer and shift versions did not reproduce all 37 bytes. The
current masked-shift spelling is a semantic model, not an exact-output claim.

The next compiler experiment should preserve a separate local word while
loading the argument once and keeping its original value in EAX through the
four byte stores. Behavior and function boundary are clear; exact code
generation remains open.
