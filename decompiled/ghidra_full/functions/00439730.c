/* Raw Ghidra reference; not compilable reconstruction. Address: 00439730 */

undefined4 FUN_00439730(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  HINSTANCE unaff_EBX;
  UINT local_28;
  WNDPROC local_24;
  int local_20;
  int local_1c;
  
  local_28 = 0;
  local_24 = (WNDPROC)0x0;
  local_20 = 0;
  local_1c = 0;
  GetStockObject(4);
  LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_24 = FUN_004390e0;
  DAT_004924fc = 1;
  DAT_00492500 = 0;
  RegisterClassA((WNDCLASSA *)&local_28);
  if (DAT_00491d65 == '\0') {
    DAT_00491c70 = CreateWindowExA(0,"BASE",&DAT_0046f66c,0xcf0000,0,0,0x280,0x1e0,(HWND)0x0,
                                   (HMENU)0x0,unaff_EBX,(LPVOID)0x0);
  }
  else {
    iVar1 = GetSystemMetrics(7);
    iVar2 = GetSystemMetrics(8);
    iVar3 = GetSystemMetrics(4);
    DAT_00491c70 = CreateWindowExA(0,"BASE",&DAT_0046f66c,0x100a0000,-0x80000000,-0x80000000,
                                   iVar1 * 2 + 0x280,iVar3 + 0x1e0 + iVar2 * 2,(HWND)0x0,(HMENU)0x0,
                                   unaff_EBX,(LPVOID)0x0);
  }
  g_pWnd = DAT_00491c70;
  if (DAT_00491c70 == (HWND)0x0) {
    return 1;
  }
  SendMessageA(DAT_00491c70,0x112,0xf020,0);
  Sleep(0x10);
  SendMessageA(g_pWnd,0x112,0xf120,0);
  return 0;
}

