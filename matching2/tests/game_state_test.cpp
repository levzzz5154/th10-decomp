#include "th10/game/game_state.hpp"

#include <cassert>
#include <cstdlib>

uint32_t DAT_00476f78;
uint32_t DAT_004776e4;
uint32_t DAT_004776e8;
uint32_t DAT_00474c7c;
uint32_t DAT_00474ca0;
uint32_t DAT_00491be4;
uint32_t DAT_00491d7c[0x46];
void* ExceptionList;
void* g_pGameStateManager;
uint32_t DAT_00492274;
uint8_t DAT_0049231c;

extern "C" void* operator_new(uint32_t size) {
    return std::malloc(size);
}

extern "C" void _free(void* allocation) {
    std::free(allocation);
}

extern "C" void _eh_vector_constructor_iterator_(
    void*, uint32_t, uint32_t, void*, void*) {}
extern "C" void _eh_vector_destructor_iterator_(
    void*, uint32_t, uint32_t, void*) {}

void __fastcall Entity_Constructor(Entity*) {}
void __fastcall Entity_Destructor(Entity*) {}
void __fastcall Entity_Init(void*, Entity*) {}

int GameState_InitializeRenderResources(void*) { return 1; }
void Platform_LogMessage(const char*) {}
void Render_UpdateCameraMatrices(void) {}
void Scheduler_UnregisterCallback(void*, int) {}
void ResourceManager_DestroyContents(void*) {}
extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

int GameState_Update(GameState*) { return 0; }
int GameState_Draw(GameState*) { return 0; }
int GameState_AfterDraw(GameState*) { return 0; }

static void TestStateZeroPreservesCurrentStateOnDeviceFailure() {
    GameState state = {};
    DAT_004776e4 = 0x11111111u;
    DAT_004776e8 = 0x22222222u;

    assert(GameState_Init(0, &state, 0) == -1);
    assert(DAT_004776e4 == 0x11111111u);
    assert(DAT_004776e8 == (uint32_t)&state);
}

static void TestNonzeroStateReplacesCurrentStateOnDeviceFailure() {
    GameState state = {};
    DAT_004776e4 = 0x11111111u;
    DAT_004776e8 = 0x22222222u;

    assert(GameState_Init(0, &state, 3) == -1);
    assert(DAT_004776e4 == (uint32_t)&state);
    assert(DAT_004776e8 == 0x22222222u);
}

int main() {
    TestStateZeroPreservesCurrentStateOnDeviceFailure();
    TestNonzeroStateReplacesCurrentStateOnDeviceFailure();
    return 0;
}
