#include "th10/render/device_reset.hpp"
#include "th10/render/game_render_targets.hpp"

extern void* g_pD3DDevice;
extern void* g_pGameStateManager;
extern uint32_t DAT_00474e36;
extern uint32_t DAT_00491fd4;

int D3DDevice_TestCooperativeLevel(void* device);
int D3DDevice_Reset(void* device);
void GameStateManager_DestroyEntitiesForReset(void* manager);
void Render_ReinitializeAfterReset(void);
void Directory_Create(const char* path);
int File_Exists(const char* path);
void Screenshot_Capture(const char* path);

static void BuildSnapshotPath(char* output, int index) {
    const char* prefix = "snapshot/th";
    while (*prefix != 0) {
        *output++ = *prefix++;
    }
    *output++ = (char)('0' + index / 100);
    *output++ = (char)('0' + index / 10 % 10);
    *output++ = (char)('0' + index % 10);
    *output++ = '.';
    *output++ = 'b';
    *output++ = 'm';
    *output++ = 'p';
    *output = 0;
}

// 0x004391F0 - Device-loss recovery and numbered BMP snapshot dispatch.
void Render_HandleDeviceResetAndSnapshot(void) {
    if (D3DDevice_TestCooperativeLevel(g_pD3DDevice) < 0) {
        GameStateManager_DestroyEntitiesForReset(g_pGameStateManager);
        D3DDevice_Reset(g_pD3DDevice);
        Render_ReinitializeAfterReset();
        DAT_00491fd4 = 2;
    }

    GameRenderTargets_Release((GameRenderTargets*)g_pGameStateManager);

    if ((DAT_00474e36 & 0x800) != 0) {
        Directory_Create("snapshot");
        char path[256];
        int index = 0;
        while (index < 1000) {
            BuildSnapshotPath(path, index);
            if (!File_Exists(path)) {
                Screenshot_Capture(path);
                return;
            }
            ++index;
        }
    }
}
