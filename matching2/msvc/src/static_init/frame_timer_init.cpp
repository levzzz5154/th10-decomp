// 0x004658C0: dynamic initializer of the global frame timer at 0x00474C54:
// point its delta at the default game speed (0x00476F78) and mark it set up.

extern "C" int g_frame_timer_flags;
extern "C" int g_frame_timer_list;

extern "C" void __cdecl StaticInit_FrameTimer(void) {
    g_frame_timer_flags &= ~1;
    if ((g_frame_timer_flags & 1) == 0) {
        int live = g_frame_timer_flags | 1;
        g_frame_timer_list = 0x476F78;
        g_frame_timer_flags = live;
    }
}
