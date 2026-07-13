/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00420100
 * Tracking name: FUN_00420100
 * Ghidra name: FUN_00420100
 * Tracked span: 368 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00420100(void)

{
  undefined4 uVar1;
  char *pcVar2;
  size_t local_88;
  char local_84 [128];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_88;
  uVar1 = FUN_00434c30(0x497990);
  if ((char)uVar1 == '\0') {
    pcVar2 = &DAT_0046dfa0;
  }
  else {
    _sprintf(local_84,"th10_%.4x%c.ver",0x100,0x61);
    DAT_0049238c = FUN_0044b360(&local_88,0);
    _DAT_00492388 = local_88;
    if (DAT_0049238c != (byte *)0x0) {
      return 0;
    }
    pcVar2 = &DAT_0046dfc8;
    DAT_0049238c = (byte *)0x0;
  }
  FUN_0044b8e0(pcVar2);
  return 0xffffffff;
}

