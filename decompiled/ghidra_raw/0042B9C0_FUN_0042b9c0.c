/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042B9C0
 * Tracking name: FUN_0042b9c0
 * Ghidra name: FUN_0042b9c0
 * Tracked span: 2464 bytes
 */


void FUN_0042b9c0(undefined4 param_1)

{
  undefined1 *puVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  undefined4 *unaff_EDI;
  
  if (0x2cf < *(int *)(unaff_ESI + 0x14)) {
    *(undefined4 *)(unaff_ESI + 0x14) = 0;
  }
  puVar1 = (undefined1 *)(*(int *)(unaff_ESI + 0x14) * 0x40 + 0x3c4 + unaff_ESI);
  iVar3 = 0;
  puVar1[0x38] = 1;
  if (in_EAX < 0) {
    *puVar1 = 10;
  }
  else {
    if (in_EAX != 0) {
      do {
        iVar2 = in_EAX / 10;
        iVar4 = iVar3 + 1;
        puVar1[iVar3] = (char)(in_EAX % 10);
        in_EAX = iVar2;
        iVar3 = iVar4;
      } while (iVar2 != 0);
      if (iVar4 != 0) goto LAB_0042ba10;
    }
    *puVar1 = 0;
  }
  iVar4 = 1;
LAB_0042ba10:
  puVar1[0x39] = (char)iVar4;
  *(undefined4 *)(puVar1 + 0x18) = param_1;
  if ((*(uint *)(puVar1 + 0x2c) & 1) == 0) {
    *(undefined4 *)(puVar1 + 0x20) = 0;
    *(undefined4 *)(puVar1 + 0x1c) = 0xfff0bdc1;
    *(undefined4 *)(puVar1 + 0x24) = 0;
    *(undefined4 **)(puVar1 + 0x28) = &DAT_00476f78;
    *(uint *)(puVar1 + 0x2c) = *(uint *)(puVar1 + 0x2c) | 1;
  }
  *(undefined4 *)(puVar1 + 0x20) = 0;
  *(undefined4 *)(puVar1 + 0x24) = 0;
  *(undefined4 *)(puVar1 + 0x1c) = 0xffffffff;
  *(undefined4 *)(puVar1 + 0xc) = *unaff_EDI;
  *(undefined4 *)(puVar1 + 0x10) = unaff_EDI[1];
  *(undefined4 *)(puVar1 + 0x14) = unaff_EDI[2];
  *(int *)(unaff_ESI + 0x14) = *(int *)(unaff_ESI + 0x14) + 1;
  return;
}

