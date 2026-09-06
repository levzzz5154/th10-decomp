/* Raw Ghidra reference; not compilable reconstruction. Address: 0042BFC0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x0042c304) */
/* WARNING: Removing unreachable block (ram,0x0042c317) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0042bfc0(void *param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  HANDLE pvVar5;
  BOOL BVar6;
  void *pvVar7;
  CHAR *pCVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  _WIN32_FIND_DATAA local_144;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_144;
  iVar10 = *(int *)((int)param_1 + 0x30);
  if (iVar10 == 0) {
    FUN_0042bad0();
    iVar10 = 0;
    pvVar5 = FindFirstFileA("../../data/*.ecl",&local_144);
    if (pvVar5 != (HANDLE)0xffffffff) {
      do {
        iVar10 = iVar10 + 1;
        BVar6 = FindNextFileA(pvVar5,&local_144);
      } while (BVar6 != 0);
    }
    FindClose(pvVar5);
    iVar11 = 0;
    *(int *)((int)param_1 + 0x38) = iVar10;
    if (iVar10 != 0) {
      pvVar7 = _malloc(iVar10 * 4);
      *(void **)((int)param_1 + 0x34) = pvVar7;
      pvVar5 = FindFirstFileA("../../data/*.ecl",&local_144);
      if (0 < iVar10) {
        do {
          pCVar8 = local_144.cFileName;
          do {
            cVar1 = *pCVar8;
            pCVar8 = pCVar8 + 1;
          } while (cVar1 != '\0');
          pvVar7 = _malloc((size_t)(pCVar8 + (1 - (int)(local_144.cFileName + 1))));
          *(void **)(*(int *)((int)param_1 + 0x34) + iVar11 * 4) = pvVar7;
          pcVar9 = *(char **)(*(int *)((int)param_1 + 0x34) + iVar11 * 4);
          pCVar8 = local_144.cFileName;
          do {
            cVar1 = *pCVar8;
            pCVar8 = pCVar8 + 1;
            *pcVar9 = cVar1;
            pcVar9 = pcVar9 + 1;
          } while (cVar1 != '\0');
          BVar6 = FindNextFileA(pvVar5,&local_144);
        } while ((BVar6 != 0) && (iVar11 = iVar11 + 1, iVar11 < iVar10));
      }
      FindClose(pvVar5);
    }
    *(undefined4 *)((int)param_1 + 0x44) = 3;
    *(undefined4 *)((int)param_1 + 0x10c) = 1;
    iVar11 = *(int *)((int)param_1 + 0x44);
    if (iVar11 == 0) {
      *(undefined4 *)((int)param_1 + 0x3c) = 0;
    }
    else if (iVar11 < 1) {
      *(int *)((int)param_1 + 0x3c) = iVar11 + -1;
    }
    else {
      *(undefined4 *)((int)param_1 + 0x3c) = 0;
    }
    *(int *)((int)param_1 + 0x11c) = iVar10;
    *(undefined4 *)((int)param_1 + 0x1e4) = 1;
    if (iVar10 == 0) {
      *(undefined4 *)((int)param_1 + 0x114) = 0;
    }
    else if (iVar10 < 1) {
      *(int *)((int)param_1 + 0x114) = iVar10 + -1;
    }
    else {
      *(undefined4 *)((int)param_1 + 0x114) = 0;
    }
    *(undefined4 *)((int)param_1 + 500) = 1;
    *(undefined4 *)((int)param_1 + 700) = 1;
    *(undefined4 *)((int)param_1 + 0x1ec) = 0;
    *(undefined4 *)((int)param_1 + 0x30) = 1;
    *(undefined4 *)((int)param_1 + 0x2c4) = 0;
    *(undefined4 *)((int)param_1 + 0x2c8) = 0x42000000;
    *(undefined4 *)((int)param_1 + 0x2cc) = 0;
    *(undefined4 *)((int)param_1 + 0x2d0) = 1000;
  }
  else if (iVar10 == 1) {
    *(undefined4 *)((int)param_1 + 0x40) = *(undefined4 *)((int)param_1 + 0x3c);
    if (((DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    if (((DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    iVar10 = *(int *)((int)param_1 + 0x3c);
    if (iVar10 == 0) {
      *(undefined4 *)((int)param_1 + 0x118) = *(undefined4 *)((int)param_1 + 0x114);
      if (((DAT_00474e36 & 0x80) != 0) || ((DAT_00474e34 & 0x80) != 0)) {
        FUN_0044bea0(1);
      }
      if (((DAT_00474e36 & 0x40) != 0) || ((DAT_00474e34 & 0x40) != 0)) {
        FUN_0044bea0(-1);
      }
      if ((CONCAT11(uRam00474e37,DAT_00474e36) & 0x1001) != 0) {
        *(uint *)((int)param_1 + 0x2d4) = *(uint *)((int)param_1 + 0x2d4) & 0xfffffffd;
        FUN_0044c1c0(param_1);
        *(undefined4 *)((int)param_1 + 0x30) = 2;
      }
    }
    else if (iVar10 == 1) {
      if (*(int *)((int)param_1 + 0x2d8) != 0) {
        *(undefined4 *)((int)param_1 + 0x1f0) = *(undefined4 *)((int)param_1 + 0x1ec);
        uVar3 = FUN_0040ace0(0x474e30);
        if ((short)uVar3 != 0) {
          FUN_0044bea0(1);
        }
        uVar3 = FUN_0040ace0(0x474e30);
        if ((short)uVar3 != 0) {
          FUN_0044bea0(-1);
        }
        if ((_DAT_00474e38 & 0x1001) != 0) {
          if (*(int **)((int)param_1 + 0x2dc) != (int *)0x0) {
            (**(code **)(**(int **)((int)param_1 + 0x2dc) + 0x14))(1);
            *(undefined4 *)((int)param_1 + 0x2dc) = 0;
          }
          puVar4 = FUN_00450500(*(byte **)(*(int *)(*(int *)((int)param_1 + 0x2d8) + 0x8c) +
                                          *(int *)((int)param_1 + 0x1ec) * 8));
          *(undefined4 **)((int)param_1 + 0x2dc) = puVar4;
          *(undefined4 *)((int)param_1 + 0x30) = 4;
        }
      }
    }
    else if ((iVar10 == 2) && ((CONCAT11(uRam00474e37,DAT_00474e36) & 0x1001) != 0)) {
      FUN_0040ac90(3);
    }
  }
  else if (iVar10 == 4) {
    FUN_0044fd10(1.0);
    piVar2 = *(int **)((int)param_1 + 0x2dc);
    if (piVar2 != (int *)0x0) {
      if (*(int *)(piVar2[1] + 4) != 0) {
        return 1;
      }
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 0x14))(1);
      }
    }
    *(undefined4 *)((int)param_1 + 0x2dc) = 0;
    *(undefined4 *)((int)param_1 + 0x30) = 1;
  }
  return 1;
}

