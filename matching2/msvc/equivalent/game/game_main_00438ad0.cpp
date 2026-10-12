// 0x00438AD0..0x0043900C: the game's WinMain. Everything here is one
// straight line per phase; the frame loop in the middle owns the window
// message pump, the device-lost recovery and the three exits (restart,
// in-game quit, error).
//
// Equivalent recovery: the COM-style device calls and the two x87 timing
// stores compile to the retail shapes; the allocator null checks and the
// crash-log branches are recorded differences.
#include "th10/game/game_main_00438ad0.hpp"
#include "th10/platform/text_log.hpp"



extern "C" {
// KERNEL32 slots.
extern void* (__stdcall* data_004660b8)(void* section);          // InitializeCriticalSection
extern void* (__stdcall* data_004660bc)(void* section);          // DeleteCriticalSection
// KERNEL32 slots (continued).
extern void* (__stdcall* data_00466118)(void* security, unsigned stack,
    unsigned (__stdcall* entry)(void*), void* parameter, unsigned flags, unsigned* thread_id);
// USER32 slots.
extern int   (__stdcall* data_004661f0)(void* window);           // SetForegroundWindow
extern int   (__stdcall* data_004661f4)(void* window, int x, int y, int w, int h, int repaint);
extern int   (__stdcall* data_00466220)(void* window);           // DestroyWindow
extern void* (__stdcall* data_00466224)(void* cursor);           // SetCursor
extern int   (__stdcall* data_0046622c)(const void* message);    // TranslateMessage
extern int   (__stdcall* data_00466230)(int show);               // ShowCursor
extern int   (__stdcall* data_00466234)(void* window, const char* text,
                                         const char* caption, unsigned type);
extern int   (__stdcall* data_0046623c)(void* message, void* window,
                                        unsigned low, unsigned high, unsigned remove);
extern int   (__stdcall* data_0046624c)(void* window, int command);
extern int   (__stdcall* data_00466254)(const void* message);    // DispatchMessageA
extern unsigned int (__stdcall* data_00466258)(unsigned action, void* parameter,
                                               void* ini_file, unsigned update);
extern int (__stdcall* data_00466264)(void* instance, const char* template_name,
                                      void* window, void* dialog_proc, void* parameter);

// The globals the body reads or writes.
extern void* data_004924f0;                 // the game window
extern unsigned int data_004924f4;          // quit requested
extern void* data_004924f8;                 // the instance copy
extern void* data_00491be0;                 // the replay buffer (0xA004 dwords)
extern void* data_00491be4;                 // the D3D resource manager
extern void* data_00491c10;                 // the animation manager storage
extern void* data_00491c28;                 // the instance copy
extern void* data_00491c2c;                 // the Direct3D object
extern void* data_00491c30;                 // the Direct3D device
extern void* data_00491d0c;                 // the device reset parameters
extern unsigned char data_00491d65;         // the startup dialog ran
extern unsigned int data_00491d78;          // configuration flags
extern void* data_00491fd4;                 // the application mode
extern unsigned int data_00491fe8;          // the MIDI handle
extern unsigned int data_00491ff4;          // runtime flags (0x10: device lost)
extern unsigned int data_0049251c;          // the system mouse speed 1
extern unsigned int data_00492520;          // the system mouse speed 2
extern unsigned int data_00492524;          // the system mouse speed 3
extern double data_00492528;                // the frame-time doubles
extern double data_00492530;
extern double data_00492538;
extern double data_00492540;
extern unsigned char data_00492504;         // the cursor-clip marker
extern void* data_004977a8;                 // the music thread handle
extern void* data_004977b4;                 // the sound worker stage
extern void* data_004977b8;                 // the sound manager owner
extern void* data_004977b0;                 // the sound thread parameter block
extern TextLog_0044b810 data_00474f70;      // the 8 KiB diagnostic log
extern void* data_00476f70;                 // the log-owning module marker
extern unsigned char data_00476f74;         // log to the file too
extern void* data_00491d48;                 // the 0x34-byte config tail
extern void* data_00491c70;                 // the music worker parameter
}

// 0x00420470: register the application tasks.
extern "C" int __stdcall App_RegisterTasks_00420470();
// 0x00439390: one frame; 0x00439890: the D3D device init.
extern "C" int __stdcall GameFrameAdvance_00439390(void* window_slot);
extern "C" int __stdcall D3DInitialize_00439890();
// 0x00439540: the frame clock delta; 0x00439D20: apply device defaults.
extern "C" double __cdecl FrameTimer_GetDelta_00439540();
extern "C" void __stdcall Renderer_ApplyDeviceDefaults_00439d20();
// 0x004392E0, 0x00439730: the settings and the window.
extern "C" int __stdcall SaveSystemSettingsRetail_004392e0(void);
extern "C" int __fastcall CreateGameWindow_00439730(
    void* instance, void* edx_dummy);
