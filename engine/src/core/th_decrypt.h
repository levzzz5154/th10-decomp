#pragma once
#include <cstdint>
#include <cstddef>
#include "th10/types.h"

namespace th10 {

void th_decrypt(uint8_t* data, size_t size, uint8_t key, uint8_t step, uint32_t block, uint32_t limit);

} // namespace th10
