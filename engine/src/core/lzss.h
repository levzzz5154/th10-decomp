#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

namespace th10 {

std::vector<uint8_t> lzss_decompress(const uint8_t* data, size_t size, size_t output_size);

} // namespace th10
