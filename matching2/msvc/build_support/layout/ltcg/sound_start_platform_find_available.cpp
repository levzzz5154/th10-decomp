#pragma code_seg(".text$07find")
__declspec(noinline) WaveSecondaryBufferStatus*
SoundBufferPool::GetFreeBuffer() {
    if (entries_004 == 0)
        return 0;

    unsigned int index = 0;
    for (; index < count_010; ++index) {
        if (entries_004[index] != 0) {
            unsigned int state = 0;
            reinterpret_cast<WaveSecondaryBufferStatus*>(entries_004[index])
                ->read_state(&state);
            if ((state & 1) == 0)
                break;
        }
    }
    if (index != count_010)
        return reinterpret_cast<WaveSecondaryBufferStatus*>(entries_004[index]);
    return reinterpret_cast<WaveSecondaryBufferStatus*>(
        entries_004[(unsigned int)crt_rand() % count_010]);
}
#pragma code_seg()
