// Compiler context only; never selected as recovered game code.
#include "../../src/platform/text_log.cpp"

#pragma code_seg(".text$03context")
int __stdcall D3DTextLogAppendCompilerContext(char* format) {
    return *(int*)((TextLog_0044b810*)0x00474F70)->Append(format);
}
#pragma code_seg()
