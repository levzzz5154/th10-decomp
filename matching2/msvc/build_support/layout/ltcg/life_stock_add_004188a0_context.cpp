// Compiler context only; never selected as recovered game code.
#include "th10/game/life_stock_add.hpp"
#include "recovery_script_executor_anchor_43dc90.cpp"
#include "../../contexts/legacy/game/life_stock_add.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall LifeStockAddContext(const int* amounts, int count) {
    for (int index = 0; index < count; ++index)
        g_globals.AddLives(amounts[index]);
    for (int index = 0; index < count; ++index)
        g_globals.AddPower(amounts[index]);
    return count;
}
#pragma code_seg()
#pragma inline_depth()
