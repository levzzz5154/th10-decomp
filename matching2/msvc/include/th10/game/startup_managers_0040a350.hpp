#pragma once
#include <stddef.h>
#include "th10/game/menu_cursor.hpp"

// Startup state used by the real 0x0040A340 wrapper and 0x0040A350 initializer.
struct FactoryCallerState {
    unsigned char reserved_000[0x30];
    int state_030;
    int *scripts_034;
    unsigned char reserved_038[0x114 - 0x38];
    int script_index_114;
    unsigned char reserved_118[0x1EC - 0x118];
    MenuCursor menu_1ec;

    __declspec(noinline) int InitializeManagers();
};
typedef char StartupState_script_index_is_114[
    offsetof(FactoryCallerState, script_index_114) == 0x114 ? 1 : -1];
typedef char StartupState_menu_is_1ec[
    offsetof(FactoryCallerState, menu_1ec) == 0x1EC ? 1 : -1];
extern "C" FactoryCallerState *data_004776f8;
