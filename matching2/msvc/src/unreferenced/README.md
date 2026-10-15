# Unreferenced retail functions

Retail th10.exe contains these functions, but nothing in it calls them, jumps to
them or stores their address. They are out-of-line copies of small inline
methods (accessors, vector operators, copies, constructors) that the linker
kept. They are compiled only so the image matches byte for byte; no game code
path reaches them.

Unreferenced means: IDA found no reference to the function's entry, and its
address appears nowhere in the retail image as a 32-bit value.
