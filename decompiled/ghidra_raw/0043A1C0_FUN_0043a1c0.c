/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043A1C0
 * Tracking name: FUN_0043a1c0
 * Ghidra name: FUN_0043a1c0
 * Tracked span: 208 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0043a1c0(void)

{
  DWORD DVar1;
  byte *_Memory;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  size_t local_110;
  CHAR local_10c [264];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_110;
  DVar1 = GetModuleFileNameA((HMODULE)0x0,local_10c,0x105);
  if (DVar1 == 0) {
    return -1;
  }
  iVar4 = 0;
  _Memory = FUN_0044b360(&local_110,1);
  if (_Memory != (byte *)0x0) {
    iVar2 = ((int)(local_110 + ((int)local_110 >> 0x1f & 3U)) >> 2) + -1;
    pbVar3 = _Memory;
    if (0 < iVar2) {
      do {
        iVar4 = iVar4 + *(int *)pbVar3;
        iVar2 = iVar2 + -1;
        pbVar3 = pbVar3 + 4;
      } while (iVar2 != 0);
    }
    _free(_Memory);
    _DAT_00492384 = local_110;
    _DAT_00492380 = iVar4;
    return iVar4;
  }
  return -1;
}

