# Decimal digit append at 0x0045A77E

Ghidra identifies a 54-byte function with no incoming xrefs. Retail receives
a signed integer in EAX, a remaining-slot count through ESI, and an output
cursor through EDI. While more than one slot remains, it writes the signed
remainder modulo ten as an ASCII digit, advances the cursor, decrements the
slot count, and repeats while the quotient is positive. It then reverses the
newly written span. The same write-and-reverse pattern appears in the adjacent
`__store_num` routine at `0x0045A7B4`.

The [C++ source](../semantic_candidates/append_decimal_digits_0045a77e.cpp)
keeps the signed quotient/remainder and the retail do-while reversal order.
Retail enters the reversal even when it wrote no digit, so that path reads at
`cursor - 1`; the intended caller must provide a writable preceding byte or
more than one remaining slot. The manifest retains the assembly record in
`previous_record`. Typed cdecl arguments replace the retail register ABI;
byte matching remains unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
