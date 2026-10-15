
struct EclFrame;

int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame, int selector, int value);

struct EclSource { unsigned char pad_000[4]; void* field_004; };

__declspec(noinline) int Resolve_0040c670(int selector, EclSource* source, int value);

#pragma code_seg(".text$01resolve")
__declspec(noinline) int Resolve_0040c670(int selector, EclSource* source, int value) {
    return ECL_ResolveIntValue_0044ff00(selector, (EclFrame*)source->field_004, selector, value);
}
#pragma code_seg()
