#pragma once

#include <string.h>

struct StageTip;

// Intrusive list node embedded at +0x0C in every stage-tip record.
struct StageTipNode {
    StageTip* owner;
    StageTipNode* next;
    StageTipNode* previous;

    __forceinline void Initialize(StageTip* tip) {
        next = 0;
        previous = 0;
        owner = tip;
    }

    void InsertAfter(StageTipNode* node) {
        if (next) {
            node->next = next;
            next->previous = node;
        }
        next = node;
        node->previous = this;
    }

    // Link a node after the last one of the list this node heads.
    void Append(StageTipNode* node) {
        StageTipNode* tail = this;
        while (tail->next)
            tail = tail->next;
        tail->InsertAfter(node);
    }
};

// Parsed stage-tip entry. The retail allocator reserves 0x88 bytes.
struct StageTipPosition {
    float x;
    float y;
    float z;
};

struct StageTip {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        StageTipPosition position;
    };
    StageTipNode node;
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

    StageTip();
};

typedef char StageTip_size_check[sizeof(StageTip) == 0x88 ? 1 : -1];

StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip);
