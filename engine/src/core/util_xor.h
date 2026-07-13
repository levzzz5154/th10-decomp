#pragma once
#include <cstdint>
#include <cstddef>

namespace th10 {

void util_xor(uint8_t* data, size_t size, uint8_t key, uint8_t step1, uint8_t step2);

} // namespace th10
