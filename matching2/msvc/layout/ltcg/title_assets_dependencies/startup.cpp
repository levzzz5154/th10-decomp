// Unselected ABI anchor for 0x0041F8D0. The maintained body in
// src/game/load_startup_resources_0041f8d0.cpp is the same statements as a
// free function; here it is the member the title worker calls, so that the
// whole-program pass sees a receiver the callee never reads.
#pragma code_seg(".text$00startup")
int TitleWorkerOwner::LoadStartupResources() {
    if (!Recovery_LoadCachedResource_00447280(
            6, data_00491c10, (const char *)0x0046D254)) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CB68);
        return -1;
    }
    if (!Recovery_LoadCachedResource_00447280(
            7, data_00491c10, (const char *)0x0046CD88)) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CD54);
        return -1;
    }
    return 0;
}
#pragma code_seg()
