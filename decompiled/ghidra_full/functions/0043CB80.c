/* Raw Ghidra reference; not compilable reconstruction. Address: 0043CB80 */

uint __fastcall FUN_0043cb80(ushort *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  uint unaff_EDI;
  
  uVar2 = 0;
  if (unaff_EDI != 0) {
    uVar2 = (*param_1 ^ 0x9630) - 0x6553;
    iVar3 = (uVar2 >> 0xe & 3) + uVar2 * 4;
    uVar1 = (ushort)iVar3;
    uVar4 = (uVar1 ^ 0x9630) + 0x9aad;
    *param_1 = uVar1;
    uVar4 = (uVar4 >> 0xe) + uVar4 * 4;
    *(int *)(param_1 + 2) = *(int *)(param_1 + 2) + 2;
    *param_1 = uVar4;
    uVar2 = (iVar3 * 0x10000 | (uint)uVar4) % unaff_EDI;
  }
  return uVar2;
}

