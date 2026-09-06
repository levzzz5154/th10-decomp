/* Raw Ghidra reference; not compilable reconstruction. Address: 0043A3A0 */

undefined4 FUN_0043a3a0(HWND param_1,int param_2,short param_3)

{
  UINT UVar1;
  HWND hWnd;
  WPARAM wParam;
  LPARAM lParam;
  
  if (param_2 == 0x110) {
    lParam = 0;
    wParam = 1;
    UVar1 = 0xf1;
    hWnd = GetDlgItem(param_1,0xca);
    SendMessageA(hWnd,UVar1,wParam,lParam);
    return 0;
  }
  if (param_2 == 0x111) {
    if (param_3 == 0xc9) {
      UVar1 = IsDlgButtonChecked(param_1,0xca);
      if (UVar1 == 1) {
        DAT_00491d78 = DAT_00491d78 | 0x100;
        EndDialog(param_1,6);
        return 0;
      }
      DAT_00491d78 = DAT_00491d78 & 0xfffffeff;
      EndDialog(param_1,6);
    }
    else if (param_3 == 0xcb) {
      UVar1 = IsDlgButtonChecked(param_1,0xca);
      if (UVar1 == 1) {
        DAT_00491d78 = DAT_00491d78 | 0x100;
        EndDialog(param_1,7);
        return 0;
      }
      DAT_00491d78 = DAT_00491d78 & 0xfffffeff;
      EndDialog(param_1,7);
      return 0;
    }
  }
  return 0;
}

