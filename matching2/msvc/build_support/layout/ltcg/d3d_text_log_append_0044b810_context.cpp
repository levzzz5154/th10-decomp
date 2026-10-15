// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zunlib/text_log.cpp"

#pragma code_seg(".text$05context")
short __stdcall Joystick_Probe_0044a0c0();

#pragma code_seg(".text$05context")
int __stdcall D3DTextLogAppendCompilerContext(char* format) {
    Joystick_Probe_0044a0c0();
    return *(int*)((TextLog_0044b810*)0x00474F70)->Append(format);
}
#pragma code_seg()
