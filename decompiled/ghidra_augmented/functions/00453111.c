/* Raw Ghidra reference; not compilable reconstruction. Address: 00453111 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Removing unreachable block (ram,0x00453236) */

undefined4 __cdecl FUN_00453111(LPCSTR param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  BOOL BVar3;
  DWORD DVar4;
  uint uVar5;
  byte *lpBuffer;
  undefined4 local_130;
  CHAR local_12c;
  undefined1 local_12b;
  undefined1 local_12a;
  undefined1 local_129;
  byte local_128 [264];
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046a750;
  uStack_c = 0x453120;
  local_20 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  lpBuffer = local_128;
  local_130 = 0xffffffff;
  BVar3 = SetCurrentDirectoryA(param_1);
  puVar2 = local_1c;
  if (BVar3 != 0) {
    DVar4 = GetCurrentDirectoryA(0x105,(LPSTR)lpBuffer);
    if (0x104 < (int)DVar4) {
      local_1c = &stack0xfffffeb8;
      lpBuffer = &stack0xfffffeb8;
      local_8 = (undefined *)0xffffffff;
      puVar2 = &stack0xfffffeb8;
      if (DVar4 == 0) goto LAB_00453221;
      DVar4 = GetCurrentDirectoryA(DVar4 + 1,&stack0xfffffeb8);
    }
    puVar2 = local_1c;
    if (DVar4 != 0) {
      bVar1 = *lpBuffer;
      if (((bVar1 != 0x5c) && (bVar1 != 0x2f)) || (bVar1 != lpBuffer[1])) {
        local_12c = '=';
        uVar5 = __mbctoupper((uint)*lpBuffer);
        local_12b = (undefined1)uVar5;
        local_12a = 0x3a;
        local_129 = 0;
        BVar3 = SetEnvironmentVariableA(&local_12c,(LPCSTR)lpBuffer);
        puVar2 = local_1c;
        if (BVar3 == 0) goto LAB_00453221;
      }
      local_130 = 0;
      puVar2 = local_1c;
    }
  }
LAB_00453221:
  local_1c = puVar2;
  DVar4 = GetLastError();
  __dosmaperr(DVar4);
  return local_130;
}

