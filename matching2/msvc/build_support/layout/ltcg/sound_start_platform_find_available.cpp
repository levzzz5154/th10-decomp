#pragma code_seg(".text$07find")
__declspec(noinline) PlatformD370Entry*
PlatformInterfaceState::FindAvailable() {
    if (entries_004 == 0)
        return 0;

    unsigned int index = 0;
    for (; index < count_010; ++index) {
        if (entries_004[index] != 0) {
            unsigned int state = 0;
            reinterpret_cast<PlatformD370Entry*>(entries_004[index])
                ->read_state(&state);
            if ((state & 1) == 0)
                break;
        }
    }
    if (index != count_010)
        return reinterpret_cast<PlatformD370Entry*>(entries_004[index]);
    return reinterpret_cast<PlatformD370Entry*>(
        entries_004[(unsigned int)asm_rand_0045371b() % count_010]);
}
#pragma code_seg()
