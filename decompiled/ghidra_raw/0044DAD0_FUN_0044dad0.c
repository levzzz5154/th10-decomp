/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044DAD0
 * Tracking name: FUN_0044dad0
 * Ghidra name: FUN_0044dad0
 * Tracked span: 288 bytes
 */


int __fastcall FUN_0044dad0(int param_1)

{
  int iVar1;
  int iVar2;
  int unaff_EDI;
  
  if ((**(int **)(unaff_EDI + 4) == 0) || (*(int *)(unaff_EDI + 0xc) == 0)) {
    return -0x7ffbfe10;
  }
  *(undefined4 *)(unaff_EDI + 0x5c) = 0;
  *(undefined4 *)(unaff_EDI + 0x60) = 0;
  *(undefined4 *)(unaff_EDI + 100) = 0;
  *(undefined4 *)(unaff_EDI + 0x68) = 0;
  iVar2 = FUN_0044d300();
  if (-1 < iVar2) {
    if ((param_1 != 0) && (iVar2 = FUN_0044d110((int *)**(undefined4 **)(unaff_EDI + 4)), iVar2 < 0)
       ) {
      return iVar2;
    }
    iVar2 = *(int *)(unaff_EDI + 0xc);
    if (*(int *)(iVar2 + 0x7c) == 0) {
      if (*(HANDLE *)(iVar2 + 0x8c) != (HANDLE)0x0) {
        SetFilePointer(*(HANDLE *)(iVar2 + 0x8c),
                       *(int *)(*(int *)(iVar2 + 0x90) + 0x10) + DAT_004977a4,(PLONG)0x0,0);
        *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(*(int *)(iVar2 + 0x90) + 0x1c);
      }
    }
    else {
      *(undefined4 *)(iVar2 + 0x84) = *(undefined4 *)(iVar2 + 0x80);
      iVar1 = *(int *)(*(int *)(iVar2 + 0x90) + 0x1c);
      if (0 < iVar1) {
        *(int *)(iVar2 + 0x88) = iVar1;
        iVar2 = (**(code **)(*(int *)**(undefined4 **)(unaff_EDI + 4) + 0x34))
                          ((int *)**(undefined4 **)(unaff_EDI + 4),0);
        return iVar2;
      }
    }
    iVar2 = (**(code **)(*(int *)**(undefined4 **)(unaff_EDI + 4) + 0x34))
                      ((int *)**(undefined4 **)(unaff_EDI + 4),0);
  }
  return iVar2;
}

