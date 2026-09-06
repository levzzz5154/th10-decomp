/* Raw Ghidra reference; not compilable reconstruction. Address: 00401530 */

void __fastcall AppendGameThreadRecord(int param_1)

{
  int iVar1;
  char cVar2;
  char *in_EAX;
  undefined4 *unaff_EBX;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x896c);
  if (iVar3 < 0x100) {
    iVar1 = iVar3 * 0x68 + 0x76c + param_1;
    *(int *)(param_1 + 0x896c) = iVar3 + 1;
    iVar3 = iVar1 - (int)in_EAX;
    do {
      cVar2 = *in_EAX;
      in_EAX[iVar3] = cVar2;
      in_EAX = in_EAX + 1;
    } while (cVar2 != '\0');
    *(undefined4 *)(iVar1 + 0x40) = *unaff_EBX;
    *(undefined4 *)(iVar1 + 0x44) = unaff_EBX[1];
    *(undefined4 *)(iVar1 + 0x48) = unaff_EBX[2];
    *(undefined4 *)(iVar1 + 0x4c) = *(undefined4 *)(param_1 + 0x8974);
    *(undefined4 *)(iVar1 + 0x50) = *(undefined4 *)(param_1 + 0x8978);
    *(undefined4 *)(iVar1 + 0x54) = *(undefined4 *)(param_1 + 0x897c);
    *(undefined4 *)(iVar1 + 0x5c) = *(undefined4 *)(param_1 + 0x8980);
    *(undefined4 *)(iVar1 + 0x60) = 0;
    *(undefined4 *)(iVar1 + 100) = *(undefined4 *)(param_1 + 0x8988);
  }
  return;
}

