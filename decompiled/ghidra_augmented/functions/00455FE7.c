/* Raw Ghidra reference; not compilable reconstruction. Address: 00455FE7 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint * __fastcall FUN_00455fe7(int param_1,char *param_2)

{
  bool bVar1;
  uint *puVar2;
  char *pcVar3;
  size_t sVar4;
  int iVar5;
  size_t sVar6;
  undefined4 *puVar7;
  undefined **ppuVar8;
  int local_98;
  int local_90;
  uint local_8c [4];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_7c;
  if (param_1 != 0) {
    if (param_2 == (char *)0x0) {
      return (&DAT_0047334c)[param_1 * 3];
    }
    puVar2 = (uint *)FUN_00455d53(param_2);
    return puVar2;
  }
  bVar1 = true;
  local_90 = 0;
  if (param_2 != (char *)0x0) {
    if (((*param_2 == 'L') && (param_2[1] == 'C')) && (param_2[2] == '_')) {
      do {
        pcVar3 = _strpbrk(param_2,"=;");
        if (((pcVar3 == (char *)0x0) || (sVar4 = (int)pcVar3 - (int)param_2, sVar4 == 0)) ||
           (*pcVar3 == ';')) {
          return (uint *)0x0;
        }
        local_98 = 1;
        ppuVar8 = &PTR_s_LC_COLLATE_00473354;
        do {
          iVar5 = _strncmp(*ppuVar8,param_2,sVar4);
          if ((iVar5 == 0) && (sVar6 = _strlen(*ppuVar8), sVar4 == sVar6)) break;
          local_98 = local_98 + 1;
          ppuVar8 = ppuVar8 + 3;
        } while ((int)ppuVar8 < 0x473385);
        pcVar3 = pcVar3 + 1;
        sVar4 = _strcspn(pcVar3,";");
        if ((sVar4 == 0) && (*pcVar3 != ';')) {
          return (uint *)0x0;
        }
        if (local_98 < 6) {
          _strncpy((char *)local_8c,pcVar3,sVar4);
          *(undefined1 *)((int)local_8c + sVar4) = 0;
          iVar5 = FUN_00455d53((char *)local_8c);
          if (iVar5 != 0) {
            local_90 = local_90 + 1;
          }
        }
      } while ((pcVar3[sVar4] != '\0') && (param_2 = pcVar3 + sVar4 + 1, *param_2 != '\0'));
      if (local_90 == 0) {
        return (uint *)0x0;
      }
    }
    else {
      puVar2 = FUN_00455bf3(param_2,local_8c,(undefined2 *)0x0,(undefined4 *)0x0);
      if (puVar2 == (uint *)0x0) {
        return (uint *)0x0;
      }
      puVar7 = &DAT_0047334c;
      do {
        if ((void **)puVar7 != &DAT_0047334c) {
          iVar5 = _strcmp((char *)local_8c,(char *)*puVar7);
          if ((iVar5 == 0) || (iVar5 = FUN_00455d53((char *)local_8c), iVar5 != 0)) {
            local_90 = local_90 + 1;
          }
          else {
            bVar1 = false;
          }
        }
        puVar7 = puVar7 + 3;
      } while ((int)puVar7 < 0x473389);
      if (bVar1) {
        puVar2 = FUN_00455b19();
        _free(DAT_0047334c);
        DAT_0047334c = (void *)0x0;
        return puVar2;
      }
      if (local_90 == 0) {
        return (uint *)0x0;
      }
    }
  }
  puVar2 = FUN_00455b19();
  return puVar2;
}

