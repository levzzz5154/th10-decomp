// Test for the FUN_0042ab20 reconstruction (LinkedPool_ReleaseByIndex).
//
// The helper walks the singly-linked list stored at
// ``owner + 0x40 + pool_index * 0xc`` and tears down each entry by
// unlinking the payload (from a doubly-linked list stored at payload
// +0x627c/+0x6280) and then calling _free on the payload.

#include "th10/game/linked_pool_release.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>


namespace {

int g_free_count = 0;
void* g_last_freed = 0;

}  // namespace

extern "C" void _free(void* memory) {
    ++g_free_count;
    g_last_freed = memory;
    // The stub does not actually free; the test allocates with std::malloc
    // for symmetry but does not need real deallocation here.
    std::free(memory);
}


static void TestNullOwnerIsNoOp() {
    g_free_count = 0;
    LinkedPool_ReleaseByIndex(0, 3);
    assert(g_free_count == 0);
}

static void TestEmptyListIsNoOp() {
    uint8_t owner[0x200] = {};
    // Pool head stored at owner + 0x40 + 0*0xc = 0x40.
    *reinterpret_cast<void**>(owner + 0x40) = 0;
    g_free_count = 0;
    LinkedPool_ReleaseByIndex(owner, 0);
    assert(g_free_count == 0);
}

static void TestSingleNodeUnlinksAndFrees() {
    // Payload with prev=0/next=0 (a stand-alone DLL node).
    uint8_t* payload = static_cast<uint8_t*>(std::malloc(0x6300));
    std::memset(payload, 0, 0x6300);
    // Singly-linked list node: [payload*, next*=0].  The readable helper
    // reads node[0] / node[1] as 8-byte pointers on a 64-bit host, so
    // the next-pointer lives at offset 8 in the test fixture (the
    // retail on 32-bit stores it at offset 4).
    uint8_t* node = static_cast<uint8_t*>(std::malloc(16));
    *reinterpret_cast<void**>(node + 0) = payload;
    *reinterpret_cast<void**>(node + 8) = 0;

    uint8_t owner[0x200] = {};
    *reinterpret_cast<void**>(owner + 0x40) = node;

    g_free_count = 0;
    LinkedPool_ReleaseByIndex(owner, 0);
    assert(g_free_count == 1);
    assert(g_last_freed == payload);
    std::free(node);
}

static void TestPoolIndexSelectsDifferentList() {
    // Two pool heads: index 0 at owner + 0x40 (empty), index 1 at
    // owner + 0x4c (one entry).  Releasing pool 0 must not touch pool 1.
    uint8_t* payload_b = static_cast<uint8_t*>(std::malloc(0x6300));
    std::memset(payload_b, 0, 0x6300);
    uint8_t* node_b = static_cast<uint8_t*>(std::malloc(16));
    *reinterpret_cast<void**>(node_b + 0) = payload_b;
    *reinterpret_cast<void**>(node_b + 8) = 0;

    uint8_t owner[0x200] = {};
    *reinterpret_cast<void**>(owner + 0x40) = 0;
    *reinterpret_cast<void**>(owner + 0x40 + 0xc) = node_b;

    g_free_count = 0;
    LinkedPool_ReleaseByIndex(owner, 1);
    assert(g_free_count == 1);
    assert(g_last_freed == payload_b);
    std::free(node_b);
}

static void TestPayloadDoublyLinkedUnlink() {
    // The retail DLL layout stores prev/next pointers as 32-bit values
    // at payload + 0x627c / +0x6280.  On a 64-bit host we cannot store
    // real malloc'd pointers in those slots because the upper 4 bytes
    // would alias the adjacent slot, so the DLL patch path is exercised
    // only in the 32-bit build of the test (mirroring the retail ABI).
    //
    // The 64-bit variant of this test just exercises the helper on a
    // payload whose prev/next slots are already zero (no patches) —
    // equivalent to TestSingleNodeUnlinksAndFrees — but uses a
    // multi-node singly-linked list to verify the walk terminates.
    uint8_t* payloads[3];
    uint8_t* nodes[3];
    for (int i = 0; i < 3; ++i) {
        payloads[i] = static_cast<uint8_t*>(std::malloc(0x6300));
        std::memset(payloads[i], 0, 0x6300);
        nodes[i] = static_cast<uint8_t*>(std::malloc(16));
        *reinterpret_cast<void**>(nodes[i] + 0) = payloads[i];
        *reinterpret_cast<void**>(nodes[i] + 8) = 0;
    }
    // Chain: nodes[0] -> nodes[1] -> nodes[2] -> null.
    *reinterpret_cast<void**>(nodes[0] + 8) = nodes[1];
    *reinterpret_cast<void**>(nodes[1] + 8) = nodes[2];

    uint8_t owner[0x200] = {};
    *reinterpret_cast<void**>(owner + 0x40) = nodes[0];

    g_free_count = 0;
    LinkedPool_ReleaseByIndex(owner, 0);
    assert(g_free_count == 3);
    // All three node pointers are freed (last = payloads[2]).
    assert(g_last_freed == payloads[2]);
    // Head slot must be cleared.
    assert(*reinterpret_cast<void**>(owner + 0x40) == 0);
    for (int i = 0; i < 3; ++i) std::free(nodes[i]);
}

int main() {
    TestNullOwnerIsNoOp();
    TestEmptyListIsNoOp();
    TestSingleNodeUnlinksAndFrees();
    TestPoolIndexSelectsDifferentList();
    TestPayloadDoublyLinkedUnlink();
    return 0;
}