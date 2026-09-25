# Compact payload and record helpers

Ghidra identifies the following independent functions, each with no incoming
xrefs:

- `0x0042AC90..0x0042ACAD`: sum unsigned bytes from offset eight through the
  end of a buffer. Retail receives the buffer in ESI and total size in EDX.
- `0x00435FA0..0x00435FC3`: publish an index at `data_0048F860` and set its
  12-byte record at `data_00477858 + 12 * index` to `{0x2000, 0, 0}`. Retail
  receives the index in EAX.
- `0x00436D60..0x00436D96`: for an ARGB4444 pixel with nonzero alpha nibble,
  add its red, green, and blue nibbles to three consecutive totals and
  increment a qualifying-pixel count. The identical packed-color behavior at
  `0x00446570` establishes the format. Retail uses EAX, EDX, and ESI for
  these pointers.

The maintained C++ sources are [payload sum](../semantic_candidates/sum_payload_bytes_0042ac90.cpp),
[record initializer](../semantic_candidates/initialize_indexed_record_00435fa0.cpp),
and [ARGB4444 accumulator](../semantic_candidates/accumulate_argb4444_color_00436d60.cpp).
Their manifest entries retain the old assembly records in `previous_record`.
Typed cdecl arguments replace the retail register ABIs; byte matching remains
unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
