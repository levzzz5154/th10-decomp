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
extern char str_log_header[];    // "Touhou action log ------ ..."
extern char str_d3d_create_failed[];    // "the Direct3D object could not be created for some reason"
extern char str_restart_required[];    // "an option that needs a restart was changed, restarting"
extern char str_log_footer[];    // "------ ..."
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
extern ReplayTable_00438ad0* g_replay_table;
extern D3DResourceManager_00438ad0* g_func_ctrl;
extern AnimationManager_00438ad0* g_sprt_ctrl;
extern Application g_application;
extern MainWindow g_main_window;
extern SoundManager_00438ad0 g_sound_manager;
extern TextLog_0044b810 g_log;
extern ThreadSynchronization g_thread_sync;
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

    g_main_window.instance = instance;
    ReplayTable_00438ad0* replays = new ReplayTable_00438ad0;
    g_replay_table = replays;
    for (section = g_thread_sync.critical_sections, index = 7; index != 0; --index, ++section)
        InitializeCriticalSection(section);
    g_log.Append(str_log_header);

    if (Startup_InstanceCheck_00439ff0() == -1)
        goto close_pass;
    g_application.instance = instance;
    SaveSystemSettingsRetail_004392e0();
    if (reinterpret_cast<GameApp_00420870*>(&g_application)->LoadConfig("th10.cfg") != 0)
        goto close_pass;
    if (g_application.config.flags & 0x100) {
        // The start-up dialog: "run full screen?"; 6 is its Yes button.
        g_application.config.field_1d = DialogBoxParamA(instance,
            reinterpret_cast<const char*>(0xCB), 0, &StartupDialog_Procedure, 0) != 6;
    }
    ComputeExecutableChecksum();

    for (;;) {
        D3DResourceManager_00438ad0* resources = new D3DResourceManager_00438ad0;
        g_func_ctrl = resources;
        g_application.direct3d = static_cast<Direct3D*>(Direct3DCreate9_00452176(0x20));
        if (g_application.direct3d == 0) {
            reinterpret_cast<TextLog_0044b8e0*>(&g_log)->AppendLine(str_d3d_create_failed);
            goto close_pass;
        }
        if (CreateGameWindow_00439730(instance) != 0)
            goto close_pass;
        g_sound_manager.Start(g_main_window.window);
        if (asm_FUN_00439890_00439890() != 0)
            goto close_pass;
        Joystick_Probe_0044a0c0();
        Input_NormalizeKeyboardState();
        AnimationManager_00438ad0* animations = new AnimationManager_00438ad0;
        g_sprt_ctrl = animations;
        if (!g_application.config.field_1d) {
            asm_WINNLSEnableIME_0045232c(0, 0);
            ShowCursor(0);
            SetCursor(0);
        }
        g_main_window.previous_time = 0.0;
        g_main_window.start_time = g_main_window.target_time =
            g_main_window.frame_time = g_main_window.previous_time = FrameTimer_GetDelta();
        SetForegroundWindow(g_main_window.window);

        exit_code = App_RegisterTasks_00420470();
        if (exit_code != 0) {
            if (exit_code != -1)
                exit_code = 2;
        } else {
            exit_code = 0;
            g_main_window.cursor_state = 0xFC;
            while (!g_main_window.quit) {
                if (PeekMessageA(&message, 0, 0, 0, 1)) {
                    PumpMessage(&message);
                    continue;
                }
                long state = g_application.device->TestCooperativeLevel();
                if (state == 0) {
                    exit_code = GameFrameAdvance_00439390(
                        reinterpret_cast<GameFrame_00439390*>(&g_main_window));
                    if (exit_code != 0)
                        break;
                    g_application.flags &= ~0x10u;
                } else if (state == 0x88760869) {
                    // D3DERR_DEVICENOTRESET
                    ReleaseAll_00438a30(reinterpret_cast<Holder_00438a30*>(g_sprt_ctrl));
                    if (g_application.device->Reset(&g_application.present_parameters) != 0)
                        break;
                    Renderer_ApplyDeviceDefaults();
                    g_application.mode = 3;
                    g_application.flags |= 0x10;
                }
            }
        }

        reinterpret_cast<App_00420270*>(&g_application)->Shutdown();
        delete g_func_ctrl;
        g_func_ctrl = 0;
        while (reinterpret_cast<WaveSoundManager*>(&g_sound_manager)->ProcessCommands() != 0) {
        }
close_pass:
        g_sound_manager.Stop();
        delete g_sprt_ctrl;
        g_sprt_ctrl = 0;
        if (g_application.device != 0) {
            g_application.device->Reset(&g_application.present_parameters);
            if (g_application.device != 0) {
                g_application.device->Release();
                g_application.device = 0;
            }
        }
        if (g_application.direct3d != 0) {
            g_application.direct3d->Release();
            g_application.direct3d = 0;
        }
        if (g_main_window.window != 0) {
            ShowWindow(g_main_window.window, 0);
            MoveWindow(g_main_window.window, 0, 0, 0, 0, 0);
            DestroyWindow(g_main_window.window);
            g_main_window.window = 0;
        }
        ShowCursor(1);
        if (exit_code != 2)
            break;

        // Start the log over for the next run.
        TextLog_0044b810* log = &g_log;
        log->cursor = log->text;
        log->text[0] = 0;
        log->Append(str_restart_required);
        if (!g_application.config.field_1d)
            asm_WINNLSEnableIME_0045232c(0, 1);
        for (index = 0; index < 60; ++index) {
            if (PeekMessageA(&message, 0, 0, 0, 1))
                PumpMessage(&message);
        }
    }

    File_WriteWholeFile("th10.cfg", &g_application.config, 0x34);
    if (g_application.midi != 0) {
        ShutdownMidi_0043ae20(reinterpret_cast<MidiSequencer*>(g_application.midi));
        delete g_application.midi;
        g_application.midi = 0;
    }
    if (g_log.cursor != g_log.text) {
        g_log.Append(str_log_footer);
        if (g_log.dirty)
            MessageBoxA(0, g_log.text, "log", 0x10);
        File_WriteWholeFile("./log.txt", g_log.text, strlen(g_log.text));
    }
    for (section = g_thread_sync.critical_sections, index = 7; index != 0; --index, ++section)
        DeleteCriticalSection(section);
    SystemParametersInfoA(0x11, g_main_window.saved_parameters[0], 0, 2);
    SystemParametersInfoA(0x55, g_main_window.saved_parameters[1], 0, 2);
    SystemParametersInfoA(0x56, g_main_window.saved_parameters[2], 0, 2);
    asm_WINNLSEnableIME_0045232c(0, 1);
    delete g_replay_table;
    return 0;
}
#pragma code_seg()

// The link's entry: the one caller the whole-program link sees.
extern "C" int __stdcall RigEntry(void* instance, int show) {
    return GameMain_00438ad0(instance, 0, 0, show);
}
