#include <cassert>

#define __declspec(attribute)
#define __stdcall
#define __cdecl
#define __fastcall
#include "../msvc/src/game/input_pattern_count.cpp"

signed char g_input_pattern_table[110];

int main() {
    for (int index = 0; index < 110; ++index)
        g_input_pattern_table[index] = (signed char)(index % 7 - 3);

    assert(InputPattern_CountMatches(0, -3) == 16);
    assert(InputPattern_CountMatches((void*)0x1234, 0) == 16);
    assert(InputPattern_CountMatches(0, 3) == 15);
    assert(InputPattern_CountMatches(0, 99) == 0);

    for (int index = 0; index < 110; ++index)
        g_input_pattern_table[index] = (signed char)0x80;
    assert(InputPattern_CountMatches(0, -128) == 110);
    assert(InputPattern_CountMatches(0, 128) == 0);
}
