// Compile the maintained C++98 string implementation. Grow, exceptions and
// heap release are scripted boundaries, not reconstructions tested here.
// The byte-exact MSVC build separately verifies the 32-bit object layout.
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "th10/util/heap.hpp"

enum BoundaryError { RangeError, LengthError, GrowthError };
struct GrowthCall {
    LegacyString* string;
    uint32_t requested;
    uint32_t old_length;
};

static std::map<void*, size_t> allocations;
static std::vector<GrowthCall> growth_calls;
static std::string events;
static bool fail_growth;
static unsigned int allocation_calls;
static unsigned int free_calls;
static LegacyString* reset_observer;
static void* reset_old_buffer;
static uint32_t reset_old_length;
static uint32_t reset_old_capacity;
static std::string reset_expected_prefix;

static void record(const char* event) {
    if (!events.empty()) events += ',';
    events += event;
}

static void reset_events() {
    events.clear();
    growth_calls.clear();
    allocation_calls = 0;
    free_calls = 0;
    fail_growth = false;
    assert(reset_observer == 0);
}

static char* allocate_buffer(uint32_t capacity) {
    char* buffer = static_cast<char*>(std::malloc(static_cast<size_t>(capacity) + 1));
    assert(buffer && allocations.insert(std::make_pair(buffer, capacity + 1)).second);
    std::memset(buffer, 0xCD, capacity + 1);
    ++allocation_calls;
    record("allocate");
    return buffer;
}

extern "C" void __cdecl entry_free_004524a1(void* memory) {
    std::map<void*, size_t>::iterator found = allocations.find(memory);
    assert(found != allocations.end());
    if (reset_observer) {
        // Reset overlays its old heap pointer with inline bytes. The free
        // argument must still be the saved pointer, and copying must be done.
        assert(memory == reset_old_buffer);
        assert(reset_observer->length == reset_old_length);
        assert(reset_observer->capacity == reset_old_capacity);
        assert(std::memcmp(reset_observer->storage.inline_data,
                           reset_expected_prefix.data(),
                           reset_expected_prefix.size()) == 0);
        reset_observer = 0;
    }
    std::memset(memory, 0xDD, found->second);
    allocations.erase(found);
    std::free(memory);
    ++free_calls;
    record("free");
}

// Supply a deliberately simple successful growth policy. Only the requested
// size, old length, data preservation and error propagation are under test;
// retail's allocation-size policy remains in unrecovered assembly.
void LegacyString::Grow(uint32_t requested, uint32_t old_length) {
    const GrowthCall call = {this, requested, old_length};
    growth_calls.push_back(call);
    record("grow");
    assert(requested > capacity && old_length == length);
    if (fail_growth || requested > 4096)
        throw GrowthError;
    char* buffer = allocate_buffer(requested);
    std::memcpy(buffer, Data(), old_length + 1);
    if (capacity >= 16)
        entry_free_004524a1(storage.heap_data);
    storage.heap_data = buffer;
    capacity = requested;
}

void LegacyString::ThrowLengthError() const {
    record("length-error");
    throw LengthError;
}

extern "C" void __cdecl LegacyString_ThrowOutOfRange() {
    record("range-error");
    throw RangeError;
}

struct Fixture {
    LegacyString value;

    explicit Fixture(const std::string& text, uint32_t requested_capacity = 15) {
        value.allocator_cookie = 0x1234ABCD;
        value.length = static_cast<uint32_t>(text.size());
        value.capacity = requested_capacity < text.size()
            ? static_cast<uint32_t>(text.size()) : requested_capacity;
        if (value.capacity < 16)
            value.capacity = 15;
        if (value.capacity >= 16)
            value.storage.heap_data = allocate_buffer(value.capacity);
        std::memcpy(value.Data(), text.data(), text.size());
        value.Data()[text.size()] = 0;
    }

    ~Fixture() {
        if (value.capacity >= 16)
            entry_free_004524a1(value.storage.heap_data);
    }

private:
    Fixture(const Fixture&);
    Fixture& operator=(const Fixture&);
};

