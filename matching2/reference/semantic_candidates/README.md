# Unintegrated semantic source candidates

These `.cpp` files preserve readable source models for regions whose retail
entry ABI still depends on private registers. They are intentionally outside
`matching2/msvc/regions.json` and the maintained `translation_units` list; the
mapped files under `matching2/msvc/src` keep the original assembly entries
until their callers can be adapted as a coherent cluster.

The candidates were not compiled, probed, or tested. Their Ghidra evidence and
ABI limitations are recorded in the corresponding notes under
`matching2/reference/recovery_notes`.

Most of the remaining files were integrated as maintained C++ and later
removed because the full byte-verified build rejected them: they compile, but
their code differs from retail (usually a private register ABI, register
allocation, or frame shape). Each is the unit's source as it stood when
removed; for a unit that also holds matching functions, the file keeps only the
rejected declarations. The mapped sources and their manifest records are back
on the exact assembly.
