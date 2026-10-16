// 0x0042D260 and 0x0042D2F0: the title's render task.
//
// The task draws the text overlay of whichever menu page is open; the pages
// without one fall through. The scheduler enters through the callback at
// 0x0042D2F0, which hands the menu over in EAX.
#include "th10/game/title_draw.hpp"

extern "C" {
// These pages take the menu on the stack.
int __stdcall TitleMenu_DrawReplayBrowser2(TitleDrawView* menu);
int __stdcall TitleMenu_DrawScoreEntry2(TitleDrawView* menu);
int __stdcall TitleMenu_DrawReplaySave2(TitleDrawView* menu);
}

#pragma code_seg(".text$03dispatch")
int TitleDrawView::DrawOverlay() {
    switch (page) {
    case 12:
        TitleMenu_DrawReplayBrowser2(this);
        return 1;
    case 11:
        DrawScoreRows();
        return 1;
    case 15:
        TitleMenu_DrawScoreEntry2(this);
        return 1;
    case 16:
        TitleMenu_DrawReplaySave2(this);
        return 1;
    case 9:
        DrawPracticeRows();
        break;
    }
    return 1;
}

#pragma code_seg(".text$04callback")
int __fastcall Title_OnDraw(TitleDrawView* menu) {
    return menu->DrawOverlay();
}
#pragma code_seg()
