extern "C" unsigned int g_crt_output_mask;
extern "C" unsigned int g_crt_output_flag;

// 0x00458C25..0x00458C38: Set the masked CRT flag when enabled.
extern "C" void __cdecl crt_unassigned_458c25(unsigned int enabled) {
    g_crt_output_flag = enabled ? g_crt_output_mask : 0;
}
