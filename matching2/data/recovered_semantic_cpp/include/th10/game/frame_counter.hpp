#pragma once
struct FrameCounterPair {
    int previous;
    int current;
    int AtInterval(int interval);
};
typedef char FrameCounterPair_size_check[sizeof(FrameCounterPair) == 8 ? 1 : -1];
