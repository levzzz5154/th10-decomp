/* Raw Ghidra reference; not compilable reconstruction. Address: 0043C460 */

/* WARNING: Removing unreachable block (ram,0x0043c48c) */

undefined4 __fastcall FUN_0043c460(int param_1)

{
  byte bVar1;
  int iVar2;
  ulonglong uVar3;
  
  bVar1 = *(byte *)(param_1 + 0x27);
  if (DAT_004918a4 != 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x34) < *(int *)(param_1 + 0x1c)) {
    uVar3 = FUN_00463b2c();
    iVar2 = (uint)bVar1 - (int)uVar3;
    *(int *)(param_1 + 0x18) = iVar2;
    if (iVar2 < 0) {
      *(undefined4 *)(param_1 + 0x18) = 0;
      FUN_00404ed0();
      return 1;
    }
  }
  else {
    iVar2 = *(int *)(param_1 + 0x20) + -1;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(int *)(param_1 + 0x20) = iVar2;
    if (iVar2 < 1) {
      return 0;
    }
    FUN_00405410(0);
  }
  FUN_00404ed0();
  return 1;
}