static void expect(const LegacyString& value, const std::string& text) {
    assert(value.allocator_cookie == 0x1234ABCD);
    assert(value.length == text.size() && value.Length() == text.size());
    assert(value.capacity >= value.length);
    assert(value.Data()[value.length] == 0);
    assert(std::string(value.Data(), value.length) == text);
    if (value.capacity < 16)
        assert(value.Data() == value.storage.inline_data);
    else
        assert(value.Data() == value.storage.heap_data &&
               allocations.count(value.storage.heap_data) == 1);
}

static void expect_growth(LegacyString* value, uint32_t old_length,
                          uint32_t old_capacity, uint32_t requested) {
    if (old_capacity < requested) {
        assert(growth_calls.size() == 1);
        assert(growth_calls[0].string == value);
        assert(growth_calls[0].old_length == old_length);
        assert(growth_calls[0].requested == requested);
        assert(events == (old_capacity >= 16 ? "grow,allocate,free" : "grow,allocate"));
        assert(allocation_calls == 1 && free_calls == (old_capacity >= 16 ? 1u : 0u));
    } else {
        assert(events.empty() && growth_calls.empty());
        assert(allocation_calls == 0 && free_calls == 0);
        assert(value->capacity == old_capacity);
    }
}

static void test_assignment_and_storage() {
    const std::string originals[] = {"", "short", std::string(15, 'i'), std::string(24, 'h')};
    const std::string replacements[] = {
        "", "x", std::string(15, 'a'), std::string(16, 'b'), std::string(47, 'c'),
        std::string("A\0B\0C", 5)
    };
    for (unsigned int i = 0; i < sizeof(originals) / sizeof(originals[0]); ++i) {
        for (unsigned int j = 0; j < sizeof(replacements) / sizeof(replacements[0]); ++j) {
            for (unsigned int roomy = 0; roomy < 2; ++roomy) {
                Fixture fixture(originals[i], roomy ? 64 : 15);
                LegacyString& value = fixture.value;
                const uint32_t old_capacity = value.capacity;
                reset_events();
                assert(value.AssignRange(replacements[j].data(), replacements[j].size()) == &value);
                std::string expected = originals[i];
                expected.assign(replacements[j].data(), replacements[j].size());
                expect(value, expected);
                expect_growth(&value, originals[i].size(), old_capacity, expected.size());
            }
        }
    }

    Fixture fixture("old", 40);
    const char text[] = "first\0ignored";
    reset_events();
    assert(fixture.value.Assign(text) == &fixture.value);
    expect(fixture.value, std::string(text));
    assert(fixture.value.capacity == 40 && events.empty());
    // Assign counts to the first NUL; AssignRange can retain embedded NULs.
    assert(fixture.value.AssignRange(text, sizeof(text) - 1) == &fixture.value);
    expect(fixture.value, std::string(text, sizeof(text) - 1));
    assert(events.empty());
}