// 0x00439FF0: the single-instance mutex check; 0x0043A1C0: the checksum.
extern "C" int __stdcall Startup_InstanceCheck_00439ff0();
extern "C" int __stdcall ComputeExecutableChecksum_0043a1c0();
// 0x0043CCF0: the sound stream worker the music thread runs; the thread
// entry ignores its parameter and reads the manager globals.
extern "C" void __stdcall StartAddress_0043ccf0();
// MIDI teardown.
extern "C" int __stdcall ShutdownMidi_0043ae20(int handle);
extern "C" int __stdcall CleanupMidi_0043a910(int handle);
// The sound worker pair and the wave manager.
extern "C" void __stdcall SoundWorker_Stop_0043cc40();
extern "C" void __stdcall WaveSoundManager_Cleanup_0043d120();
extern "C" int __stdcall WaveSoundManager_ProcessCommands_0043ddf0(void* manager);
// The animation manager storage and the D3D resource manager.
// 0x00445900: the animation storage constructor, this in ECX. The model
// reaches it through the __fastcall this-shim so no C++ object machinery
// (and no exception cleanup table) wraps the call.
extern "C" void __fastcall AnmStorage_Construct_00445900(void* storage);
// 0x00446220: the animation storage destructor, this in ECX.
extern "C" void __fastcall AnmStorage_Destroy_00446220(void* storage);

// 0x00438880: the D3D resource manager destructor (this in ECX).
struct D3DResourceManager_00438880 {
    ~D3DResourceManager_00438880();
};
extern "C" void* __stdcall D3DResourceManager_Initialize_00449aa0();
extern "C" void* __stdcall Direct3DCreate9_00452176(unsigned sdk_version);
// Input probes.
extern "C" unsigned short __stdcall Joystick_Probe_0044a0c0();
extern "C" void __stdcall Input_NormalizeKeyboardState_0044b080();
// Files and logs.
extern "C" int __stdcall File_WriteWholeFile_0044b540(
    const char* path, const void* data, unsigned length);
extern "C" void __stdcall WINNLSEnableIME_0045232c(void* window, int enabled);
extern "C" void* __cdecl operator_new_00452493(unsigned size);
extern "C" void __cdecl free_004524a1(void* memory);
// 0x00438A30: release every entity list of the animation manager.
extern "C" void __stdcall ReleaseAll_00438a30(void* holder);
// 0x00420870: the configuration; 0x00420270: the application shutdown.
extern "C" int __stdcall GameApp_LoadConfig_00420870(const char* path);
// 0x00420270: the application shutdown (this in ECX = 0x491C28).
struct App_00420270 {
    int Shutdown();
};

// The startup dialog (resource 0xCB) and its four-argument procedure.
struct StartupDialogArgs_00438ad0;
extern "C" void* __stdcall StartupDialog_Procedure(
    void* window, unsigned message, unsigned parameter, long detail);

struct MSG_00438ad0 {
    void* window;
    unsigned message;
    unsigned w_param;
    unsigned l_param;
    unsigned time;
    int point_x;
    int point_y;
};

// The retail string constants (bound to their addresses in the layout).
extern "C" const char kReplayLogBanner[];
extern "C" const char kD3dCreateFailed[];
extern "C" const char kRestartRequired[];
extern "C" const char kLogSeparator[];
extern "C" const char kLogPath[];
extern "C" const char kLogTitle[];
extern "C" const char kConfigPath[];

// The Direct3D device slots the body calls: 3 TestCooperativeLevel,
// 8 Release, 16 Reset (offset 0x40).
struct DeviceVtable_00438ad0 {
    void* slots_000[3];
    long (__stdcall* test_cooperative_level)(void* device);
    void* slots_010[4];
    unsigned long (__stdcall* release)(void* device);
    void* slots_020[6];
    long (__stdcall* reset)(void* device, void* parameters);
};

// The seven one-shot subsystem objects (0x492274 + 0x18·i) the main loop
// enters and leaves critical sections on; the retail image owns them.
extern "C" unsigned char data_00492274[7][0x18];

