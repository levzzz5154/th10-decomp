// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/game/mother/screenshot_capture_00420670.cpp"
#include <stdarg.h>

extern "C" int __cdecl ScreenshotCaptureEscape(void* pointer, int value);

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ScreenshotCaptureContext(GameApp_00420670** apps, const char** names, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        const char* name = names[index];
        total += ScreenshotCaptureEscape(apps[index], index);
        total += apps[index]->CaptureScreenshot(name);
        total += ScreenshotCaptureEscape((void*)name, total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()

// The body of the log appender 0x0044B810 (src/core/zunlib/text_log.cpp), which
// takes the log in ECX.
extern "C" int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* arguments);
struct ScreenshotCaptureCriticalSection { unsigned char storage[24]; };
extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(ScreenshotCaptureCriticalSection* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(ScreenshotCaptureCriticalSection* section);
extern ScreenshotCaptureCriticalSection g_text_log_lock;
extern unsigned char g_text_log_lock_depth;
}
#pragma code_seg(".text$00i_append")
__declspec(noinline) char* TextLog_00420670::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);
    EnterCriticalSection(&g_text_log_lock);
    ++g_text_log_lock_depth;
    asm_vsprintf_004524a6(staging, format, arguments);
    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) < (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }
    LeaveCriticalSection(&g_text_log_lock);
    --g_text_log_lock_depth;
    return format;
}
#pragma code_seg()
