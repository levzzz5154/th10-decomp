// 0x00438AD0: the game's WinMain.
//
// Start-up (replay table, critical sections, single-instance check, the
// configuration and the start-up dialog), then one pass per program run:
// Direct3D, the window, the sound thread, the device, the animation manager
// and the frame loop, followed by that pass's teardown. A pass that ends with
// exit code 2 (an option that needs a restart was changed) pumps messages for
// sixty rounds and runs again; any other exit writes the configuration and
// the log and leaves.
//
// Written from the retail instructions block by block. It is linked against
// the recovered sources of the routines it calls (the layout's
// context_sources), because the whole-program link passes most of their
// arguments in registers it picks from their bodies.
#include "th10/game/game_main_00438ad0.hpp"
#include "th10/platform/text_log.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/render/d3d_destroy_00438880.hpp"
#include <string.h>

extern "C" {
__declspec(dllimport) void __stdcall InitializeCriticalSection(CriticalSection*);
__declspec(dllimport) void __stdcall DeleteCriticalSection(CriticalSection*);
__declspec(dllimport) void* __stdcall CreateThread(void* security, unsigned int stack_size,
    unsigned long (__stdcall* entry)(void*), void* parameter, unsigned int flags,
    unsigned int* thread_id);
__declspec(dllimport) int __stdcall DialogBoxParamA(void* instance, const char* dialog,
    void* parent, int (__stdcall* procedure)(void*, unsigned int, unsigned int, long),
    long parameter);
__declspec(dllimport) int __stdcall PeekMessageA(Message_00438ad0* message, void* window,
    unsigned int first, unsigned int last, unsigned int remove);
__declspec(dllimport) int __stdcall TranslateMessage(const Message_00438ad0* message);
__declspec(dllimport) long __stdcall DispatchMessageA(const Message_00438ad0* message);
__declspec(dllimport) int __stdcall SetForegroundWindow(void* window);
__declspec(dllimport) int __stdcall ShowWindow(void* window, int command);
__declspec(dllimport) int __stdcall MoveWindow(void* window, int x, int y, int width,
    int height, int repaint);
__declspec(dllimport) int __stdcall DestroyWindow(void* window);
__declspec(dllimport) int __stdcall ShowCursor(int show);
__declspec(dllimport) void* __stdcall SetCursor(void* cursor);
__declspec(dllimport) int __stdcall MessageBoxA(void* window, const char* text,
    const char* caption, unsigned int type);
__declspec(dllimport) int __stdcall SystemParametersInfoA(unsigned int action,
    unsigned int parameter, void* data, unsigned int update);

void __cdecl free(void* block);
int __stdcall asm_WINNLSEnableIME_0045232c(void* window, int enable);
void* __stdcall Direct3DCreate9_00452176(unsigned int sdk_version);
int __cdecl Startup_InstanceCheck_00439ff0();
int __stdcall asm_FUN_00439890_00439890();          // create the Direct3D device
double __cdecl FrameTimer_GetDelta(void);
int __stdcall App_RegisterTasks_00420470();
int __stdcall ShutdownMidi_0043ae20(MidiSequencer* sequencer);
void __stdcall CleanupMidi_0043a910(MidiSequencer* sequencer);

// Log lines (Shift-JIS).
extern char data_0046f77c[];    // "Touhou action log ------ ..."
extern char data_0046f6a0[];    // "the Direct3D object could not be created for some reason"
extern char data_0046f6f0[];    // "an option that needs a restart was changed, restarting"
extern char data_0046f7cc[];    // "------ ..."
}

int __stdcall SaveSystemSettingsRetail_004392e0();
int __stdcall ComputeExecutableChecksum();
int __stdcall StartupDialog_Procedure(void* dialog, unsigned int message,
                                      unsigned int parameter, long detail);
void __stdcall Sound_InitThread();                       // the sound thread
short __stdcall Joystick_Probe_0044a0c0();
void __stdcall Input_NormalizeKeyboardState();
int __stdcall GameFrameAdvance_00439390(GameFrame_00439390* frame);
void __stdcall ReleaseAll_00438a30(Holder_00438a30* holder);
extern "C" SprtCtrlStateCacheView* __cdecl Renderer_ApplyDeviceDefaults(void);

int __fastcall CreateGameWindow_00439730(void* instance);
int __stdcall File_WriteWholeFile(const char* path, const void* buffer, unsigned long size);

struct GameApp_00420870 {
    __declspec(noinline) int LoadConfig(const char* path);
};
// The two diagnostic-log writers keep their own view of the log object.
struct TextLog_0044b8e0 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};
// The routines that build and tear down the two managers, likewise.
struct FuncCtrlInitializeView {
    unsigned char lists[0x48];
    __declspec(noinline) void Initialize();
};
struct AnimationManagerStorage_00446220 {
    __declspec(noinline) ~AnimationManagerStorage_00446220();
};
// The animation manager: built by 0x00445900, torn down by 0x00446220.
struct SprtCtrl {
    unsigned char storage[0x732460];
    SprtCtrl();
    ~SprtCtrl() {
        reinterpret_cast<AnimationManagerStorage_00446220*>(this)->
            ~AnimationManagerStorage_00446220();
    }
};
typedef SprtCtrl AnimationManager_00438ad0;
struct App_00420270 {
    __declspec(noinline) int Shutdown();
};
struct SoundWorkerPair_0043cc40 {
    __declspec(noinline) int Stop();
};
struct WaveSoundManager {
    __declspec(noinline) unsigned int ProcessCommands();
    __declspec(noinline) int Cleanup();
};

