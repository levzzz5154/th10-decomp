// Behavioral checks for the maintained MSVC source. Exact compiler bytes are
// verified separately; this harness tests the recurrence and observable API.
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>

#include "th10/math/rng.hpp"

static void check(bool condition, unsigned int seed, const char* contract) {
    if (!condition) {
        std::fprintf(stderr, "seed 0x%04X: %s\n", seed, contract);
        std::abort();
    }
}

// Reverse the transformation established by 0x0044B9B0..0x0044B9D6.
// Division/remainder undo the two-bit rotation, then modular addition undoes
// subtraction. This oracle never computes the production forward recurrence.
static unsigned int previous_word(unsigned int output) {
    const unsigned int unrotated = output / 4 + (output % 4) * 16384;
    return ((unrotated + 0x6553) % 65536) ^ 0x9630;
}

static void check_pair(unsigned int seed, unsigned int packed,
                       const RngState& state) {
    const unsigned int first = packed >> 16;
    const unsigned int second = packed & 65535;
    check(previous_word(first) == seed, seed, "first packed word");
    check(previous_word(second) == first, seed, "second packed word");
    check(state.seed == second, seed, "final state of two-word generation");
    check(state.reserved == 0xA55A, seed, "reserved field preserved");
}

static void test_all_seeds() {
    bool seen[65536] = {};
    for (unsigned int seed = 0; seed < 65536; ++seed) {
        RngState word = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        const unsigned short next = word.NextWord();
        check(previous_word(next) == seed, seed, "inverse of one-word step");
        check(!seen[next], seed, "transition is a permutation");
        seen[next] = true;
        check(word.seed == next && word.generation == 0, seed,
              "one-word state and counter wrap");
        check(word.reserved == 0xA55A, seed, "one-word reserved field");

        RngState two = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        const unsigned int packed = Rng_NextU32(&two);
        check_pair(seed, packed, two);
        check(two.generation == 1, seed, "two-word counter wrap");

        RngState alternate = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        check(Rng_NextU32Alternate(&alternate) == packed, seed,
              "alternate entry output");
        check(alternate.seed == two.seed && alternate.generation == 1 &&
              alternate.reserved == 0xA55A, seed, "alternate entry state");

        RngState four = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        const unsigned int reversed_pair = Rng_NextU32DoubleStep(&four);
        const unsigned int first = reversed_pair & 65535;
        const unsigned int second = reversed_pair >> 16;
        check(previous_word(first) == seed, seed, "four-step first word is low");
        check(previous_word(second) == first, seed, "four-step second word is high");
        check(previous_word(previous_word(four.seed)) == second, seed,
              "four-step final state advances past returned pair");
        check(four.generation == 3 && four.reserved == 0xA55A, seed,
              "four-step counter wrap and reserved field");
    }
    for (unsigned int output = 0; output < 65536; ++output)
        check(seen[output], output, "every 16-bit output is reachable");
}

struct CounterCase {
    unsigned int initial;
    unsigned int after_one;
    unsigned int after_two;
    unsigned int after_four;
};

static void test_counter_boundaries_and_sequence() {
    const CounterCase cases[] = {
        {0, 1, 2, 4},
        {0x7FFFFFFE, 0x7FFFFFFF, 0x80000000u, 0x80000002u},
        {0x7FFFFFFF, 0x80000000u, 0x80000001u, 0x80000003u},
        {0xFFFFFFFCu, 0xFFFFFFFDu, 0xFFFFFFFEu, 0},
        {0xFFFFFFFDu, 0xFFFFFFFEu, 0xFFFFFFFFu, 1},
        {0xFFFFFFFEu, 0xFFFFFFFFu, 0, 2},
        {0xFFFFFFFFu, 0, 1, 3}
    };
    for (unsigned int i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        const CounterCase& count = cases[i];
        RngState initial = {0, 0xA55A, count.initial};
        RngState state = initial;
        check(state.NextWord() == 0xC374 && state.generation == count.after_one,
              0, "one-word count boundary and zero-seed vector");
        state = initial;
        check(Rng_NextU32(&state) == 0xC374BFC7u &&
              state.generation == count.after_two, 0, "two-word count boundary");
        state = initial;
        check(Rng_NextU32Alternate(&state) == 0xC374BFC7u &&
              state.generation == count.after_two, 0, "alternate count boundary");
        state = initial;
        check(Rng_NextU32DoubleStep(&state) == 0xBFC7C374u &&
              state.generation == count.after_four, 0, "four-word count boundary");
        state = initial;
        Rng_NextFloat(&state);
        check(state.generation == count.after_two, 0, "unit-float count boundary");
        state = initial;
        Rng_NextFloatSigned(&state);
        check(state.generation == count.after_two, 0, "signed-float count boundary");
    }

    // Zero-seed vectors also recorded in game_runtime_test.cpp. Mixing APIs
    // checks continued state ownership instead of only freshly seeded calls.
    RngState state = {0, 0xA55A, 0};
    check(Rng_NextU32(&state) == 0xC374BFC7u, 0, "sequence first pair");
    check(Rng_NextU32Alternate(&state) == 0x12937D40u, 0, "sequence second pair");
    check(Rng_NextU32(&state) == 0x1876A3CCu, 0, "sequence third pair");
    check(state.generation == 6 && state.seed == 0xA3CC, 0, "sequence final state");
    state.seed = 0;
    state.generation = 0;
    check(Rng_NextU32DoubleStep(&state) == 0xBFC7C374u && state.seed == 0x7D40,
          0, "four-step sequence returns first pair");
    check(Rng_NextU32(&state) == 0x1876A3CCu && state.generation == 6,
          0, "sequence resumes after four words");
}

