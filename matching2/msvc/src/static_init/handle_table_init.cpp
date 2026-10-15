// 0x004659A0: dynamic initializer of the 128-entry handle table at 0x00492998;
// every slot starts at -1.

extern "C" int g_handle_table[0x80];

extern "C" void __cdecl StaticInit_HandleTable(void) {
    for (int index = 0; index < 0x80; ++index)
        g_handle_table[index] = -1;
}
