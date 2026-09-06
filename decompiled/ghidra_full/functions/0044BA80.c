/* Raw Ghidra reference; not compilable reconstruction. Address: 0044BA80 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_0044ba80(ushort *param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  
  uVar4 = (*param_1 ^ 0x9630) - 0x6553;
  uVar4 = uVar4 * 4 + (uVar4 >> 0xe & 3);
  uVar2 = (ushort)uVar4;
  *param_1 = uVar2;
  uVar4 = (uVar4 ^ 0x9630) - 0x6553;
  uVar4 = uVar4 * 4 + (uVar4 >> 0xe & 3);
  uVar3 = (ushort)uVar4;
  *param_1 = uVar3;
  uVar4 = (uVar4 ^ 0x9630) - 0x6553;
  uVar1 = (((ushort)(uVar4 >> 0xe) & 3) + (short)uVar4 * 4 ^ 0x9630) + 0x9aad;
  *(int *)(param_1 + 2) = *(int *)(param_1 + 2) + 4;
  *param_1 = (uVar1 >> 0xe) + uVar1 * 4;
  return CONCAT22(uVar3,uVar2);
}

