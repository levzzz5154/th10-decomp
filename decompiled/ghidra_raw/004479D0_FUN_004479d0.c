/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004479D0
 * Tracking name: FUN_004479d0
 * Ghidra name: FUN_004479d0
 * Tracked span: 128 bytes
 */


void FUN_004479d0(int *param_1,int param_2,COLORREF param_3,int param_4)

{
  int in_EAX;
  char *unaff_EBX;
  ulonglong uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (in_EAX < 1) {
    in_EAX = 0x11;
  }
  else if (in_EAX < 9) {
    return;
  }
  uVar1 = FUN_00463b2c();
  local_10 = (undefined4)uVar1;
  uVar1 = FUN_00463b2c();
  local_c = (undefined4)uVar1;
  uVar1 = FUN_00463b2c();
  local_8 = (undefined4)uVar1;
  uVar1 = FUN_00463b2c();
  local_4 = (undefined4)uVar1;
  if (param_4 != 0) {
    FUN_00437fe0(&local_10,param_2,in_EAX,param_3,unaff_EBX,param_1);
    return;
  }
  FUN_00437db0(&local_10,param_2,in_EAX,param_3,unaff_EBX,param_1);
  return;
}

