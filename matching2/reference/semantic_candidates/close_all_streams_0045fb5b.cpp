// 0x0045FB5B..0x0045FBF5: close every active CRT stream and release dynamic
// stream records. The first 20 records are statically owned.
extern "C" unsigned char data_004981d4;
extern "C" int data_004991e0;
extern "C" unsigned char data_004660bc;

extern "C" void __cdecl asm_lock_00453c0c(int lock_number);
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int lock_number);
extern "C" int __cdecl asm_unassigned_00461458(void* stream);
extern "C" void __cdecl asm_free_00452422(void* memory);

typedef void (__stdcall *DeleteCriticalSection_0045fb5b)(void* section);

extern "C" int __cdecl asm_target_0045fb5b(void) {
    int closed_count = 0;
    asm_lock_00453c0c(1);

    __try {
        for (int index = 3; index < data_004991e0; ++index) {
            unsigned char** streams = *(unsigned char***)&data_004981d4;
            unsigned char* stream = streams[index];
            if (stream == 0)
                continue;

            if ((stream[0x0c] & 0x83) != 0 &&
                asm_unassigned_00461458(stream) != -1) {
                ++closed_count;
            }

            if (index >= 20) {
                // Closing a stream can update its table entry, so reload it.
                streams = *(unsigned char***)&data_004981d4;
                stream = streams[index];
                DeleteCriticalSection_0045fb5b destroy =
                    *(DeleteCriticalSection_0045fb5b*)&data_004660bc;
                destroy(stream + 0x20);
                streams = *(unsigned char***)&data_004981d4;
                asm_free_00452422(streams[index]);
                streams = *(unsigned char***)&data_004981d4;
                streams[index] = 0;
            }
        }
    } __finally {
        asm_FUN_00453b3f_00453b3f(1);
    }

    return closed_count;
}
