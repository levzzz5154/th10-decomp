// Compiler context only; this caller is never selected as recovered game code.
// The shared native LTCG unit recovers EAX as the cursor pointer for all methods.
#include "../units/menu_9d8ff0.cpp"

// 0x004243C0/0x004243D0 are a separate translation unit of this link.
int StepMenuCursor(int step, MenuCursor* cursor);
int StepMenuCursorBack(int step, MenuCursor* cursor);

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
        result += StepMenuCursor(delta, cursors[index]);
        result += StepMenuCursorBack(delta, cursors[index]);
    }
    return result;
}
#pragma code_seg()
