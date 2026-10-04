#pragma once
struct Int2 {
    int x, y;
    Int2() {}
    Int2(int x, int y) : x(x), y(y) {}
    __declspec(noinline) Int2 operator+(const Int2&) const;
};

typedef char Int2Size[sizeof(Int2) == 8 ? 1 : -1];
