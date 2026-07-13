/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00441E50
 * Tracking name: FUN_00441e50
 * Ghidra name: FUN_00441e50
 * Tracked span: 160 bytes
 */


void FUN_00441e50(void)

{
  undefined4 *unaff_ESI;
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  
  uVar1 = FUN_00463b2c();
  uVar2 = FUN_00463b2c();
  uVar3 = FUN_00463b2c();
  unaff_ESI[2] = (int)uVar2;
  *unaff_ESI = (int)uVar3;
  unaff_ESI[1] = (int)uVar1;
  return;
}

