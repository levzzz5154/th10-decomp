/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004491C0
 * Tracking name: FUN_004491c0
 * Ghidra name: FUN_004491c0
 * Tracked span: 80 bytes
 */


undefined4 __fastcall FUN_004491c0(undefined4 param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  
  if (param_3 == 0) {
    return 0;
  }
  for (puVar1 = *(undefined4 **)(param_2 + 0x72dad4); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[1]) {
    if (*(int *)*puVar1 == param_3) goto LAB_00449203;
  }
  puVar1 = *(undefined4 **)(param_2 + 0x72dadc);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (*(int *)*puVar1 == param_3) break;
    puVar1 = (undefined4 *)puVar1[1];
  }
LAB_00449203:
  return *puVar1;
}

