#include "th10/game/gameplay_final_runtime.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>

std::uint32_t DAT_00476f78 = 0x3F800000u;

template <typename T>
void Store(std::vector<unsigned char>& bytes, std::size_t offset, T value) {
    std::memcpy(bytes.data() + offset, &value, sizeof(value));
}

template <typename T>
T Load(const std::vector<unsigned char>& bytes, std::size_t offset) {
    T value{};
    std::memcpy(&value, bytes.data() + offset, sizeof(value));
    return value;
}

int main() {
    std::vector<unsigned char> player(0x4478, 0);
    std::vector<unsigned char> table(0x200, 0);

    // The retail bridge reads pair A at +0x20 and pair B at +0x98, with
    // twelve-byte rows selected by the difficulty offset table. Difficulty 1
    // at counter 20 selects row 0 for focused shot zero.
    Store<float>(table, 0x20, -32.0f);
    Store<float>(table, 0x24, 8.0f);
    Store<float>(table, 0x98, 30.0f);
    Store<float>(table, 0x9C, 40.0f);
    Store<std::uint32_t>(player, 0x45C,
                         static_cast<std::uint32_t>(
                             reinterpret_cast<std::uintptr_t>(table.data())));
    Store<int>(player, 0x43AC, 321);
    Store<int>(player, 0x43B0, 654);
    Store<int>(player, 0x4474, 1);  // retail focus latch

    th10::gameplay_final::AttachedEffects state{};
    state.difficulty = 1;
    state.shot = 0;
    state.formation.focus = true;
    th10::gameplay_final::UpdateAttachedEffectsRetail(
        player.data(), state, 20);

    assert(state.formation.table_offsets_valid);
    assert(state.familiar_slots[0].position_x == 321);
    assert(state.familiar_slots[0].position_y == 654);
    assert(state.familiar_slots[0].random[0] == 3000);
    assert(state.familiar_slots[0].random[1] == 4000);
    assert(state.familiar_slots[0].callback_address == 0x00427950u);
    assert(Load<std::uint32_t>(player, 0x3330) == 0x00427950u);
    return 0;
}
