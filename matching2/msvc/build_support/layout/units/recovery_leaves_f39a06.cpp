#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
RecoverySmallState::RecoverySmallState() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    *(void**)&g_ending = this;
}
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "../../../src/game/ending/recovery_create_small_state.cpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "../../../src/game/enemy/enemy_deleting_destructor.cpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
#include "../../../src/game/mother/recovery_release_global_states.cpp"
#include "th10/source_views/recovery_leaves_f39a06_5.hpp"
#include "../../../src/core/sprtlib/recovery_load_cached_resource.cpp"
#include "th10/source_views/recovery_leaves_f39a06_6.hpp"
#include "../../../src/core/zwave/platform_owned_array_deleting_destructor.cpp"


