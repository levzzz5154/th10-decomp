# Unintegrated semantic source candidates

These `.cpp` files preserve readable source models for regions whose retail
entry ABI still depends on private registers. They are intentionally outside
`matching2/msvc/regions.json` and the maintained `translation_units` list; the
mapped files under `matching2/msvc/src` keep the original assembly entries
until their callers can be adapted as a coherent cluster.

The candidates were not compiled, probed, or tested. Their Ghidra evidence and
ABI limitations are recorded in the corresponding notes under
`matching2/reference/recovery_notes`.
