#include <string.h>

struct ScoreObject;
struct ScoreManager_0041c100 {
    unsigned char bytes[0x45C];
};

ScoreObject* __fastcall ScoreObject_Initialize(void*, ScoreObject* self);
extern "C" ScoreManager_0041c100* g_laser_manager;

__declspec(noinline) ScoreManager_0041c100* InitializeManager_0041c100(
        ScoreManager_0041c100* manager);
#pragma code_seg(".text$00fzmanagerinit")
__declspec(noinline) ScoreManager_0041c100* InitializeManager_0041c100(
        ScoreManager_0041c100* manager) {
    ScoreObject_Initialize(0, reinterpret_cast<ScoreObject*>(manager->bytes + 0x10));
    memset(manager, 0, sizeof(*manager));
    g_laser_manager = manager;
    return manager;
}
#pragma code_seg()