static unsigned int float_bits(float value) {
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}

// Encode magnitude / 2^scale directly as IEEE binary32, rounding the discarded
// integer bits to nearest, ties to even. No floating arithmetic or production
// RNG helper participates in this expected-value calculation.
static unsigned int dyadic_float_bits(unsigned int magnitude, int scale,
                                     bool negative) {
    if (magnitude == 0)
        return 0;
    unsigned int top_bit = 0;
    for (unsigned int remaining = magnitude; remaining > 1; remaining >>= 1)
        ++top_bit;
    unsigned int significand;
    if (top_bit <= 23) {
        significand = magnitude << (23 - top_bit);
    } else {
        const unsigned int discarded_bits = top_bit - 23;
        significand = magnitude >> discarded_bits;
        const unsigned int remainder = magnitude % (1u << discarded_bits);
        const unsigned int halfway = 1u << (discarded_bits - 1);
        if (remainder > halfway || (remainder == halfway && (significand & 1)))
            ++significand;
        if (significand == 0x1000000) {
            significand >>= 1;
            ++top_bit;
        }
    }
    const unsigned int exponent = static_cast<int>(top_bit) - scale + 127;
    return (negative ? 0x80000000u : 0) | (exponent << 23) |
           (significand & 0x7FFFFF);
}

static void test_float_contracts() {
    // Basic oracle cases cover exact values, both tie directions, and a carry
    // into the exponent. The RNG comparisons below span every possible seed.
    assert(dyadic_float_bits(0, 32, false) == 0);
    assert(dyadic_float_bits(0x80000000u, 32, false) == 0x3F000000);
    assert(dyadic_float_bits(0x80000080u, 32, false) == 0x3F000000);
    assert(dyadic_float_bits(0x80000180u, 32, false) == 0x3F000002);
    assert(dyadic_float_bits(0xFFFFFFFFu, 32, false) == 0x3F800000);
    assert(dyadic_float_bits(0x80000000u, 31, true) == 0xBF800000u);

    unsigned int high_half = 0;
    unsigned int low_half = 0;
    for (unsigned int seed = 0; seed < 65536; ++seed) {
        RngState integers = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        const unsigned int packed = Rng_NextU32(&integers);
        check_pair(seed, packed, integers);

        RngState unit = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        const unsigned int unit_bits = float_bits(Rng_NextFloat(&unit));
        check(unit_bits == dyadic_float_bits(packed, 32, false), seed,
              "unit-float unsigned conversion and final rounding");
        check(unit.seed == integers.seed && unit.generation == 1 &&
              unit.reserved == 0xA55A, seed, "unit-float state advances two words");

        // u / 2^31 - 1 is exactly (u - 2^31) / 2^31 before the final store.
        const bool negative = packed < 0x80000000u;
        const unsigned int magnitude = negative ? 0x80000000u - packed
                                                : packed - 0x80000000u;
        if (negative)
            ++low_half;
        else
            ++high_half;
        RngState centered = {static_cast<unsigned short>(seed), 0xA55A, UINT_MAX};
        check(float_bits(Rng_NextFloatSigned(&centered)) ==
              dyadic_float_bits(magnitude, 31, negative), seed,
              "signed-float retains precision through subtraction");
        check(centered.seed == integers.seed && centered.generation == 1 &&
              centered.reserved == 0xA55A, seed, "signed-float state advances two words");
    }
    // The unsigned-conversion correction is needed for exactly half the seeds.
    assert(low_half == 32768 && high_half == 32768);
}

int main() {
    assert(CHAR_BIT == 8 && sizeof(unsigned short) == 2 && sizeof(unsigned int) == 4);
    assert(sizeof(RngState) == 8 && offsetof(RngState, generation) == 4);
    assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559);
    const unsigned int endian_check = 1;
    assert(*reinterpret_cast<const unsigned char*>(&endian_check) == 1);
    test_all_seeds();
    test_counter_boundaries_and_sequence();
    test_float_contracts();
}
