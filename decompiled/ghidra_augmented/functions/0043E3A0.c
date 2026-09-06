/* Raw Ghidra reference; not compilable reconstruction. Address: 0043E3A0 */

undefined4 FUN_0043e3a0(void)

{
  bool bVar1;
  DWORD DVar2;
  int iVar3;
  tagMSG local_1c;
  
  bVar1 = false;
  do {
    DVar2 = MsgWaitForMultipleObjects(1,(HANDLE *)&DAT_0049779c,0,0xffffffff,0xbf);
    if (DAT_00497798 == 0) {
      bVar1 = true;
    }
    if (DVar2 == 0) {
      if ((DAT_00497798 != 0) && (*(int *)(DAT_00497798 + 0x30) != 0)) {
        *(undefined4 *)(DAT_00497798 + 0x74) = 1;
        FUN_0044d850(DAT_00497798);
        *(undefined4 *)(DAT_00497798 + 0x74) = 0;
      }
    }
    else if (DVar2 == 1) {
      iVar3 = PeekMessageA(&local_1c,(HWND)0x0,0,0,1);
      while (iVar3 != 0) {
        if (local_1c.message == 0x12) {
          bVar1 = true;
        }
        iVar3 = PeekMessageA(&local_1c,(HWND)0x0,0,0,1);
      }
    }
  } while (!bVar1);
  return 0;
}

