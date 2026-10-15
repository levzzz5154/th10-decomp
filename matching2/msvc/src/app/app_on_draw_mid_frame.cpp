// 0x004200C0: the app's draw task at priority 0x28 (registered by
// 0x00420470); nothing to draw.
extern "C" int __cdecl App_OnDrawMidFrame() {
    return 1;
}
