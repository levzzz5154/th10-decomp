// Source-only semantic model for retail 0x00424480.
//
// This entry receives its output descriptor in ESI in the game binary. The
// function below instead takes every value as an ordinary explicit C++
// parameter; it is not an ABI bridge and does not reproduce RET 0x14.

struct AnimationLookupNode_00424480 {
    void* object; // +0: registered object
    AnimationLookupNode_00424480* next; // +4: next node in this bucket
};

struct AnimationLookupContext_00424480 {
    unsigned char reserved_000000[0x72DAD4];
    AnimationLookupNode_00424480* primary_bucket; // +0x72DAD4
    unsigned int unknown_72DAD8;
    AnimationLookupNode_00424480* secondary_bucket; // +0x72DADC
};

extern "C" unsigned char data_00491c10;

namespace {

AnimationLookupContext_00424480* CurrentAnimationLookupContext_00424480() {
    return *reinterpret_cast<AnimationLookupContext_00424480**>(
        &data_00491c10);
}

void* FindAnimationObject_00424480(
        AnimationLookupContext_00424480* context, int handle) {
    if (handle == 0)
        return 0;

    for (AnimationLookupNode_00424480* node = context->primary_bucket;
         node != 0; node = node->next) {
        if (*static_cast<int*>(node->object) == handle)
            return node->object;
    }

    for (AnimationLookupNode_00424480* node = context->secondary_bucket;
         node != 0; node = node->next) {
        if (*static_cast<int*>(node->object) == handle)
            return node->object;
    }

    return 0;
}

int ConvertResourceFloat_00424480(const unsigned char* resource,
                                  unsigned int field_offset) {
    const float value = *reinterpret_cast<const float*>(resource + field_offset);
    return static_cast<int>(value);
}

} // namespace

// Ordinary C++ callable signature for semantic integration:
//   descriptor, handle, and the four dwords written at descriptor +0x08..+0x14.
// The names remain offset-based because their higher-level meanings are not
// established by the retail helper alone.
extern "C" int UpdateSpriteDescriptorModel_00424480(
        void* descriptor, int handle, int value_08, int value_0C,
        int value_10, int value_14) {
    AnimationLookupContext_00424480* const context =
        CurrentAnimationLookupContext_00424480();
    unsigned char* const animation = static_cast<unsigned char*>(
        FindAnimationObject_00424480(context, handle));

    // Retail reads the resource and performs all four __ftol2 conversions
    // before checking whether the destination slot is already occupied.
    unsigned char* const resource =
        *reinterpret_cast<unsigned char**>(animation + 0x394);
    const int converted_30 = ConvertResourceFloat_00424480(resource, 0x30);
    const int converted_34 = ConvertResourceFloat_00424480(resource, 0x34);
    const int converted_0C = ConvertResourceFloat_00424480(resource, 0x0C);
    const int converted_08 = ConvertResourceFloat_00424480(resource, 0x08);

    int* const words = static_cast<int*>(descriptor);
    if (words[1] >= 0) // descriptor +0x04: signed availability guard
        return -1;

    unsigned int* const stored_handle =
        *reinterpret_cast<unsigned int**>(animation + 0x308);

    // Keep the observed retail store order. These names identify byte offsets,
    // not verified semantic fields.
    words[1] = static_cast<int>(*stored_handle); // +0x04
    words[2] = value_08;                         // +0x08
    words[6] = converted_08;                     // +0x18
    words[3] = value_0C;                         // +0x0C
    words[4] = value_10;                         // +0x10
    words[9] = converted_30;                     // +0x24
    words[7] = converted_0C;                     // +0x1C
    words[5] = value_14;                         // +0x14
    words[8] = converted_34;                     // +0x20
    words[10] = 0;                               // +0x28
    return 0;
}
