// 0x0043DDB0: queue a stop request for one of twelve pending sound effects.
// Native LTCG selects the retail convention: owner in ESI, sound ID in EDI.
// The body also leaves the selected slot (or twelve when full) in EAX.

struct StopQueue_0043ddb0 {
    unsigned char unknown_0000_061f[0x620];
    int pending_sound_indices[12];
    int pending_pan_count[12];

    __declspec(noinline) void QueueEffectStop(int sound_index);
};
typedef char StopQueue_0043ddb0_size_must_match[
    sizeof(StopQueue_0043ddb0) == 0x680 ? 1 : -1];

#pragma code_seg(".text$01stop")
void StopQueue_0043ddb0::QueueEffectStop(int sound_index) {
    int pending = 0;
    int* cursor = pending_sound_indices;
    for (; pending < 12; ++pending, ++cursor) {
        const int existing = *cursor;
        if (existing < 0)
            break;
        if (existing == sound_index)
            goto store_stop;
    }
    if (pending >= 12)
        return;
    pending_sound_indices[pending] = sound_index;
store_stop:
    pending_pan_count[pending] = -1;
}
#pragma code_seg()
