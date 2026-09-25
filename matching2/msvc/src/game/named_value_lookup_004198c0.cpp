// 0x004198C0..0x0041991F: look a name up in a table of name/value pairs and
// return the matching value, or zero when no entry matches. Native LTCG
// passes the key in EDX; the table and entry count stay on the stack.
#include <string.h>

struct NamedValue_004198c0 {
    const char* name;
    int value;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) int FindNamedValue_004198c0(
        const char* name, const NamedValue_004198c0* table, int count) {
    for (int index = 0; index < count; ++index) {
        if (strcmp(name, table[index].name) == 0)
            return table[index].value;
    }
    return 0;
}
#pragma code_seg()
