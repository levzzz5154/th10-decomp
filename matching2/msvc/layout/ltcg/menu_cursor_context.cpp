// Compiler context only; this caller is never selected as recovered game code.
// The shared native LTCG unit recovers EAX as the cursor pointer for all methods.
#include "../../src/game/menu.cpp"

#pragma code_seg(".text$23context")
int __stdcall MenuCursorCompilerContext(MenuCursor** cursors, int count, int delta, int wrap) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        cursors[index]->Reset();
        cursors[index]->SetWrap(wrap);
        cursors[index]->SetItemCount(count);
        cursors[index]->ClearDisabledItems();
        cursors[index]->DisableItem(delta);
        cursors[index]->PushSelection();
        result += cursors[index]->Previous();
        result += cursors[index]->Next();
        result += cursors[index]->Advance(delta);
        cursors[index]->PopSelection();
        result += cursors[index]->GetSelection();
    }
    return result;
}
#pragma code_seg()
