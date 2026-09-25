// 0x0040D400..0x0040D4EE: load the ANIM chunk in a script file.
//
// The retail entry is a normal x86 thiscall: the loader object arrives in ECX,
// the chunk pointer is the single stack argument, and the function returns an
// int in EAX with RET 4.  The object is opaque here; the code only reads its
// vtable to dispatch the ECL body names through slot 2.
#include "asm_symbols.hpp"

struct CachedResource {
    unsigned char unknown_000[0x124];
    int busy;
};

extern CachedResource* __fastcall Recovery_LoadCachedResource(
    int index, void* cache, const char* name);

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    char* Append(char* format, ...);
};

// 0x0040CD20 is ScriptFileLoader::Load.  The receiver and string use the
// ordinary __thiscall layout (ECX plus one stack argument); the loader returns
// with RET 4.  Slot 2 is observed in the 0x0046D0B4 dispatch table.
typedef int (__fastcall *ScriptLoadMethod_0040d400)(
    void* receiver, void* unused_edx, const char* name);

struct ScriptFileChunkContext_0040d400 {
    int ParseAnimationChunk(char* chunk);
};

__declspec(noinline) int
ScriptFileChunkContext_0040d400::ParseAnimationChunk(char* chunk) {
    unsigned char* const bytes = reinterpret_cast<unsigned char*>(chunk);
    if (*reinterpret_cast<unsigned int*>(bytes) != 0x4D494E41u) // 'ANIM'
        return 0;

    const unsigned int resource_count =
        *reinterpret_cast<unsigned int*>(bytes + 4);
    unsigned char* name = bytes + 8;

    for (unsigned int i = 0; i != resource_count; ++i) {
        CachedResource* const resource =
            Recovery_LoadCachedResource(
                static_cast<int>(i + 9u),
                *reinterpret_cast<void**>(&data_00491c10),
                reinterpret_cast<const char*>(name));
        unsigned char* const resource_manager =
            *reinterpret_cast<unsigned char**>(&data_00477704);
        CachedResource** const resource_slots =
            reinterpret_cast<CachedResource**>(resource_manager + 0x34);
        resource_slots[i] = resource;
        if (resource == 0) {
            reinterpret_cast<TextLog_0044b810*>(0x00474F70)->Append(
                reinterpret_cast<char*>(0x0046CB68));
            return -1;
        }

        do {
            ++name;
        } while (name[-1] != 0);
    }

    // The optional ECLI chunk starts at the next 4-byte offset relative to the
    // beginning of the ANIM chunk, after the counted NUL-terminated names.
    const unsigned int consumed = static_cast<unsigned int>(name - bytes);
    const unsigned int padding = (0u - consumed) & 3u;
    const unsigned char* const ecli = name + padding;
    if (*reinterpret_cast<const unsigned int*>(ecli) != 0x494C4345u) // 'ECLI'
        return 0;

    const unsigned int script_count =
        *reinterpret_cast<const unsigned int*>(ecli + 4);
    const char* script_name = reinterpret_cast<const char*>(ecli + 8);
    void* const receiver = this;
    void** const vtable = *reinterpret_cast<void***>(receiver);
    const ScriptLoadMethod_0040d400 load_script =
        reinterpret_cast<ScriptLoadMethod_0040d400>(vtable[2]);

    for (unsigned int i = 0; i != script_count; ++i) {
        load_script(receiver, 0, script_name);
        do {
            ++script_name;
        } while (script_name[-1] != '\0');
    }

    return 0;
}
