/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00420B10
 * Tracking name: FUN_00420b10
 * Ghidra name: FUN_00420b10
 * Tracked span: 240 bytes
 */


undefined4 __thiscall FUN_00420b10(void *this,undefined4 param_1,int param_2)

{
  void *extraout_ECX;
  
  if (((byte)DAT_00491d78 & 0x10) != 0) {
    FUN_0043e460(this,"dummy",4,0);
    this = extraout_ECX;
  }
  FUN_0043e460(this,"dummy",2,param_1);
  *(undefined1 *)(DAT_0047783c + 0x1d892 + param_2) = 1;
  return 0;
}

