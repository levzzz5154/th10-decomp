/* 0x00452422..0x00452492: Visual C++ 7.1 CRT free.  Its __finally
 * funclet occupies 0x00452475..0x0045247D inside this 113-byte contribution. */
extern int data_00499344;
extern void* data_00499340;
extern void __cdecl asm_lock_00453c0c(int lock_number);
extern void* __cdecl asm_sbh_find_block_00453c9a(void* block);
extern void __cdecl asm_sbh_free_block_00453cc5(void* header, void* block);
extern void __cdecl asm_FUN_00453b3f_00453b3f(int lock_number);
extern int (__stdcall *imp_HeapFree)(void* heap, unsigned long flags, void* block);

void __cdecl free_00452422(void* block) {
    int result = 0;
    if (block == 0) {
        return;
    }
    if (data_00499344 == 3) {
        void* header;
        asm_lock_00453c0c(4);
        __try {
            if ((header = asm_sbh_find_block_00453c9a(block)) != 0) {
                asm_sbh_free_block_00453cc5(header, block);
            }
        }
        __finally {
            asm_FUN_00453b3f_00453b3f(4);
        }
        if (header == 0) {
            result = imp_HeapFree(data_00499340, 0, block);
        }
    } else {
        result = imp_HeapFree(data_00499340, 0, block);
    }
}
