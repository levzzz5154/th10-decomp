# Landing a region through the native-LTCG cluster path

2026-09-18. The procedure that landed `0x0042C850`, `0x00449590`, `0x004495E0`
and `0x00449670`, written down so the next attempt does not rediscover it. The
pitfalls behind steps 4-6 are in `ltcg_cluster_lessons.md`.

## When to use it

A region needs the cluster when its entry register is not expressible in a plain
translation unit — object in EAX, `this` in EDI, and the like — or when an
otherwise unrepresentable call convention has to be reached. It is *not* a way to
change allocator-pressure or scheduling residuals; for those the plain build is
what retail matches.

Model the function as a **member** of its data type: the compiler then emits
`this` in ECX, and the whole-program pass moves it to EAX when the synthetic
caller's shape makes that the cheapest register.

## Procedure

1. **Replace the region's assembly in its source file.** The cluster compiles the
   whole source, so any other `__declspec(naked)` function in the same file would
   be emitted too and the loader rejects undeclared contributions. If the file
   holds other regions, move the model to its own file and point the manifest's
   `source` for that region at it.
2. **Wrap the function in `#pragma code_seg(".text$01accessor")` … `#pragma
   code_seg()`.** Without it the function lands in the default `.text` and the
   entry point collapses.
3. **Write the layout** `matching2/msvc/layout/ltcg/<name>.json` and the driver
   `…_context.cpp`. The driver includes the source and defines a synthetic caller
   that walks an array of objects and calls the function in a loop — that shape is
   what establishes the register convention. The `context.symbol` must be the
   **decorated** name the compiler will actually emit; verify it from a build if
   unsure. Keep a positive gap between the function and the context (16 bytes is
   safe).
4. **Bind opaquely-called assembly callees.** Declare them `extern "C"
   __fastcall` with the argument order retail uses — `__fastcall` gives ECX, EDX,
   then stack, which is what the animation-manager calls need — and bind the
   mangled name the declaration produces (e.g. `@AnimationManager_Find_004491c0@12`)
   in the layout's `absolute_symbols` with `"kind": "relative_code"`. The
   declaration fixes the registers; the binding fixes the address.
5. **Register**: `python3 matching2/tools/waves/register_cluster.py --layout
   layout/ltcg/<name>.json --apply` (run from `matching2/msvc`).
6. **Probe**: `python3 matching2/tools/matching/probe.py --source <source>
   --project matching2/msvc`. Expect `EXACT`. If the extent differs, the layout's
   declared `size` must be raised to the emitted one, and the context address and
   gap recomputed; the probe's `--json` report gives the honest
   `different_bytes` count — the first difference alone has repeatedly overstated
   how close a model was.
7. **Gate**: `make` (about five minutes). It must print `Whole EXE exact:
   487,936 bytes.`; semantic C++ should rise by exactly the region's size.
8. Commit with the region, its layout and its driver, and push.

## Iterating safely

Do the exploration in a throwaway copy (`cp -a matching2/msvc /tmp/<name>/msvc`)
so the maintained tree is never left in a broken state; only the final, verified
edit goes into the real tree. `cluster_region.py` in the same copy drives a
variant sweep and rolls the registration back automatically, and it resets the
layout file per variant so an adaptive size fix cannot leak between attempts.
