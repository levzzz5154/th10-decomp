#include "../../src/game/ending/ending_text_construct.cpp"
inline void* __cdecl operator new(unsigned int, void* memory) { return memory; }
#pragma code_seg(".text$03context")
extern "C" EndingText* __stdcall EndingTextContext(EndingText* storage, void* script) { return new(storage) EndingText(script); }
#pragma code_seg()
