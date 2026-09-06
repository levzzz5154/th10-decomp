/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B9E0 */

uint __fastcall NextRandomU32(ushort *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  
  uVar2 = (*param_1 ^ 0x9630) - 0x6553;
  iVar3 = (uVar2 >> 0xe & 3) + uVar2 * 4;
  uVar1 = (ushort)iVar3;
  uVar4 = (uVar1 ^ 0x9630) + 0x9aad;
  *param_1 = uVar1;
  uVar4 = (uVar4 >> 0xe) + uVar4 * 4;
  *(int *)(param_1 + 2) = *(int *)(param_1 + 2) + 2;
  *param_1 = uVar4;
  return iVar3 * 0x10000 | (uint)uVar4;
}