// The table of loaded replays: 0x2800 entries and whether any is in use.
struct ReplayTable_00438ad0 {
    void* entries[0x2800];
    int in_use;

    ReplayTable_00438ad0() {
        memset(this, 0, sizeof(*this));
        in_use = 0;
    }
    ~ReplayTable_00438ad0() {
        if (in_use != 0) {
            for (int index = 0; index < 0x2800; ++index) {
                if (entries[index] != 0)
                    free(entries[index]);
            }
        }
    }
};

struct D3DResourceManager_00438ad0 {
    unsigned char lists[0x48];
    D3DResourceManager_00438ad0() {
        reinterpret_cast<FuncCtrlInitializeView*>(this)->Initialize();
    }
    ~D3DResourceManager_00438ad0() {
        reinterpret_cast<FuncCtrlDestroyView*>(this)->
            ~FuncCtrlDestroyView();
    }
};

struct MidiOwner_00438ad0 {
    ~MidiOwner_00438ad0() { CleanupMidi_0043a910(reinterpret_cast<MidiSequencer*>(this)); }
};

// The sound manager at 0x00492590, as far as start-up reaches it.
struct SoundManager_00438ad0 {
    unsigned char reserved_0000[0x5218];
    void* thread;                   // +0x5218
    void* second_thread;            // +0x521C
    unsigned int thread_id;         // +0x5220
    int stop_stage;                 // +0x5224
    void* window;                   // +0x5228
    unsigned char reserved_522c[0x52D0 - 0x522C];

    void Start(void* owner) {
        memset(this, 0, sizeof(*this));
        window = owner;
        thread = CreateThread(0, 0,
            reinterpret_cast<unsigned long (__stdcall*)(void*)>(&Sound_InitThread),
            this, 0, &thread_id);
    }
    void Stop() {
        stop_stage = 2;
        reinterpret_cast<SoundWorkerPair_0043cc40*>(this)->Stop();
        reinterpret_cast<WaveSoundManager*>(this)->Cleanup();
    }
};
typedef char SoundManagerSize_00438ad0[sizeof(SoundManager_00438ad0) == 0x52D0 ? 1 : -1];

extern "C" {
extern ReplayTable_00438ad0* data_00491be0;
extern D3DResourceManager_00438ad0* g_func_ctrl;
extern AnimationManager_00438ad0* g_sprt_ctrl;
extern Application data_00491c28;
extern MainWindow data_004924f0;
extern SoundManager_00438ad0 data_00492590;
extern TextLog_0044b810 data_00474f70;
extern ThreadSynchronization data_00492274;
}

static inline void PumpMessage(Message_00438ad0* message) {
    TranslateMessage(message);
    DispatchMessageA(message);
}