#pragma code_seg(".text$00438ad0_fn")
__declspec(noinline) int __stdcall GameMain_00438ad0(
        void* instance, void* previous, char* command_line, int show) {
    MSG_00438ad0 message;
    unsigned exit_code = 0;
    data_004924f8 = instance;
    // The replay buffer: 0xA000 entry slots plus the length guard.
    void* replay_buffer = operator_new_00452493(0xA004);
    if (replay_buffer != 0) {
        unsigned int* fill = static_cast<unsigned int*>(replay_buffer);
        for (int words = 0x2801; words != 0; --words)
            *fill++ = 0;
        static_cast<unsigned int*>(replay_buffer)[0xA000] = 0;
    } else {
        replay_buffer = 0;
    }
    data_00491be0 = replay_buffer;
    {
        void* (__stdcall* initialize)(void*) = data_004660b8;
        unsigned char* section = data_00492274[0];
        for (int count = 7; count != 0; --count, section += 0x18)
            initialize(section);
    }
    data_00474f70.Append(const_cast<char*>(kReplayLogBanner));
restart_window:
    if (Startup_InstanceCheck_00439ff0() == -1)
        goto shutdown;
    data_00491c28 = instance;
    SaveSystemSettingsRetail_004392e0();
    if (GameApp_LoadConfig_00420870(kConfigPath) != 0) {
        exit_code = 1;
        goto shutdown;
    }
    if (data_00491d78 & 0x100) {
        if (data_00466264(instance,
                reinterpret_cast<const char*>(0xCB), 0,
                reinterpret_cast<void*>(&StartupDialog_Procedure), 0) != 6)
            data_00491d65 = 1;
    }
    ComputeExecutableChecksum_0043a1c0();
    // The D3D resource manager and the Direct3D object.
    {
        void* d3d_manager = operator_new_00452493(0x48);
        data_00491be4 = (d3d_manager != 0)
            ? D3DResourceManager_Initialize_00449aa0() : 0;
        void* d3d_object = Direct3DCreate9_00452176(0x20);
        data_00491c2c = d3d_object;
        if (d3d_object == 0) {
            data_00474f70.Append(const_cast<char*>(kD3dCreateFailed));
            goto shutdown;
        }
        if (CreateGameWindow_00439730(instance, 0) != 0) {
            exit_code = 1;
            goto shutdown;
        }
    }
    {
        // The sound subsystem: a zeroed 0x14B4 manager at 0x492590, its
        // owner word, and the streaming thread.
        unsigned int* sound = reinterpret_cast<unsigned int*>(0x492590);
        for (int words = 0x14B4 / 4; words != 0; --words) *sound++ = 0;
        data_004977b8 = data_004924f0;
        data_004977a8 = data_00466118(0, 0,
            reinterpret_cast<unsigned (__stdcall*)(void*)>(&StartAddress_0043ccf0),
            data_00491c70, 0, reinterpret_cast<unsigned*>(&data_004977b0));
        if (D3DInitialize_00439890() != 0) {
            exit_code = 1;
            goto shutdown;
        }
        Joystick_Probe_0044a0c0();
        Input_NormalizeKeyboardState_0044b080();
        // The animation manager storage.
        void* storage = operator_new_00452493(0x732460);
        if (storage != 0) {
            AnmStorage_Construct_00445900(storage);
            data_00491c10 = storage;
        } else {
            data_00491c10 = 0;
        }
        if (data_00491d65 == 0) {
            WINNLSEnableIME_0045232c(0, 0);
            data_00466230(0);
            data_00466224(0);
        }
        // The frame-time doubles: the default delta first, then the
        // clock's delta stored to all four homes from the x87 return.
        data_00492540 = *reinterpret_cast<const double*>(0x470B70);
        data_00492540 = data_00492538 = data_00492530 = data_00492528 =
            FrameTimer_GetDelta_00439540();
        data_004661f0(data_004924f0);
        int registered = App_RegisterTasks_00420470();
        if (registered != 0) {
            if (registered != -1)
                exit_code = 2;
            goto leave;
        }
        data_00492504 = 0xFC;
        for (;;) {
            if (data_0046623c(&message, 0, 0, 0, 1) != 0) {
                data_0046622c(&message);
                data_00466254(&message);
            } else {
                // One game frame; the device-loss recovery on the side.
                void** device_object = static_cast<void**>(data_00491c30);
                int frame = (device_object != 0)
                    ? reinterpret_cast<long (__stdcall**)(void*)>(device_object)[3](data_00491c30)
                    : 0;
                if (frame == 0) {
                    int advanced = GameFrameAdvance_00439390(&data_004924f0);
                    exit_code = static_cast<unsigned>(advanced);
                    if (advanced != 0) {
                        data_00491ff4 &= ~0x10u;
                        goto leave;
                    }
                } else if (frame == 0x88760869 /* D3DERR_DEVICELOST */) {
                    ReleaseAll_00438a30(data_00491c10);
                    DeviceVtable_00438ad0* vtable =
                        *reinterpret_cast<DeviceVtable_00438ad0**>(data_00491c30);
                    if (vtable->reset(data_00491c30, &data_00491d0c) == 0) {
                        Renderer_ApplyDeviceDefaults_00439d20();
                        data_00491fd4 = reinterpret_cast<void*>(3);
                        data_00491ff4 |= 0x10u;
                    }
                }
            }
            if (data_004924f4 != 0)
                break;
        }
    }
leave:
    // Not the restart exit: write the settings tail.
    if (exit_code != 2)
        File_WriteWholeFile_0044b540(kConfigPath, &data_00491d48, 0x34);
shutdown:
    reinterpret_cast<App_00420270*>(data_00491c28)->Shutdown();
    if (data_00491be4 != 0) {
        reinterpret_cast<D3DResourceManager_00438880*>(data_00491be4)->
            ~D3DResourceManager_00438880();
        free_004524a1(data_00491be4);
    }
    data_00491be4 = 0;
    while (WaveSoundManager_ProcessCommands_0043ddf0(
            reinterpret_cast<void*>(0x492590)) == 0) {}
    SoundWorker_Stop_0043cc40();
    WaveSoundManager_Cleanup_0043d120();
    if (data_00491c10 != 0) {
        AnmStorage_Destroy_00446220(data_00491c10);
        free_004524a1(data_00491c10);
    }
    data_00491c10 = 0;
    if (data_00491c30 != 0) {
        DeviceVtable_00438ad0* vtable =
            *reinterpret_cast<DeviceVtable_00438ad0**>(data_00491c30);
        vtable->reset(data_00491c30, &data_00491d0c);
        if (data_00491c30 != 0) {
            vtable = *reinterpret_cast<DeviceVtable_00438ad0**>(data_00491c30);
            vtable->release(data_00491c30);
        }
        data_00491c30 = 0;
    }
    if (data_00491c2c != 0) {
        DeviceVtable_00438ad0* vtable =
            *reinterpret_cast<DeviceVtable_00438ad0**>(data_00491c2c);
        vtable->release(data_00491c2c);
        data_00491c2c = 0;
    }
    if (data_004924f0 != 0) {
        data_0046624c(data_004924f0, 0);
        data_004661f4(data_004924f0, 0, 0, 0, 0, 0);
        data_00466220(data_004924f0);
        data_004924f0 = 0;
    }
    data_00466230(1);
    if (exit_code == 2) {
        // The restart-required exit: a fresh log, IME back on if the
        // dialog never ran, and a 60-frame message pump before the
        // window pass restarts.
        data_00476f70 = &data_00474f70;
        data_00474f70.text[0] = 0;
        data_00474f70.Append(const_cast<char*>(kRestartRequired));
        if (data_00491d65 == 0)
            WINNLSEnableIME_0045232c(0, 1);
        for (int frames = 0x3C; frames != 0; --frames) {
            if (data_0046623c(&message, 0, 0, 0, 1) != 0) {
                data_0046622c(&message);
                data_00466254(&message);
            }
        }
        goto restart_window;
    }
    File_WriteWholeFile_0044b540(kConfigPath, &data_00491d48, 0x34);
    if (data_00491fe8 != 0) {
        ShutdownMidi_0043ae20(data_00491fe8);
        if (data_00491fe8 != 0)
            CleanupMidi_0043a910(data_00491fe8);
        data_00491fe8 = 0;
    }
    if (data_00476f70 != &data_00474f70) {
        data_00474f70.Append(const_cast<char*>(kLogSeparator));
        if (data_00476f74 != 0)
            data_00466234(0, data_00474f70.text, kLogTitle, 0x10);
        const char* text = data_00474f70.text;
        const char* end = text;
        while (*end != 0) ++end;
        File_WriteWholeFile_0044b540(kLogPath, text, end - text);
    }
    {
        unsigned char* section = data_00492274[0];
        for (int count = 7; count != 0; --count, section += 0x18)
            data_004660bc(section);
    }
    // The system mouse speeds and the IME state as the dialog left them.
    unsigned int (__stdcall* set_parameter)(unsigned, void*, void*, unsigned) =
        data_00466258;
    set_parameter(0x11, &data_0049251c, 0, 2);
    set_parameter(0x55, &data_00492520, 0, 2);
    set_parameter(0x56, &data_00492524, 0, 2);
    WINNLSEnableIME_0045232c(0, 1);
    // The replay buffer and its entries.
    if (data_00491be0 != 0) {
        unsigned int count = static_cast<unsigned int*>(data_00491be0)[0xA000];
        unsigned int** entries = reinterpret_cast<unsigned int**>(data_00491be0);
        for (unsigned int index = 0; index < 0x2800; ++index) {
            if (entries[index] != 0)
                free_004524a1(entries[index]);
        }
        free_004524a1(data_00491be0);
    }
    return 0;
}
#pragma code_seg()
