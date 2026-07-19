// Test for the FUN_0040c540 reconstruction
// (GameStateThread_EnsureAnimationHandle).
//
// The lazy-init contract:
//   - game_thread == 0                  -> no-op
//   - cache already armed (>0)          -> no-op (does not call fetch)
//   - cache zero + fetch_handle == 0    -> no-op
//   - cache zero + fetch_handle present -> cache = fetch_handle(thread)

#include "th10/game/animation_resource_lazy_fetch.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>


namespace {

// Raw byte layout matching the retail offsets (0x8994 and 0x89a4 are
// slot addresses inside the game thread); using a byte buffer keeps
// the test independent of the host ABI.
struct FakeGameThread {
    uint8_t bytes[0x8a00];
};

int g_fetch_count = 0;
void* g_last_thread = 0;

uint32_t StubFetch(void* game_thread) {
    ++g_fetch_count;
    g_last_thread = game_thread;
    return 0xABCD1234u;
}

static uint32_t& CachedHandle(FakeGameThread& t) {
    return *reinterpret_cast<uint32_t*>(t.bytes + 0x89a4);
}

}  // namespace


static void TestNullThreadIsNoOp() {
    g_fetch_count = 0;
    GameStateThread_EnsureAnimationHandle(0, StubFetch);
    assert(g_fetch_count == 0);
}

static void TestNullFetchIsNoOp() {
    FakeGameThread thread;
    std::memset(&thread, 0, sizeof(thread));
    CachedHandle(thread) = 0;
    GameStateThread_EnsureAnimationHandle(&thread, 0);
    assert(CachedHandle(thread) == 0);
}

static void TestAlreadyArmedSkipsFetch() {
    FakeGameThread thread;
    std::memset(&thread, 0, sizeof(thread));
    CachedHandle(thread) = 0x77u;
    g_fetch_count = 0;
    GameStateThread_EnsureAnimationHandle(&thread, StubFetch);
    assert(g_fetch_count == 0);
    assert(CachedHandle(thread) == 0x77u);
}

static void TestLazyInitCallsFetchAndStores() {
    FakeGameThread thread;
    std::memset(&thread, 0, sizeof(thread));
    CachedHandle(thread) = 0;
    g_fetch_count = 0;
    g_last_thread = 0;
    GameStateThread_EnsureAnimationHandle(&thread, StubFetch);
    assert(g_fetch_count == 1);
    assert(g_last_thread == &thread);
    assert(CachedHandle(thread) == 0xABCD1234u);
}

static void TestSecondCallSkipsFetchAfterArming() {
    FakeGameThread thread;
    std::memset(&thread, 0, sizeof(thread));
    g_fetch_count = 0;
    GameStateThread_EnsureAnimationHandle(&thread, StubFetch);
    assert(g_fetch_count == 1);
    // Second call must not re-arm.
    GameStateThread_EnsureAnimationHandle(&thread, StubFetch);
    assert(g_fetch_count == 1);
}

int main() {
    TestNullThreadIsNoOp();
    TestNullFetchIsNoOp();
    TestAlreadyArmedSkipsFetch();
    TestLazyInitCallsFetchAndStores();
    TestSecondCallSkipsFetchAfterArming();
    return 0;
}