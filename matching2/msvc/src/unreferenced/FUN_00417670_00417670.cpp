// The global the accessor publishes; the retail body loads it directly.
extern "C" int data_00491fc4;

// 0x00417670: FUN_00417670 - read the published frame counter.
int FUN_00417670() {
    return data_00491fc4;
}
