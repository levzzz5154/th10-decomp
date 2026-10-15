// 0x0042AF90: free the pair held by the global at 0x47783C, then the record
// itself, then clear the global.
extern "C" void* g_score;
extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void __cdecl entry_free_004524a1(void* memory);
extern "C" void FlushHolder_0042af90(void) {
    void** record = (void**)g_score;
    if (record) {
        if (record[0]) { entry_free_00452422(record[0]); record[0] = 0; }
        if (record[1]) { entry_free_00452422(record[1]); record[1] = 0; }
        entry_free_004524a1(record);
    }
    g_score = 0;
}
