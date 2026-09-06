/* Raw Ghidra reference; not compilable reconstruction. Address: 004390E0 */

LRESULT __thiscall FUN_004390e0(void *this,HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  LRESULT LVar1;
  HCURSOR hCursor;
  
  if (0x20 < param_2) {
    if (param_2 == 0x201) {
      SetForegroundWindow(param_1);
    }
    else if ((param_2 == 0x3c9) && (DAT_00491fe8 != 0)) {
      FUN_0043aeb0(this,DAT_00491fe8);
      LVar1 = DefWindowProcA(param_1,0x3c9,param_3,param_4);
      return LVar1;
    }
LAB_004391d8:
    LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
    return LVar1;
  }
  if (param_2 == 0x20) {
    if ((DAT_00491d65 == '\0') && (DAT_00492500 == 0)) {
      ShowCursor(0);
      SetCursor((HCURSOR)0x0);
      return 1;
    }
    hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
    SetCursor(hCursor);
    ShowCursor(1);
    return 1;
  }
  if (param_2 == 0x10) {
    DAT_00491ff4 = DAT_00491ff4 | 0x80;
  }
  else if (param_2 != 0x14) {
    if (param_2 == 0x1c) {
      DAT_00492500 = (uint)(param_3 == 0);
      DAT_004924fc = param_3;
      LVar1 = DefWindowProcA(param_1,0x1c,param_3,param_4);
      return LVar1;
    }
    goto LAB_004391d8;
  }
  return 1;
}

