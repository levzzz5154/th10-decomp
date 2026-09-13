# Camera application through the render cluster

The 330-byte camera application at 0x004215A0 is exact in readable C++98. It joins
the existing render cluster as a separate /GL source and uses its compiler-visible
Flush helper. The camera receiver is EDI and Flush receives ESI. The two public
render roots remain unchanged; the synthetic array-loop context also calls the
camera method and grows from 233 to 255 bytes. It contributes no recovered bytes.

## Source-shape findings

The first source already had the retail 40-byte frame, all saved registers, all
view/projection construction, and the exact D3DX/device calls. Its remaining 41
byte differences were in the cross-product calculation: direct constructor
arguments selected camera-relative accesses instead of the cached up-vector
pointer and interleaved the output copy differently.

An ordinary inline CameraCross(out, a, b) helper computes three components into
a local vector before aggregate assignment. This produces the retail x87 operand
order, uses the up-vector pointer in ESI, and copies through the same local. The
complete 330 bytes match. The view/projection and normalization routines retain
their real stdcall D3DX boundaries; no synthetic call implementation is used.

The compiler itself emits binary32 4294967296.0 for unsigned viewport dimensions.
Its native constant is placed at 0x00470B98 with the existing constants mechanism
and an ordinary .rdata layout gap. No constant aliases are needed in the accepted
batch, and no literal or instruction bytes are rewritten.

## Default setup still blocked

The neighboring 287-byte default setup at 0x00421480 was also probed now that its
private flush call is expressible. Six source forms produced the following
complete compiler extents: 300, 298, 329, 329, 291, and 292 bytes. Width/height and
half-dimension locals, constructor expressions, and aspect-ratio ordering affect
x87 rounding stores, value retention, and frame size. The 291/292-byte candidates
have the correct 44-byte frame but different operand/store scheduling. The tan
operation does inline to FPTAN, so the remaining issue is not an outlined math
call or private ABI. Normalizing source literals through rigorously validated
constant aliases in the disposable experiment did not repair the code shape.

Default setup remains assembly. Its failed longer contribution also moves later
native functions by 16 bytes, which explains their shifted relative calls in
those diagnostic outputs; those shifts are not an additional ABI blocker. The
accepted camera-only expansion restores every existing function's exact address
and removes the experimental aliases and default-setup source from the cluster.

Diagnostic outputs are `matching2/build/camera-lab/camera1`, `camera2`, and
`default1` through `default6`. The accepted production focused probe is:

`python3 matching2/tools/matching/probe.py --source src/render/camera_apply.cpp
--output matching2/build/probe_camera_apply`

All 14 real bodies are EXACT. `make verify MSVC_ARGS='--jobs 32'` passes with the whole 487,936-byte executable
identical. Progress is 456 C++ regions / 28,016 bytes; 2,129 assembly regions /
360,966 bytes. Whole executable SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The new camera body SHA-256 is `ce13b8109946afb7eaff5b7191f013f485a9d0530e615c199d72166d1f71f0c6`.
