/* Raw Ghidra reference; not compilable reconstruction. Address: 00421E00 */

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
        SetOperationDeadline();
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
        SetOperationDeadline();
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
        SetOperationDeadline();
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
      SetOperationDeadline();
    }
  }
  return;
}

