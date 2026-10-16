// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtanim/animation_object_resolve_float_variable.cpp"

extern "C" int* __stdcall ResolveIntegerVariable(
    int* value, unsigned char* object, unsigned char selector, unsigned short mask);

#pragma code_seg(".text$05context")
int __stdcall AnimationVariableResolversContext(
        unsigned char* selectors, float** float_values, int** integer_values,
        unsigned char** objects, unsigned short* masks, int count) {
    int result = 0;
    while (count--) {
        unsigned char selector = *selectors++;
        unsigned short mask = *masks++;
        unsigned char* object = *objects++;
        result += (int)ResolveFloatVariable(selector, *float_values++, object, mask);
        result += (int)ResolveIntegerVariable(*integer_values++, object, selector, mask);
    }
    return result;
}
#pragma code_seg()
