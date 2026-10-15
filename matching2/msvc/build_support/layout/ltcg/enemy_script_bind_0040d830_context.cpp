#include "../../../src/game/enemy/fun_0040d830_0040d830.cpp"
#include "enemy_script_bind_resolve_anchor.cpp"
// Unselected array caller: keep the receiver live through repeated binds so
// LTCG chooses the retail ESI receiver and leaves the name aggregate on stack.
#pragma code_seg(".text$70context")
EnemyScriptEntity* __stdcall EnemyScriptBindCompilerContext_0040d830(
        EnemyScriptEntity** entities, BindScriptName* labels, int count, int unused) {
    EnemyScriptEntity* result = 0;
    for (int index = 0; index < count; ++index)
        result = InitializeEnemyScriptEntity(unused, entities[index], labels[index]);
    return result;
}
#pragma code_seg()
