// Compiler context of the stage-tip parser cluster: the record constructor and
// the named-value lookup the parser calls, then the real parser and reader.
#include "stage_parser_model.hpp"
#include "th10/platform/archive_file.hpp"
#include <new>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy, strlen)
#pragma code_seg(".text$p00b_ctor")
__declspec(noinline) Tip::Tip() {
    memset(this, 0, sizeof *this);
    node.Unlink();
    node.owner = this;
    *reinterpret_cast<int*>(&blue) = -1;
    remain = -1;
    time = 300;
    scale = 1.0f;
}
#pragma code_seg(".text$p00zfind")
__declspec(noinline) int FindNamedValue(const char* name, const NamedValue* table, int count) {
    for (int index = 0; index < count; ++index) {
        if (strcmp(name, table[index].key) == 0)
            return table[index].value;
    }
    return 0;
}
#pragma code_seg()


// Synthetic root: keeps the parser address-taken, as it is for its retail callers.
#pragma code_seg(".text$p10b_context")
extern "C" __declspec(noinline) void* __stdcall HintParserContext() {
    return Hint_ParseData;
}
#pragma code_seg()
#include "../../../src/game/hint/script_text_reader.cpp"
#include "stage_archive_loader.cpp"
