/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00420C00
 * Tracking name: FUN_00420c00
 * Ghidra name: FUN_00420c00
 * Tracked span: 48 bytes
 */


undefined4 __fastcall FUN_00420c00(undefined4 param_1)

{
  if (((byte)DAT_00491d78 & 0x10) != 0) {
    FUN_0043e460(param_1,"dummy",4,0);
    return 0;
  }
  FUN_0043e460(param_1,"dummy",3,0);
  return 0;
}

