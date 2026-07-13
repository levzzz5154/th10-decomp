#include "th10/archive/lzss.hpp"

// Keep this harness free of host standard-library headers: the game headers
// intentionally model MSVC 7.1's 32-bit fundamental typedefs.
extern "C" void* malloc(unsigned long size);
extern "C" void free(void* memory);

extern "C" void* _malloc(uint32_t size) {
    return malloc((unsigned long)size);
}

class BitWriter {
public:
    BitWriter() : size_(0), bit_(0) {}

    void Bit(bool set) {
        if (bit_ == 0) {
            bytes_[size_++] = 0;
        }
        if (set) {
            bytes_[size_ - 1] |= (uint8_t)(0x80 >> bit_);
        }
        bit_ = (bit_ + 1) & 7;
    }

    void Bits(uint32_t value, uint32_t mask) {
        while (mask != 0) {
            Bit((value & mask) != 0);
            mask >>= 1;
        }
    }

    void Literal(uint8_t value) {
        Bit(true);
        Bits(value, 0x80);
    }

    void BackReference(uint32_t offset, uint32_t length_code) {
        Bit(false);
        Bits(offset, 0x1000);
        Bits(length_code, 8);
    }

    void End() {
        Bit(false);
        Bits(0, 0x1000);
    }

    const uint8_t* Bytes() const { return bytes_; }
    int32_t Size() const { return size_; }

private:
    uint8_t bytes_[64];
    int32_t size_;
    uint32_t bit_;
};

static bool Equal(const uint8_t* left, const char* right, uint32_t size) {
    for (uint32_t index = 0; index < size; ++index) {
        if (left[index] != (uint8_t)right[index]) {
            return false;
        }
    }
    return true;
}

static bool TestLiteralsAndAllocation() {
    BitWriter encoded;
    encoded.Literal('H');
    encoded.Literal('E');
    encoded.Literal('L');
    encoded.Literal('L');
    encoded.Literal('O');
    encoded.End();

    uint8_t* decoded = Dat_LzssDecompress(
        encoded.Bytes(), encoded.Size(), 0, 5);
    bool passed = decoded != 0 && Equal(decoded, "HELLO", 5);
    free(decoded);
    return passed;
}

static bool TestOverlappingBackReference() {
    BitWriter encoded;
    encoded.Literal('A');
    encoded.Literal('B');
    encoded.BackReference(1, 1); // four bytes copied from dictionary offset 1
    encoded.End();

    uint8_t decoded[6] = {0};
    uint8_t* result = Dat_LzssDecompress(
        encoded.Bytes(), encoded.Size(), decoded, sizeof(decoded));
    return result == decoded && Equal(decoded, "ABABAB", sizeof(decoded));
}

int main() {
    if (!TestLiteralsAndAllocation()) {
        return 1;
    }
    if (!TestOverlappingBackReference()) {
        return 2;
    }
    return 0;
}
