#include <string.h>

struct LaserBaseView;
struct ScoreManager_0041c100 {
    unsigned char bytes[0x45C];
};

LaserBaseView* __fastcall Laser_Construct(void*, LaserBaseView* self);
extern "C" ScoreManager_0041c100* g_laser_manager;

__declspec(noinline) ScoreManager_0041c100* InitializeManager_0041c100(
        ScoreManager_0041c100* manager);
#pragma code_seg(".text$00fzmanagerinit")
__declspec(noinline) ScoreManager_0041c100* InitializeManager_0041c100(
        ScoreManager_0041c100* manager) {
    Laser_Construct(0, reinterpret_cast<LaserBaseView*>(manager->bytes + 0x10));
    memset(manager, 0, sizeof(*manager));
    g_laser_manager = manager;
    return manager;
}
#pragma code_seg()
