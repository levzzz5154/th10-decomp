// Per-frame state tracer for replay-sync comparison between retail and a rebuilt th10.exe.
// Runs the game under the Win32 debug API with an int3 at the item update (0x0041AFD0, once per
// gameplay frame) and appends one fixed-size record per hit. Build:
//   i686-w64-mingw32-gcc -O2 -o rtrace.exe rtrace.c
// Usage (inside the game directory): rtrace.exe <game.exe> <out.bin>
#include <windows.h>
#include <stdio.h>

#define HOOK 0x0041AFD0u

#pragma pack(push, 1)
typedef struct {
    DWORD magic;              // 'RTR1'
    DWORD hit;                // hook hit index
    DWORD mode;               // 0x00491FB8
    DWORD flags;              // 0x00474CA0
    DWORD globals[64];        // 0x00474C40..0x00474D3F (score, power, lives, ...)
    BYTE  rng[16];            // 0x004918A8 replay RNG, 0x004918B0 effect RNG
    DWORD player;             // 0x00477834
    DWORD player_block[16];   // player+0x3B0..+0x3EF
} Record;
#pragma pack(pop)

static HANDLE proc;
static BOOL rd(DWORD a, void* out, DWORD n) {
    SIZE_T got = 0;
    if (!ReadProcessMemory(proc, (void*)a, out, n, &got) || got != n) { memset(out, 0, n); return FALSE; }
    return TRUE;
}
static char status_path[MAX_PATH];
static volatile DWORD hit_count;
static DWORD WINAPI status_thread(LPVOID unused) {
    for (;;) {
        DWORD mode = 0, title = 0, t[3] = {0}, player = 0;
        rd(0x00491FB8, &mode, 4);
        rd(0x0047784C, &title, 4);
        if (title) rd(title + 0x1C, t, sizeof(t));
        rd(0x00477834, &player, 4);
        char tmp[MAX_PATH + 4];
        snprintf(tmp, sizeof(tmp), "%s.tmp", status_path);
        FILE* f = fopen(tmp, "w");
        if (f) {
            fprintf(f, "mode=%lu title=%lx submode=%lu phase=%lu cursor=%lu player=%lx hits=%lu\n",
                    mode, title, t[0], t[1], t[2], player, hit_count);
            fclose(f);
            MoveFileExA(tmp, status_path, MOVEFILE_REPLACE_EXISTING);
        }
        Sleep(100);
    }
    return 0;
}

static void wr(DWORD a, BYTE b) {
    SIZE_T got = 0;
    WriteProcessMemory(proc, (void*)a, &b, 1, &got);
    FlushInstructionCache(proc, (void*)a, 1);
}

int main(int argc, char** argv) {
    if (argc < 3) { fprintf(stderr, "usage: rtrace <exe> <out.bin>\n"); return 2; }
    FILE* out = fopen(argv[2], "wb");
    if (!out) { fprintf(stderr, "cannot open %s\n", argv[2]); return 2; }
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(argv[1], NULL, NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess %lu\n", GetLastError()); return 2;
    }
    proc = pi.hProcess;
    snprintf(status_path, sizeof(status_path), "%s.status", argv[2]);
    CreateThread(NULL, 0, status_thread, NULL, 0, NULL);
    BYTE original = 0;
    BOOL armed = FALSE, stepping = FALSE;
    DWORD hit = 0;
    DEBUG_EVENT ev;
    for (;;) {
        if (!WaitForDebugEvent(&ev, INFINITE)) break;
        DWORD status = DBG_CONTINUE;
        switch (ev.dwDebugEventCode) {
        case CREATE_PROCESS_DEBUG_EVENT:
            rd(HOOK, &original, 1);
            wr(HOOK, 0xCC);
            armed = TRUE;
            if (ev.u.CreateProcessInfo.hFile) CloseHandle(ev.u.CreateProcessInfo.hFile);
            break;
        case LOAD_DLL_DEBUG_EVENT:
            if (ev.u.LoadDll.hFile) CloseHandle(ev.u.LoadDll.hFile);
            break;
        case EXCEPTION_DEBUG_EVENT: {
            EXCEPTION_RECORD* er = &ev.u.Exception.ExceptionRecord;
            DWORD addr = (DWORD)(ULONG_PTR)er->ExceptionAddress;
            HANDLE th = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT, FALSE, ev.dwThreadId);
            CONTEXT c; c.ContextFlags = CONTEXT_FULL;
            if (er->ExceptionCode == EXCEPTION_BREAKPOINT && armed && addr == HOOK) {
                Record r; memset(&r, 0, sizeof(r));
                r.magic = 0x31525452; r.hit = hit++; hit_count = hit;
                rd(0x00491FB8, &r.mode, 4);
                rd(0x00474CA0, &r.flags, 4);
                rd(0x00474C40, r.globals, sizeof(r.globals));
                rd(0x004918A8, r.rng, sizeof(r.rng));
                rd(0x00477834, &r.player, 4);
                if (r.player) rd(r.player + 0x3B0, r.player_block, sizeof(r.player_block));
                fwrite(&r, sizeof(r), 1, out);
                fflush(out);   // the run ends by killing the game; keep every record
                GetThreadContext(th, &c);
                c.Eip = HOOK;
                c.EFlags |= 0x100;   // single-step over the restored byte, then re-arm
                SetThreadContext(th, &c);
                wr(HOOK, original);
                stepping = TRUE;
            } else if (er->ExceptionCode == EXCEPTION_SINGLE_STEP && stepping) {
                wr(HOOK, 0xCC);
                stepping = FALSE;
            } else if (er->ExceptionCode == EXCEPTION_BREAKPOINT) {
                // loader breakpoint
            } else {
                if (!ev.u.Exception.dwFirstChance || er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION
                    || er->ExceptionCode == EXCEPTION_ILLEGAL_INSTRUCTION) {
                    GetThreadContext(th, &c);
                    fprintf(stderr, "EXCEPTION code=%08lx addr=%08lx first=%lu hit=%lu eip=%08lx esp=%08lx\n",
                            er->ExceptionCode, addr, ev.u.Exception.dwFirstChance, hit, c.Eip, c.Esp);
                    for (DWORD a = c.Esp; a < c.Esp + 0x400; a += 4) {
                        DWORD v; if (rd(a, &v, 4) && v >= 0x401000 && v < 0x470000) fprintf(stderr, " stack %08lx: %08lx\n", a, v);
                    }
                    fflush(stderr);
                }
                status = DBG_EXCEPTION_NOT_HANDLED;
            }
            if (th) CloseHandle(th);
            break;
        }
        case EXIT_PROCESS_DEBUG_EVENT:
            fprintf(stderr, "EXIT code=%lu hits=%lu\n", ev.u.ExitProcess.dwExitCode, hit);
            fclose(out);
            return 0;
        }
        ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, status);
    }
    fclose(out);
    return 1;
}
