#include "th10/game/player.hpp"

#include <cassert>
#include <cstdint>

namespace {

std::int32_t& PowerAt(std::uint8_t* player) {
    return *reinterpret_cast<std::int32_t*>(player + 0x58);
}

void TestDeltas() {
    alignas(std::int32_t) std::uint8_t storage[0x60] = {};
    PowerAt(storage) = 0;

    Player_AdjustPower(storage, 7);
    assert(PowerAt(storage) == 7);
    Player_AdjustPower(storage, -3);
    assert(PowerAt(storage) == 4);
    Player_AdjustPower(storage, -0x404);
    assert(PowerAt(storage) == -0x400);

    PowerAt(storage) = 0;
    Player_AdjustPower(storage, 0x401);
    assert(PowerAt(storage) == 0x400);
}

void TestClampBoundaries() {
    alignas(std::int32_t) std::uint8_t storage[0x60] = {};

    PowerAt(storage) = 0x3FF;
    Player_AdjustPower(storage, 1);
    assert(PowerAt(storage) == 0x400);
    Player_AdjustPower(storage, 1);
    assert(PowerAt(storage) == 0x400);

    PowerAt(storage) = -0x3FF;
    Player_AdjustPower(storage, -1);
    assert(PowerAt(storage) == -0x400);
    Player_AdjustPower(storage, -1);
    assert(PowerAt(storage) == -0x400);
}

}  // namespace

int main() {
    TestDeltas();
    TestClampBoundaries();
    return 0;
}
