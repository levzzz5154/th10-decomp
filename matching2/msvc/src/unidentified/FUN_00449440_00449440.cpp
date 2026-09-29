// The draw dispatcher receives the entity in EAX and its manager in ECX.
// Its first instruction replaces EDX, so that register can pass through
// unchanged while the wrapper loads the manager from the global.
extern "C" void* data_00491c10;
extern "C" __attribute__((regparm(3))) int
asm_FUN_004451c0_004451c0(void* entity, unsigned int unused_edx, void* manager);

extern "C" __attribute__((regparm(2), noinline, used,
                           section(".text$global_draw_00449440"), aligned(1)))
int DrawGlobalAnimation_00449440(void* entity, unsigned int unused_edx) {
    return asm_FUN_004451c0_004451c0(entity, unused_edx, data_00491c10);
}
