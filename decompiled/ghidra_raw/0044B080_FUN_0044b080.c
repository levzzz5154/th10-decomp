/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B080
 * Tracking name: FUN_0044b080
 * Ghidra name: FUN_0044b080
 * Tracked span: 80 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_0044b080(void)

{
  int iVar1;
  byte local_104 [256];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_104;
  GetKeyboardState(local_104);
  iVar1 = 0;
  do {
    local_104[iVar1] = local_104[iVar1] & 0x7f;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  SetKeyboardState(local_104);
  return;
}

