#pragma once

#include <string.h>

struct HintData;

// Intrusive list node embedded at +0x0C in every hint record.
struct HintDataNode {
    HintData* owner;
    HintDataNode* next;
    HintDataNode* previous;

    __forceinline void Initialize(HintData* tip) {
        next = 0;
        previous = 0;
        owner = tip;
    }

    void InsertAfter(HintDataNode* node) {
        if (next) {
            node->next = next;
            next->previous = node;
        }
        next = node;
        node->previous = this;
    }

    // Link a node after the last one of the list this node heads.
    void Append(HintDataNode* node) {
        HintDataNode* tail = this;
        while (tail->next)
            tail = tail->next;
        tail->InsertAfter(node);
    }
};

// Parsed hint entry. The retail allocator reserves 0x88 bytes.
struct HintDataPosition {
    float x;
    float y;
    float z;
};

struct HintData {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        HintDataPosition position;
    };
    HintDataNode node;
    unsigned char reserved_018[4];
    char name[0x40];
    unsigned char reserved_05C[4];
    int display_value;
    int display_zero;
    int display_mode;
    int duration;
    int selection;
    unsigned char reserved_074[8];
    float scale;
    unsigned int rendered_width;
    int state;

    HintData();
};

typedef char HintData_size_check[sizeof(HintData) == 0x88 ? 1 : -1];

HintData* __fastcall HintData_Initialize(void* unused, HintData* tip);
