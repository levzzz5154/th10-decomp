/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044A0C0
 * Tracking name: FUN_0044a0c0
 * Ghidra name: FUN_0044a0c0
 * Tracked span: 208 bytes
 */


undefined4 FUN_0044a0c0(void)

{
  MMRESULT MVar1;
  char *pcVar2;
  joyinfoex_tag local_34;
  
  local_34.dwSize = 0x34;
  local_34.dwFlags = 0xff;
  MVar1 = joyGetPosEx(0,&local_34);
  if (MVar1 != 0) {
    MVar1 = joyGetPosEx(1,&local_34);
    if (MVar1 != 0) {
      pcVar2 = FUN_0044b810(&DAT_00474f70,&DAT_00470580);
      return CONCAT22((short)((uint)pcVar2 >> 0x10),1);
    }
  }
  MVar1 = joyGetDevCapsA(0,(LPJOYCAPSA)&DAT_004918b8,0x194);
  return MVar1 & 0xffff0000;
}