static void test_substrings_and_overlap() {
    const std::string originals[] = {
        "", "0123456789abcde", "abcdefghijklmnopqrstuvwxyz0123456789",
        std::string("a\0bc\0def", 8)
    };
    const uint32_t counts[] = {0, 1, 4, 15, 100, 0xFFFFFFFFu};
    for (unsigned int i = 0; i < sizeof(originals) / sizeof(originals[0]); ++i) {
        const std::string& original = originals[i];
        for (uint32_t offset = 0; offset <= original.size(); ++offset) {
            for (unsigned int j = 0; j < sizeof(counts) / sizeof(counts[0]); ++j) {
                const size_t count = counts[j] == 0xFFFFFFFFu ? std::string::npos : counts[j];
                const std::string expected = original.substr(offset, count);
                Fixture self(original);
                const uint32_t old_capacity = self.value.capacity;
                char* const old_data = self.value.Data();
                reset_events();
                assert(self.value.AssignSubstring(&self.value, offset, counts[j]) == &self.value);
                expect(self.value, expected);
                assert(self.value.Data() == old_data && self.value.capacity == old_capacity);
                assert(events.empty());

                Fixture source(original);
                Fixture external("destination");
                reset_events();
                assert(external.value.AssignSubstring(&source.value, offset, counts[j]) == &external.value);
                expect(external.value, expected);
                expect(source.value, original);
                expect_growth(&external.value, 11, 15, expected.size());

                // Interior input has substring semantics even for a count
                // beyond the end, including UINT_MAX. It must not reach Grow
                // or ThrowLengthError before the overlap has been recognized.
                if (offset < original.size()) {
                    Fixture overlap(original);
                    reset_events();
                    assert(overlap.value.AssignRange(overlap.value.Data() + offset, counts[j]) ==
                           &overlap.value);
                    expect(overlap.value, expected);
                    assert(events.empty());
                }
            }
        }
        Fixture pointer_checks(original, 64);
        LegacyString& value = pointer_checks.value;
        for (uint32_t offset = 0; offset < original.size(); ++offset)
            assert(value.OwnsPointer(value.Data() + offset));
        assert(!value.OwnsPointer(value.Data() + value.length));
        assert(!value.OwnsPointer(value.Data() + value.capacity));
        reset_events();
        assert(value.AssignRange(value.Data() + value.length, 0) == &value);
        expect(value, "");
        assert(events.empty() && value.capacity == 64);
    }

    Fixture interior_c_string("prefix-suffix");
    reset_events();
    assert(interior_c_string.value.Assign(interior_c_string.value.Data() + 7) ==
           &interior_c_string.value);
    expect(interior_c_string.value, "suffix");
    assert(events.empty());
}

static void test_erase_and_range_errors() {
    const std::string originals[] = {"", "abcdef", std::string("ab\0cdefghijklmnopq", 18)};
    const uint32_t counts[] = {0, 1, 3, 100, 0xFFFFFFFFu};
    for (unsigned int i = 0; i < sizeof(originals) / sizeof(originals[0]); ++i) {
        for (uint32_t offset = 0; offset <= originals[i].size(); ++offset) {
            for (unsigned int j = 0; j < sizeof(counts) / sizeof(counts[0]); ++j) {
                Fixture fixture(originals[i]);
                char* const old_data = fixture.value.Data();
                const uint32_t old_capacity = fixture.value.capacity;
                std::string expected = originals[i];
                expected.erase(offset, counts[j] == 0xFFFFFFFFu ? std::string::npos : counts[j]);
                reset_events();
                assert(fixture.value.Erase(offset, counts[j]) == &fixture.value);
                expect(fixture.value, expected);
                assert(events.empty() && fixture.value.Data() == old_data);
                assert(fixture.value.capacity == old_capacity);
            }
        }
    }

    const uint32_t invalid_offsets[] = {7, 0xFFFFFFFFu};
    for (unsigned int i = 0; i < 2; ++i) {
        for (unsigned int zero_count = 0; zero_count < 2; ++zero_count) {
            const uint32_t count = zero_count ? 0 : 0xFFFFFFFFu;
            Fixture fixture("abcdef", 40);
            reset_events();
            try {
                fixture.value.Erase(invalid_offsets[i], count);
                assert(false);
            } catch (BoundaryError error) {
                assert(error == RangeError);
            }
            expect(fixture.value, "abcdef");
            assert(events == "range-error" && allocation_calls == 0 && free_calls == 0);

            Fixture source("abcdef");
            reset_events();
            try {
                fixture.value.AssignSubstring(&source.value, invalid_offsets[i], count);
                assert(false);
            } catch (BoundaryError error) {
                assert(error == RangeError);
            }
            expect(fixture.value, "abcdef");
            expect(source.value, "abcdef");
            assert(events == "range-error" && growth_calls.empty());

            reset_events();
            try {
                fixture.value.AssignSubstring(&fixture.value, invalid_offsets[i], count);
                assert(false);
            } catch (BoundaryError error) {
                assert(error == RangeError);
            }
            expect(fixture.value, "abcdef");
            assert(events == "range-error");
        }
    }
}

