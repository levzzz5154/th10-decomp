#pragma once

// A 0xD8-byte counter block: cleared counts, a 999 limit and an enabled flag.
// The constructor's store order is the one retail's inlined copies show.
struct CounterBlock {
    int value;
    int unknown_04;
    int limit;
    unsigned char unknown_0c[0x80];
    int total;
    unsigned char unknown_090[0x40];
    int enabled;
    int elapsed;

    __forceinline CounterBlock() {
        total = 0;
        value = 0;
        elapsed = 0;
        enabled = 1;
        limit = 999;
    }
};
typedef char CounterBlock_size_check[sizeof(CounterBlock) == 0xD8 ? 1 : -1];