#pragma code_seg(".text$00438ad0_fn")
__declspec(noinline) int __stdcall GameMain_00438ad0(
        void* instance, void* previous, char* command_line, int show) {
    Message_00438ad0 message;
    int exit_code = 0;
    int index;
    CriticalSection* section;

    data_004924f0.instance = instance;
    ReplayTable_00438ad0* replays = new ReplayTable_00438ad0;
    data_00491be0 = replays;
    for (section = data_00492274.critical_sections, index = 7; index != 0; --index, ++section)
        InitializeCriticalSection(section);
    data_00474f70.Append(data_0046f77c);

    if (Startup_InstanceCheck_00439ff0() == -1)
        goto close_pass;
    data_00491c28.instance = instance;
    SaveSystemSettingsRetail_004392e0();
    if (reinterpret_cast<GameApp_00420870*>(&data_00491c28)->LoadConfig("th10.cfg") != 0)
        goto close_pass;
    if (data_00491c28.config.flags & 0x100) {
        // The start-up dialog: "run full screen?"; 6 is its Yes button.
        data_00491c28.config.field_1d = DialogBoxParamA(instance,
            reinterpret_cast<const char*>(0xCB), 0, &StartupDialog_Procedure, 0) != 6;
    }
    ComputeExecutableChecksum();

    for (;;) {
        D3DResourceManager_00438ad0* resources = new D3DResourceManager_00438ad0;
        g_func_ctrl = resources;
        data_00491c28.direct3d = static_cast<Direct3D*>(Direct3DCreate9_00452176(0x20));
        if (data_00491c28.direct3d == 0) {
            reinterpret_cast<TextLog_0044b8e0*>(&data_00474f70)->AppendLine(data_0046f6a0);
            goto close_pass;
        }
        if (CreateGameWindow_00439730(instance) != 0)
            goto close_pass;
        data_00492590.Start(data_004924f0.window);
        if (asm_FUN_00439890_00439890() != 0)
            goto close_pass;
        Joystick_Probe_0044a0c0();
        Input_NormalizeKeyboardState();
        AnimationManager_00438ad0* animations = new AnimationManager_00438ad0;
        g_sprt_ctrl = animations;
        if (!data_00491c28.config.field_1d) {
            asm_WINNLSEnableIME_0045232c(0, 0);
            ShowCursor(0);
            SetCursor(0);
        }
        data_004924f0.previous_time = 0.0;
        data_004924f0.start_time = data_004924f0.target_time =
            data_004924f0.frame_time = data_004924f0.previous_time = FrameTimer_GetDelta();
        SetForegroundWindow(data_004924f0.window);

        exit_code = App_RegisterTasks_00420470();
        if (exit_code != 0) {
            if (exit_code != -1)
                exit_code = 2;
        } else {
            exit_code = 0;
            data_004924f0.cursor_state = 0xFC;
            while (!data_004924f0.quit) {
                if (PeekMessageA(&message, 0, 0, 0, 1)) {
                    PumpMessage(&message);
                    continue;
                }
                long state = data_00491c28.device->TestCooperativeLevel();
                if (state == 0) {
                    exit_code = GameFrameAdvance_00439390(
                        reinterpret_cast<GameFrame_00439390*>(&data_004924f0));
                    if (exit_code != 0)
                        break;
                    data_00491c28.flags &= ~0x10u;
                } else if (state == 0x88760869) {
                    // D3DERR_DEVICENOTRESET
                    ReleaseAll_00438a30(reinterpret_cast<Holder_00438a30*>(g_sprt_ctrl));
                    if (data_00491c28.device->Reset(&data_00491c28.present_parameters) != 0)
                        break;
                    Renderer_ApplyDeviceDefaults();
                    data_00491c28.mode = 3;
                    data_00491c28.flags |= 0x10;
                }
            }
        }

        reinterpret_cast<App_00420270*>(&data_00491c28)->Shutdown();
        delete g_func_ctrl;
        g_func_ctrl = 0;
        while (reinterpret_cast<WaveSoundManager*>(&data_00492590)->ProcessCommands() != 0) {
        }
close_pass:
        data_00492590.Stop();
        delete g_sprt_ctrl;
        g_sprt_ctrl = 0;
        if (data_00491c28.device != 0) {
            data_00491c28.device->Reset(&data_00491c28.present_parameters);
            if (data_00491c28.device != 0) {
                data_00491c28.device->Release();
                data_00491c28.device = 0;
            }
        }
        if (data_00491c28.direct3d != 0) {
            data_00491c28.direct3d->Release();
            data_00491c28.direct3d = 0;
        }
        if (data_004924f0.window != 0) {
            ShowWindow(data_004924f0.window, 0);
            MoveWindow(data_004924f0.window, 0, 0, 0, 0, 0);
            DestroyWindow(data_004924f0.window);
            data_004924f0.window = 0;
        }
        ShowCursor(1);
        if (exit_code != 2)
            break;

        // Start the log over for the next run.
        TextLog_0044b810* log = &data_00474f70;
        log->cursor = log->text;
        log->text[0] = 0;
        log->Append(data_0046f6f0);
        if (!data_00491c28.config.field_1d)
            asm_WINNLSEnableIME_0045232c(0, 1);
        for (index = 0; index < 60; ++index) {
            if (PeekMessageA(&message, 0, 0, 0, 1))
                PumpMessage(&message);
        }
    }

    File_WriteWholeFile("th10.cfg", &data_00491c28.config, 0x34);
    if (data_00491c28.midi != 0) {
        ShutdownMidi_0043ae20(reinterpret_cast<MidiSequencer*>(data_00491c28.midi));
        delete data_00491c28.midi;
        data_00491c28.midi = 0;
    }
    if (data_00474f70.cursor != data_00474f70.text) {
        data_00474f70.Append(data_0046f7cc);
        if (data_00474f70.dirty)
            MessageBoxA(0, data_00474f70.text, "log", 0x10);
        File_WriteWholeFile("./log.txt", data_00474f70.text, strlen(data_00474f70.text));
    }
    for (section = data_00492274.critical_sections, index = 7; index != 0; --index, ++section)
        DeleteCriticalSection(section);
    SystemParametersInfoA(0x11, data_004924f0.saved_parameters[0], 0, 2);
    SystemParametersInfoA(0x55, data_004924f0.saved_parameters[1], 0, 2);
    SystemParametersInfoA(0x56, data_004924f0.saved_parameters[2], 0, 2);
    asm_WINNLSEnableIME_0045232c(0, 1);
    delete data_00491be0;
    return 0;
}
#pragma code_seg()

// The link's entry: the one caller the whole-program link sees.
extern "C" int __stdcall RigEntry(void* instance, int show) {
    return GameMain_00438ad0(instance, 0, 0, show);
}