static void test_length_checks_and_growth_failures() {
    Fixture fixture("unchanged");
    const char external[] = "external";
    reset_events();
    try {
        fixture.value.AssignRange(external, 0xFFFFFFFFu);
        assert(false);
    } catch (BoundaryError error) {
        assert(error == LengthError);
    }
    expect(fixture.value, "unchanged");
    assert(events == "length-error" && growth_calls.empty());

    // The largest admitted count must reach Grow, whose scripted failure
    // prevents allocation or access to an impossibly large input buffer.
    reset_events();
    try {
        fixture.value.AssignRange(external, 0xFFFFFFFEu);
        assert(false);
    } catch (BoundaryError error) {
        assert(error == GrowthError);
    }
    assert(events == "grow" && growth_calls.size() == 1);
    assert(growth_calls[0].requested == 0xFFFFFFFEu && growth_calls[0].old_length == 9);
    expect(fixture.value, "unchanged");

    const std::string longer(50, 'x');
    for (unsigned int substring = 0; substring < 2; ++substring) {
        Fixture source(longer);
        reset_events();
        fail_growth = true;
        try {
            if (substring)
                fixture.value.AssignSubstring(&source.value, 3, 40);
            else
                fixture.value.Assign(longer.c_str());
            assert(false);
        } catch (BoundaryError error) {
            assert(error == GrowthError);
        }
        assert(events == "grow" && allocation_calls == 0 && free_calls == 0);
        assert(growth_calls.size() == 1 && growth_calls[0].old_length == 9);
        assert(growth_calls[0].requested == (substring ? 40u : 50u));
        expect(fixture.value, "unchanged");
        expect(source.value, longer);
    }

    // Metadata-only boundary probe: the length error must happen before any
    // read of the synthetic source's unavailable UINT_MAX bytes.
    Fixture synthetic("x");
    synthetic.value.length = 0xFFFFFFFFu;
    reset_events();
    try {
        fixture.value.AssignSubstring(&synthetic.value, 0, 0xFFFFFFFFu);
        assert(false);
    } catch (BoundaryError error) {
        assert(error == LengthError);
    }
    assert(events == "length-error" && growth_calls.empty());
    expect(fixture.value, "unchanged");
    synthetic.value.length = 1;
}

static void test_reset_storage_order() {
    const std::string original("abc\0defghijklmnopqrstuvwxyz", 27);
    const uint32_t lengths[] = {0, 1, 7, 15};
    for (unsigned int i = 0; i < sizeof(lengths) / sizeof(lengths[0]); ++i) {
        Fixture fixture(original, 48);
        reset_events();
        reset_observer = &fixture.value;
        reset_old_buffer = fixture.value.storage.heap_data;
        reset_old_length = fixture.value.length;
        reset_old_capacity = fixture.value.capacity;
        reset_expected_prefix = original.substr(0, lengths[i]);
        fixture.value.ResetInlineStorage(true, lengths[i]);
        assert(reset_observer == 0);
        expect(fixture.value, reset_expected_prefix);
        assert(fixture.value.capacity == 15);
        assert(events == "free" && free_calls == 1 && allocation_calls == 0);

        Fixture already_inline("abcdefghijklmno");
        reset_events();
        already_inline.value.ResetInlineStorage(true, lengths[i]);
        expect(already_inline.value, std::string("abcdefghijklmno").substr(0, lengths[i]));
        assert(events.empty() && already_inline.value.capacity == 15);
    }

    LegacyString unbuilt;
    std::memset(&unbuilt, 0xA5, sizeof(unbuilt));
    unbuilt.allocator_cookie = 0x1234ABCD;
    reset_events();
    unbuilt.ResetInlineStorage(false, 0);
    expect(unbuilt, "");
    assert(unbuilt.capacity == 15 && events.empty());
    assert(allocation_calls == 0 && free_calls == 0);
}

int main() {
    test_assignment_and_storage();
    assert(allocations.empty());
    test_substrings_and_overlap();
    assert(allocations.empty());
    test_erase_and_range_errors();
    assert(allocations.empty());
    test_length_checks_and_growth_failures();
    assert(allocations.empty());
    test_reset_storage_order();
    assert(allocations.empty());
}
