/* Raw Ghidra reference; not compilable reconstruction. Address: 004015C0 */

void __fastcall FUN_004015c0(char *param_1)

{
  int iVar1;
  char cVar2;
  undefined4 *unaff_EBX;
  int unaff_ESI;
  int iVar3;
  
  iVar3 = *(int *)(unaff_ESI + 0x8970);
  if (iVar3 < 0x40) {
    iVar1 = iVar3 * 0x68 + 0x6f6c + unaff_ESI;
    *(int *)(unaff_ESI + 0x8970) = iVar3 + 1;
    iVar3 = iVar1 - (int)param_1;
    do {
      cVar2 = *param_1;
      param_1[iVar3] = cVar2;
      param_1 = param_1 + 1;
    } while (cVar2 != '\0');
    *(undefined4 *)(iVar1 + 0x40) = *unaff_EBX;
    *(undefined4 *)(iVar1 + 0x44) = unaff_EBX[1];
    *(undefined4 *)(iVar1 + 0x48) = unaff_EBX[2];
    *(undefined4 *)(iVar1 + 0x4c) = *(undefined4 *)(unaff_ESI + 0x8974);
    *(undefined4 *)(iVar1 + 0x50) = *(undefined4 *)(unaff_ESI + 0x8978);
    *(undefined4 *)(iVar1 + 0x54) = *(undefined4 *)(unaff_ESI + 0x897c);
    *(undefined4 *)(iVar1 + 0x5c) = *(undefined4 *)(unaff_ESI + 0x8980);
    *(undefined4 *)(iVar1 + 0x60) = 0;
  }
  return;
}

