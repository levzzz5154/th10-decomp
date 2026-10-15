// The global the accessor publishes; the retail body loads it directly.
extern "C" int g_stage_flags;

// 0x00417670: FUN_00417670 - read the published frame counter.
int FUN_00417670() {
    return g_stage_flags;
}
