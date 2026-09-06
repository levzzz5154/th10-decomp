/* Raw Ghidra reference; not compilable reconstruction. Address: 0040A450 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x0040a8d7) */
/* WARNING: Removing unreachable block (ram,0x0040a8ea) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0040a450(void *this,void *param_1)

{
  uint *puVar1;
  char cVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  HANDLE pvVar5;
  BOOL BVar6;
  void *pvVar7;
  CHAR *pCVar8;
  undefined4 extraout_ECX;
  int iVar9;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  void *this_00;
  undefined4 extraout_ECX_03;
  int iVar10;
  undefined3 uVar11;
  undefined3 extraout_var;
  void *extraout_ECX_04;
  void *extraout_ECX_05;
  void *extraout_ECX_06;
  char *pcVar12;
  undefined4 *puVar13;
  undefined4 local_184 [5];
  undefined4 local_170;
  _WIN32_FIND_DATAA local_144;
  uint local_4;
  
  uVar3 = DAT_00474e5c;
  local_4 = DAT_00473660 ^ (uint)local_184;
  iVar10 = *(int *)((int)param_1 + 0x30);
  if (iVar10 == 0) {
    FUN_00409eb0();
    iVar10 = 0;
    pvVar5 = FindFirstFileA("../../data/*.ecl",&local_144);
    if (pvVar5 != (HANDLE)0xffffffff) {
      do {
        iVar10 = iVar10 + 1;
        BVar6 = FindNextFileA(pvVar5,&local_144);
      } while (BVar6 != 0);
    }
    FindClose(pvVar5);
    iVar9 = 0;
    *(int *)((int)param_1 + 0x38) = iVar10;
    if (iVar10 != 0) {
      pvVar7 = _malloc(iVar10 * 4);
      *(void **)((int)param_1 + 0x34) = pvVar7;
      pvVar5 = FindFirstFileA("../../data/*.ecl",&local_144);
      if (0 < iVar10) {
        do {
          pCVar8 = local_144.cFileName;
          do {
            cVar2 = *pCVar8;
            pCVar8 = pCVar8 + 1;
          } while (cVar2 != '\0');
          pvVar7 = _malloc((size_t)(pCVar8 + (1 - (int)(local_144.cFileName + 1))));
          *(void **)(*(int *)((int)param_1 + 0x34) + iVar9 * 4) = pvVar7;
          pcVar12 = *(char **)(*(int *)((int)param_1 + 0x34) + iVar9 * 4);
          pCVar8 = local_144.cFileName;
          do {
            cVar2 = *pCVar8;
            pCVar8 = pCVar8 + 1;
            *pcVar12 = cVar2;
            pcVar12 = pcVar12 + 1;
          } while (cVar2 != '\0');
          BVar6 = FindNextFileA(pvVar5,&local_144);
        } while ((BVar6 != 0) && (iVar9 = iVar9 + 1, iVar9 < iVar10));
      }
      FindClose(pvVar5);
    }
    *(undefined4 *)((int)param_1 + 0x44) = 3;
    *(undefined4 *)((int)param_1 + 0x10c) = 1;
    iVar9 = *(int *)((int)param_1 + 0x44);
    if (iVar9 == 0) {
      *(undefined4 *)((int)param_1 + 0x3c) = 0;
    }
    else if (iVar9 < 1) {
      *(int *)((int)param_1 + 0x3c) = iVar9 + -1;
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
    *(undefined4 *)((int)param_1 + 0x674) = 0;
    *(undefined4 *)((int)param_1 + 0x678) = 0x42000000;
    *(undefined4 *)((int)param_1 + 0x67c) = 0;
    *(undefined4 *)((int)param_1 + 0x680) = 1000;
  }
  else if (iVar10 == 1) {
    *(undefined4 *)((int)param_1 + 0x40) = *(undefined4 *)((int)param_1 + 0x3c);
    uVar4 = CONCAT31((int3)((uint)this >> 8),DAT_00474e36);
    if (((DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
      uVar4 = extraout_ECX_00;
    }
    if (((DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
      uVar4 = extraout_ECX_01;
    }
    iVar10 = *(int *)((int)param_1 + 0x3c);
    if (iVar10 == 0) {
      *(undefined4 *)((int)param_1 + 0x118) = *(undefined4 *)((int)param_1 + 0x114);
      uVar11 = (undefined3)((uint)uVar4 >> 8);
      if (((DAT_00474e36 & 0x80) != 0) || ((DAT_00474e34 & 0x80) != 0)) {
        FUN_0044bea0(1);
        uVar11 = extraout_var;
      }
      pvVar7 = (void *)CONCAT31(uVar11,DAT_00474e36);
      if (((DAT_00474e36 & 0x40) != 0) || ((DAT_00474e34 & 0x40) != 0)) {
        FUN_0044bea0(-1);
        pvVar7 = extraout_ECX_04;
      }
      if ((CONCAT11(uRam00474e37,DAT_00474e36) & 0x1001) != 0) {
        FUN_004148e0(pvVar7);
        FUN_00425090(extraout_ECX_05);
        FUN_00406140();
        FUN_00405730();
        FUN_0041afb0();
        FUN_0042b6d0();
        FUN_0040d730(extraout_ECX_06);
        *(uint *)((int)param_1 + 0x684) = *(uint *)((int)param_1 + 0x684) & 0xfffffffd;
        FUN_0044c1c0(param_1);
        *(undefined4 *)((int)param_1 + 0x30) = 2;
      }
    }
    else if (iVar10 == 1) {
      if (DAT_00477704 != 0) {
        *(undefined4 *)((int)param_1 + 0x1f0) = *(undefined4 *)((int)param_1 + 0x1ec);
        uVar4 = FUN_0040ace0(0x474e30);
        if ((short)uVar4 != 0) {
          FUN_0044bea0(1);
        }
        uVar4 = FUN_0040ace0(0x474e30);
        if ((short)uVar4 != 0) {
          FUN_0044bea0(-1);
        }
        if ((_DAT_00474e38 & 0x1001) != 0) {
          FUN_0040a010();
          FUN_00424d90();
          FUN_00409e20();
          FUN_00405ed0(extraout_ECX_02);
          iVar10 = DAT_00477704;
          FUN_0040d510();
          FUN_00409f90(this_00,iVar10);
          FUN_00413bc0(extraout_ECX_03);
          iVar10 = DAT_00477818;
          FUN_00409e20();
          puVar13 = (undefined4 *)(iVar10 + 0x14);
          for (iVar9 = 0x873a8; iVar9 != 0; iVar9 = iVar9 + -1) {
            *puVar13 = 0;
            puVar13 = puVar13 + 1;
          }
          puVar13 = local_184;
          for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
            *puVar13 = 0;
            puVar13 = puVar13 + 1;
          }
          local_184[0] = 0;
          local_184[1] = 0;
          local_184[2] = 0;
          local_170 = 10000;
          FUN_0040cfb0(DAT_00477704,
                       *(void **)(*(int *)(*(int *)(DAT_00477704 + 0x54) + 0x8c) +
                                 *(int *)((int)param_1 + 0x1ec) * 8));
          *(undefined4 *)((int)param_1 + 0x30) = 4;
        }
      }
    }
    else if ((iVar10 == 2) && ((CONCAT11(uRam00474e37,DAT_00474e36) & 0x1001) != 0)) {
      FUN_0040ac90(3);
    }
  }
  else if (iVar10 == 4) {
    DAT_00474e5c = DAT_00474e30;
    _DAT_00474e5e = uVar3;
    FUN_0040ac20(0x474e30);
    iVar10 = DAT_00477834;
    DAT_00474e62 = CONCAT11(uRam00474e37,DAT_00474e36);
    if ((DAT_00474e36 & 8) != 0) {
      if (*(int *)(DAT_00477834 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477834 + 8) + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      if (*(int *)(iVar10 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar10 + 0xc) + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      FUN_00424d90();
      iVar10 = DAT_004776f0;
      if (*(int *)(DAT_004776f0 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_004776f0 + 8) + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      if (*(int *)(iVar10 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar10 + 0xc) + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      FUN_00405ed0(extraout_ECX);
      iVar10 = DAT_00477704;
      if (*(int *)(DAT_00477704 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477704 + 8) + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      pvVar7 = *(void **)(iVar10 + 0xc);
      if (pvVar7 != (void *)0x0) {
        *(uint *)((int)pvVar7 + 4) = *(uint *)((int)pvVar7 + 4) & 0xfffffffd;
      }
      FUN_00409f90(pvVar7,iVar10);
      iVar10 = DAT_00477818;
      if (*(int *)(DAT_00477818 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477818 + 8) + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      iVar9 = *(int *)(iVar10 + 0xc);
      if (iVar9 != 0) {
        puVar1 = (uint *)(iVar9 + 4);
        *puVar1 = *puVar1 & 0xfffffffd;
      }
      puVar13 = (undefined4 *)(iVar10 + 0x14);
      for (iVar9 = 0x873a8; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar13 = 0;
        puVar13 = puVar13 + 1;
      }
      *(undefined4 *)((int)param_1 + 0x30) = 1;
    }
  }
  return 1;
}

