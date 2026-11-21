/* 0x00452422..0x00452492: Visual C++ 7.1 CRT free.  Its __finally
 * funclet occupies 0x00452475..0x0045247D inside this 113-byte contribution. */
extern int g_crt_heap_type;
extern void* g_crt_heap_handle;
extern void __cdecl crt_lock(int lock_number);
extern void* __cdecl crt_sbh_find_block(void* block);
extern void __cdecl crt_sbh_free_block(void* header, void* block);
extern void __cdecl crt_unlock(int lock_number);
extern int (__stdcall *imp_HeapFree)(void* heap, unsigned long flags, void* block);

void __cdecl free2(void* block) {
    int result = 0;
    if (block == 0) {
        return;
    }
    if (g_crt_heap_type == 3) {
        void* header;
        crt_lock(4);
        __try {
            if ((header = crt_sbh_find_block(block)) != 0) {
                crt_sbh_free_block(header, block);
            }
        }
        __finally {
            crt_unlock(4);
        }
        if (header == 0) {
            result = imp_HeapFree(g_crt_heap_handle, 0, block);
        }
    } else {
        result = imp_HeapFree(g_crt_heap_handle, 0, block);
    }
}
