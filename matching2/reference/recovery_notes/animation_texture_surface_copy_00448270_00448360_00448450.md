# Animation texture and image surface copies (0x00448270, 0x00448360, 0x00448450)

2026-10-02. `src/render/animation_texture_surface_copy.cpp` owns all three as
ordinary C++ in the new `animation_texture_surface_copy` native-LTCG cluster.
The cluster compiles unselected copies of the batch flush (0x00442F50) and
the indexed-resource clear (0x00447F70) and a synthetic array caller; the
private register conventions of all three bodies fall out of that without
roots. Incremental `make` verifies the whole EXE exactly.

Findings that decided the bytes:

* **Stray `test eax,eax` after the surface copy.** Retail tests the D3DX
  result and then runs the same releases either way. An empty `if` body drops
  the test; writing the failure branch with its own releases and `return`
  keeps it (the two tails are merged afterwards).
* **Which local takes a dead argument's stack home.** The first surface out
  parameter reuses the home of an argument already held in a register. In
  `CaptureBackBuffer` this only came out right once the function was written
  flat (early returns) instead of nesting the copy inside `if (... == 0)`.
  Declaration order had no effect.
* **Whole-program alias knowledge.** In `CaptureBackBufferImage` retail
  stores the image size before it loads the surface format and the device.
  With the format and device declared as independent globals the compiler
  moved those loads above the stores. They are members of the render state
  object at 0x00491C28; declaring that object, reading `format` and `device`
  from it, and taking the object's address in the synthetic caller (so a
  store through another pointer may alias it) gives retail's order. The
  device still has to be read through an inline accessor so it is loaded
  ahead of the arguments.

0x00448360 has no caller in the retail image.
