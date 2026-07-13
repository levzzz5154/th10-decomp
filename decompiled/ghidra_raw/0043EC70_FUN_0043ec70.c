/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043EC70
 * Tracking name: FUN_0043ec70
 * Ghidra name: FUN_0043ec70
 * Tracked span: 144 bytes
 */


ulonglong __fastcall FUN_0043ec70(int param_1)

{
  int iVar1;
  int in_EAX;
  ulonglong uVar2;
  
  iVar1 = in_EAX + -10000;
  switch(iVar1) {
  case 0:
    return CONCAT44(iVar1,*(undefined4 *)(param_1 + 0x30c));
  case 1:
    return CONCAT44(iVar1,*(undefined4 *)(param_1 + 0x310));
  case 2:
    return CONCAT44(iVar1,*(undefined4 *)(param_1 + 0x314));
  case 3:
    return CONCAT44(iVar1,*(undefined4 *)(param_1 + 0x318));
  case 4:
    uVar2 = FUN_00463b2c();
    return uVar2;
  case 5:
    uVar2 = FUN_00463b2c();
    return uVar2;
  case 6:
    uVar2 = FUN_00463b2c();
    return uVar2;
  case 7:
    uVar2 = FUN_00463b2c();
    return uVar2;
  case 8:
    return CONCAT44(iVar1,*(undefined4 *)(param_1 + 0x32c));
  case 9:
    in_EAX = *(int *)(param_1 + 0x330);
  }
  return CONCAT44(iVar1,in_EAX);
}

