Resolved on 2026-10-04: the full initializer is now exact ordinary C++. The copied flags value type resolves the ESI/EDI allocation and store-order residual. See `animation_resource_initialize_object_00449870_2026_10_04.md` and its evidence JSON. Historical diagnostics follow.

# 0x00449870 `AnimationResource::InitializeObject` (parked, 2026-10-04)

217 bytes, plain `thiscall` (resource ECX, object and script index on the
stack, `RET 8`). Calls `LoadScriptPreservingState` 0x0043E7E0 with its native
LTCG convention (resource EAX, object EDX, index ECX), so it has to be built in
the `load_script_preserving_state_0043e7e0` cluster, kept public by taking its
address in the context.

## Closest natural source (217 bytes, same instructions, wrong registers in the first two vectors)

```cpp
void AnimationResource::InitializeObject(Entity* object, int index) {
    object->Position() = Vector3Value(0.0f, 0.0f, 0.0f);
    object->BasePosition() = Vector3Value(0.0f, 0.0f, 0.0f);
    object->AnimationFlags() |= 0x40000000;
    object->ScriptIndex() = static_cast<int16_t>(index);
    object->RenderOffset() = Vector3Value(0.0f, 0.0f, 0.0f);
    EntityTail(object)->layer_3a1 = 0x10;
    EntityTail(object)->layer_3a0 = 0x10;
    LoadScriptPreservingState_0043e7e0(this, object, index);
}
```

`Vector3Value` is the constructed vector from `entity_script_start.hpp`; its
by-value float parameters give retail's store/reload of each zero through the
stack. The tail (flag load, `or`, flag store, index load, word store, layer
bytes, call) is identical to retail including its interleaving with the third
vector.

## The remaining difference

Retail writes the first two vectors with the destination in ESI and the value
in EDI, keeps `this` in ECX through them, and emits `mov eax, ecx` just before
the flag load. The source above uses ECX/ESI for the first two vectors and
copies `this` to EAX at entry (`push edi` then appears in the middle).

Traced in c2.dll (`Spillcosts` 0x107A98EE, `ChoosePhysReg` 0x107AAC16, run
under `link.exe` because code generation is at link time): object, `this` and
index are global candidates in EDX, EAX and ECX in every variant. The vector
temporaries are local and may borrow ECX while no candidate is live in it.
Retail's choice appears exactly when the flag word is a *named candidate read
at the top of the function*:

```cpp
unsigned int flags = object->AnimationFlags();   // first statement
... position, base position ...
object->AnimationFlags() = flags | 0x40000000;
```

Then the candidate holds ECX from entry, the temporaries take ESI/EDI, and the
scheduler sinks the load (with the `this` copy) down to the first store it
cannot prove independent. But with direct vector stores the optimizer forwards
the load into the store before allocation (back to the result above), and with
a store through a named pointer (`Vector3* v = &object->BasePosition(); *v =
...`) the load stops in front of that store instead of after the second vector:

| order | first two vectors | flag load position | bytes equal |
| --- | --- | --- | --- |
| natural `|=` | ECX/ESI | after 2nd vector | tail only |
| read first, direct stores | ECX/ESI (forwarded) | after 2nd vector | tail only |
| read first, 2nd vector through pointer | ESI/EDI | after 1st vector | all but the two moved instructions |
| read first, 3rd vector through pointer, flag store after it | ESI/EDI | after 2nd vector | first 30 instructions; `or`/store not interleaved |

So retail needs the flag read to stay a candidate from entry without any store
acting as an alias barrier before the third vector. Not found: twenty statement
orders, bit-field and pointer spellings of the flag update, reference/helper/
member spellings of the vector assignment, early definitions of the index,
inlined helper structures (forced or not) and address-taken versus direct
callers all leave one of the rows above. The same "read flags, write other
fields, write flags | bit" shape is in every caller (0x00448D00 family), where
the explicit temporary is enough because a scalar store sits in between.
