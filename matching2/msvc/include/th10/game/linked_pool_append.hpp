#ifndef TH10_GAME_LINKED_POOL_APPEND_HPP
#define TH10_GAME_LINKED_POOL_APPEND_HPP

#include <string.h>

struct PoolPage_0042aa50;

// A doubly linked list node that names the page it belongs to.
struct PoolLink_0042aa50 {
    PoolPage_0042aa50* page;             // +0x00
    PoolLink_0042aa50* next;             // +0x04
    PoolLink_0042aa50* previous;         // +0x08
};

// Scratch space of a page; it starts empty.
struct PoolScratch_0042aa50 {
    PoolPage_0042aa50* page;             // +0x0000
    unsigned char buffer[0xE10];         // +0x0004
    unsigned char* cursor;               // +0x0E14

    void Attach(PoolPage_0042aa50* owner) {
        page = owner;
        cursor = buffer;
    }
};

// One 0x6284-byte page of pooled records.
struct PoolPage_0042aa50 {
    unsigned char records[0x5460];
    PoolScratch_0042aa50 scratch;        // +0x5460
    PoolLink_0042aa50 link;              // +0x6278

    PoolPage_0042aa50() {
        memset(this, 0, sizeof(*this));
        scratch.Attach(this);
        link.page = this;
        link.next = 0;
        link.previous = 0;
    }
};
typedef char PoolPageSize_0042aa50[sizeof(PoolPage_0042aa50) == 0x6284 ? 1 : -1];

// The owner keeps one page list per slot.
struct PoolOwner_0042aa50 {
    unsigned char reserved_00[0x3C];
    PoolLink_0042aa50 lists[1];          // +0x3C

    // 0x0042AA50: allocate a page and append it to a slot's list.
    __declspec(noinline) PoolLink_0042aa50* AppendPage(int slot);
};

#endif
