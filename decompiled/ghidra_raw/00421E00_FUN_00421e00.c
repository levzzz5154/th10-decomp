/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421E00
 * Tracking name: FUN_00421e00
 * Ghidra name: FUN_00421e00
 * Tracked span: 256 bytes
 */


void FUN_00421e00(void)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  
  iVar1 = *(int *)(in_EAX + 21000);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar2 = *(int *)(iVar1 + 0x14) + -1;
      *(int *)(iVar1 + 0x14) = iVar2;
      if (iVar2 < 1) {
        *(undefined4 *)(iVar1 + 0x1c) = 0;
        (**(code **)(*(int *)**(undefined4 **)(iVar1 + 4) + 0x48))
                  ((int *)**(undefined4 **)(iVar1 + 4));
      }
      else {
        FUN_0044d4e0();
      }
    }
    iVar1 = *(int *)(in_EAX + 21000);
    if (*(int *)(iVar1 + 0x1c) == 2) {
      iVar2 = *(int *)(iVar1 + 0x14) + -1;
      *(int *)(iVar1 + 0x14) = iVar2;
      if (iVar2 < 1) {
        *(undefined4 *)(iVar1 + 0x1c) = 0;
      }
      else {
        FUN_0044d4e0();
      }
    }
    iVar1 = *(int *)(in_EAX + 21000);
    if (*(int *)(iVar1 + 0x1c) == 4) {
      iVar2 = *(int *)(iVar1 + 0x14) + -1;
      *(int *)(iVar1 + 0x14) = iVar2;
      if (iVar2 < 1) {
        *(undefined4 *)(iVar1 + 0x1c) = 0;
      }
      else {
        FUN_0044d4e0();
      }
    }
    iVar1 = *(int *)(in_EAX + 21000);
    if (*(int *)(iVar1 + 0x1c) == 3) {
      iVar2 = *(int *)(iVar1 + 0x14) + -1;
      *(int *)(iVar1 + 0x14) = iVar2;
      if (iVar2 < 1) {
        *(undefined4 *)(iVar1 + 0x1c) = 0;
        return;
      }
      FUN_0044d4e0();
    }
  }
  return;
}

