#ifndef TH10_GAME_LINKED_POOL_APPEND_HPP
#define TH10_GAME_LINKED_POOL_APPEND_HPP

#include <string.h>

struct PoolPage;

// A doubly linked list node that names the page it belongs to.
struct PoolLink {
    PoolPage* page;             // +0x00
    PoolLink* next;             // +0x04
    PoolLink* previous;         // +0x08
};

// Scratch space of a page; it starts empty.
struct PoolScratch {
    PoolPage* page;             // +0x0000
    unsigned char buffer[0xE10];         // +0x0004
    unsigned char* cursor;               // +0x0E14

    void Attach(PoolPage* owner) {
        page = owner;
        cursor = buffer;
    }
};

// One 0x6284-byte page of pooled records.
struct PoolPage {
    unsigned char records[0x5460];
    PoolScratch scratch;        // +0x5460
    PoolLink link;              // +0x6278

    PoolPage() {
        memset(this, 0, sizeof(*this));
        scratch.Attach(this);
        link.page = this;
        link.next = 0;
        link.previous = 0;
    }
};
typedef char PoolPageSize[sizeof(PoolPage) == 0x6284 ? 1 : -1];

// The owner keeps one page list per slot.
struct PoolOwner {
    unsigned char reserved_00[0x3C];
    PoolLink lists[1];          // +0x3C

    // 0x0042AA50: allocate a page and append it to a slot's list.
    __declspec(noinline) PoolLink* AppendPage(int slot);
};

#endif
