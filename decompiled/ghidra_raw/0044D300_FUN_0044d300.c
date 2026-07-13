/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044D300
 * Tracking name: FUN_0044d300
 * Ghidra name: FUN_0044d300
 * Tracked span: 112 bytes
 */


int FUN_0044d300(void)

{
  int iVar1;
  undefined4 *unaff_EBX;
  int *unaff_ESI;
  
  if (unaff_ESI == (int *)0x0) {
    return -0x7ffbfe10;
  }
  if (unaff_EBX != (undefined4 *)0x0) {
    *unaff_EBX = 0;
  }
  iVar1 = (**(code **)(*unaff_ESI + 0x24))();
  if (-1 < iVar1) {
    if (((uint)unaff_ESI & 2) != 0) {
      do {
        iVar1 = (**(code **)(*unaff_ESI + 0x50))();
        if (iVar1 == -0x7787ff6a) {
          Sleep(10);
        }
        iVar1 = (**(code **)(*unaff_ESI + 0x50))();
      } while (iVar1 != 0);
      if (unaff_EBX != (undefined4 *)0x0) {
        *unaff_EBX = 1;
      }
      return 0;
    }
    iVar1 = 1;
  }
  return iVar1;
}

