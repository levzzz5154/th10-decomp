// The cluster entry translation unit: the spell-list builder and a stand-in
// for its caller, the 1,968-byte title menu update at 0x00431EE0 that is still
// assembly. The stand-in is compiler context only, not recovered code.
#include "../../../src/game/title/title_spell_list.cpp"

#pragma code_seg(".text$0040a000_context")
extern "C" __declspec(noinline) int __stdcall TitleSpellListCaller(TitleMenu_00431410* menu) {
    return menu->BuildSpellList();
}
#pragma code_seg()
