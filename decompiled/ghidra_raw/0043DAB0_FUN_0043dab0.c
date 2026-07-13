/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043DAB0
 * Tracking name: FUN_0043dab0
 * Ghidra name: FUN_0043dab0
 * Tracked span: 176 bytes
 */


void FUN_0043dab0(void)

{
  DWORD DVar1;
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 21000) != 0) {
    FUN_0044d550();
    if (*(int *)(unaff_ESI + 0x618) != 0) {
      PostThreadMessageA(*(DWORD *)(unaff_ESI + 0x614),0x12,0,0);
      DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 0x618),0x100);
      while (DVar1 != 0) {
        PostThreadMessageA(*(DWORD *)(unaff_ESI + 0x614),0x12,0,0);
        DVar1 = WaitForSingleObject(*(HANDLE *)(unaff_ESI + 0x618),0x100);
      }
      CloseHandle(*(HANDLE *)(unaff_ESI + 0x618));
      CloseHandle(*(HANDLE *)(unaff_ESI + 0x520c));
      *(undefined4 *)(unaff_ESI + 0x618) = 0;
    }
    if (*(undefined4 **)(unaff_ESI + 21000) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(unaff_ESI + 21000))(1);
      *(undefined4 *)(unaff_ESI + 21000) = 0;
    }
  }
  return;
}

