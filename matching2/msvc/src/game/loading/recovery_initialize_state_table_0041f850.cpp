// Exact state-table constructor, shared with the factory closure.
#include "th10/game/state_table_0041f850.hpp"

#pragma code_seg(".text$00bstatector")
__declspec(noinline) StateTable_0041f850::StateTable_0041f850() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_00477820 = this;
}
#pragma code_seg()
