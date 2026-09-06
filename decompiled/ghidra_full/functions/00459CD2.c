/* Raw Ghidra reference; not compilable reconstruction. Address: 00459CD2 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl FUN_00459cd2(uint param_1,char *param_2,uint param_3)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  BOOL BVar4;
  int *piVar5;
  ulong *puVar6;
  uint uVar7;
  int iVar8;
  DWORD local_428;
  char *local_424;
  int local_420;
  DWORD local_41c;
  char *local_418;
  int local_414;
  ulong local_410;
  char local_40c [100];
  undefined1 local_3a8 [928];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_3a8;
  local_424 = param_2;
  local_41c = 0;
  local_420 = 0;
  if (param_3 == 0) {
    return 0;
  }
  piVar5 = &DAT_00499200 + ((int)param_1 >> 5);
  iVar8 = (param_1 & 0x1f) * 0x24;
  if ((*(byte *)(*piVar5 + 4 + iVar8) & 0x20) != 0) {
    __lseeki64_lk(param_1,0,0,2);
  }
  if ((*(byte *)((undefined4 *)(*piVar5 + iVar8) + 1) & 0x80) == 0) {
    BVar4 = WriteFile(*(HANDLE *)(*piVar5 + iVar8),param_2,param_3,&local_428,(LPOVERLAPPED)0x0);
    if (BVar4 == 0) {
LAB_00459e0a:
      local_410 = GetLastError();
    }
    else {
      local_410 = 0;
      local_41c = local_428;
    }
  }
  else {
    local_418 = param_2;
    local_410 = 0;
    if (param_3 == 0) goto LAB_00459e49;
    do {
      local_414 = 0;
      uVar7 = (int)local_418 - (int)local_424;
      pcVar3 = local_40c;
      do {
        if (param_3 <= uVar7) break;
        pcVar1 = local_418 + 1;
        cVar2 = *local_418;
        uVar7 = uVar7 + 1;
        if (cVar2 == '\n') {
          local_420 = local_420 + 1;
          *pcVar3 = '\r';
          pcVar3 = pcVar3 + 1;
          local_414 = local_414 + 1;
        }
        *pcVar3 = cVar2;
        pcVar3 = pcVar3 + 1;
        local_414 = local_414 + 1;
        local_418 = pcVar1;
      } while (local_414 < 0x400);
      BVar4 = WriteFile(*(HANDLE *)(*piVar5 + iVar8),local_40c,(int)pcVar3 - (int)local_40c,
                        &local_428,(LPOVERLAPPED)0x0);
      if (BVar4 == 0) goto LAB_00459e0a;
      local_41c = local_41c + local_428;
    } while (((int)pcVar3 - (int)local_40c <= (int)local_428) &&
            ((uint)((int)local_418 - (int)local_424) < param_3));
  }
  if (local_41c != 0) {
    return local_41c - local_420;
  }
  param_2 = local_424;
  if (local_410 != 0) {
    if (local_410 == 5) {
      piVar5 = FUN_00456af2();
      *piVar5 = 9;
      puVar6 = FUN_00456afb();
      *puVar6 = 5;
      return -1;
    }
    __dosmaperr(local_410);
    return -1;
  }
LAB_00459e49:
  if (((*(byte *)(*piVar5 + 4 + iVar8) & 0x40) != 0) && (*param_2 == '\x1a')) {
    return 0;
  }
  piVar5 = FUN_00456af2();
  *piVar5 = 0x1c;
  puVar6 = FUN_00456afb();
  *puVar6 = 0;
  return -1;
}

