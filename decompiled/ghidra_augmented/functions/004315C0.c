/* Raw Ghidra reference; not compilable reconstruction. Address: 004315C0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004315c0(int param_1)

{
  int *piVar1;
  char cVar2;
  void *_Memory;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  HANDLE hFindFile;
  BOOL BVar6;
  undefined4 uVar7;
  char *pcVar8;
  undefined4 extraout_ECX;
  int iVar9;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  char *pcVar10;
  int iVar11;
  undefined1 local_188 [4];
  _WIN32_FIND_DATAA local_184;
  char local_44 [64];
  uint local_4;
  
  uVar3 = DAT_00491c04;
  local_4 = DAT_00473660 ^ (uint)local_188;
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 0x19;
    FUN_0040ad20(uVar3,(uint *)(param_1 + 0x24));
    DAT_00491c04 = 0;
    iVar11 = FUN_004491c0(extraout_ECX,(int)g_pGameStateManager,*(int *)(param_1 + 0x43c));
    if (iVar11 == 0) {
      FUN_0042c670(param_1);
      puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)((int)g_pGameThread + 0x8994),8,0xf);
      *(undefined4 *)(param_1 + 0x5d0) = *puVar4;
    }
    FUN_0042c670(param_1);
    FUN_0042c620(1);
    puVar4 = (undefined4 *)(param_1 + 0x59e4);
    puVar5 = puVar4;
    for (iVar11 = 0x32; iVar11 != 0; iVar11 = iVar11 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    iVar11 = 1;
    do {
      _sprintf(local_44,"th10_%.2d.rpy",iVar11);
      puVar5 = FUN_004296f0(local_44);
      *puVar4 = puVar5;
      iVar11 = iVar11 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar11 < 0x1a);
    FUN_00452abc("replay");
    FUN_00453111("replay");
    hFindFile = FindFirstFileA("th10_ud????.rpy",&local_184);
    if (hFindFile != (HANDLE)0xffffffff) {
      iVar11 = 0x19;
      puVar4 = (undefined4 *)(param_1 + 0x5a48);
      do {
        FUN_00453111("../");
        puVar5 = FUN_004296f0(local_184.cFileName);
        *puVar4 = puVar5;
        FUN_00453111("replay");
        BVar6 = FindNextFileA(hFindFile,&local_184);
        if (BVar6 == 0) break;
        iVar11 = iVar11 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar11 < 0x32);
    }
    FindClose(hFindFile);
    FUN_00453111("../");
    *(undefined4 *)(param_1 + 23000) = 0;
    goto LAB_0043174f;
  case 1:
LAB_0043174f:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      *(undefined4 *)(param_1 + 0x20) = 2;
      if ((*(uint *)(param_1 + 0x2c0) & 1) == 0) {
        *(undefined4 *)(param_1 + 0x2b4) = 0;
        *(undefined4 *)(param_1 + 0x2b0) = 0xfff0bdc1;
        *(undefined4 *)(param_1 + 0x2b8) = 0;
        *(undefined4 **)(param_1 + 700) = &DAT_00476f78;
        *(uint *)(param_1 + 0x2c0) = *(uint *)(param_1 + 0x2c0) | 1;
      }
      *(undefined4 *)(param_1 + 0x2b4) = 0;
      *(undefined4 *)(param_1 + 0x2b8) = 0;
      *(undefined4 *)(param_1 + 0x2b0) = 0xffffffff;
    }
    break;
  case 2:
    piVar1 = (int *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    if (*(int *)(param_1 + 0x28) != *piVar1) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 10) == 0) {
      if ((_DAT_00474e36 & 0x1001) == 0) {
        return 1;
      }
      if (*(int *)(param_1 + 0x59e4 + *piVar1 * 4) == 0) {
        return 1;
      }
      FUN_0042c620(4);
      *(int *)(param_1 + 0x59dc) = *piVar1;
      FUN_0044be20();
      FUN_0043dc90(&DAT_00492590,0);
      *(undefined4 *)(param_1 + 0x2c) = 7;
      iVar11 = *(int *)(param_1 + 0x2c);
      if (iVar11 == 0) {
        *piVar1 = 0;
      }
      else if (iVar11 < 1) {
        *piVar1 = iVar11 + -1;
      }
      else {
        *piVar1 = 0;
      }
      iVar9 = 0;
      iVar11 = 0;
      do {
        if (*(int *)(*(int *)(param_1 + 0x59e4 + *(int *)(param_1 + 0x59dc) * 4) + 0xd4 + iVar11) ==
            0) {
          *(int *)(param_1 + 0xb4 + *(int *)(param_1 + 0xf8) * 4) = iVar9;
          *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
        }
        iVar11 = iVar11 + 0x24;
        iVar9 = iVar9 + 1;
      } while (iVar11 < 0xfc);
      FUN_0044bea0(-1);
      FUN_0044bea0(1);
      return 1;
    }
    uVar7 = 5;
    goto LAB_0043181a;
  case 3:
    if (*(int *)(param_1 + 0x2b4) == 2) {
      FUN_0043c8b0(5,0x20,0,0,0);
      FUN_0040c540();
    }
    if (0x1f < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c5c0(3);
      DAT_00474c7c = *(int *)(param_1 + 0x59e0) + 1;
      DAT_00477848 = &DAT_00474788 + DAT_00474c7c * 0x30;
      DAT_00474c80 = DAT_00474c7c;
      FUN_00420c30();
      DAT_00491fb8 = 0xc;
      pcVar8 = (char *)(*(int *)(param_1 + 0x59e4 + *(int *)(param_1 + 0x59dc) * 4) + 0x1d4);
      pcVar10 = &DAT_00477710;
      do {
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        *pcVar10 = cVar2;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      iVar11 = *(int *)(*(int *)(param_1 + 0x59e4 + *(int *)(param_1 + 0x59dc) * 4) + 0x18);
      DAT_00474c68 = *(undefined4 *)(iVar11 + 0x50);
      DAT_00474c6c = *(undefined4 *)(iVar11 + 0x54);
      DAT_00474c74 = *(undefined4 *)(iVar11 + 0x58);
      DAT_00491c04 = *(uint *)(param_1 + 0x59dc);
      DAT_00491c00 = 2;
    }
    break;
  case 4:
    if (*(int *)(param_1 + 0x2b4) < 0xf) {
      return 1;
    }
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    uVar7 = FUN_0040ace0(0x474e30);
    if ((short)uVar7 != 0) {
      FUN_0044bea0(-1);
    }
    uVar7 = FUN_0040ace0(0x474e30);
    if ((short)uVar7 != 0) {
      FUN_0044bea0(1);
    }
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 10) == 0) {
      if ((_DAT_00474e36 & 0x1001) == 0) {
        return 1;
      }
      *(int *)(param_1 + 0x59e0) = *(int *)(param_1 + 0x24);
      FUN_0042c620(3);
      return 1;
    }
    FUN_0044be70();
    *(undefined4 *)(param_1 + 0x2c) = 0x19;
    *(undefined4 *)(param_1 + 0xf8) = 0;
    uVar7 = 2;
LAB_0043181a:
    FUN_0042c620(uVar7);
    FUN_0043dc90(&DAT_00492590,0);
    break;
  case 5:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      puVar4 = (undefined4 *)(param_1 + 0x59e4);
      iVar11 = 0x32;
      do {
        _Memory = (void *)*puVar4;
        if (_Memory != (void *)0x0) {
          FUN_004294a0((int)_Memory);
          _free(_Memory);
        }
        puVar4 = puVar4 + 1;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      puVar4 = (undefined4 *)(param_1 + 0x59e4);
      for (iVar11 = 0x32; iVar11 != 0; iVar11 = iVar11 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      FUN_0042c6d0(0);
      FUN_0042c770(0x5a);
      FUN_0042c770(0x5b);
      FUN_0042c6d0(extraout_ECX_00);
      FUN_00409e50(extraout_ECX_01);
      FUN_0042c5c0(2);
      piVar1 = (int *)(param_1 + 0xb0);
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        *(undefined4 *)(param_1 + 0xb0) = 0;
      }
      *(undefined4 *)(param_1 + 0x24) =
           *(undefined4 *)(param_1 + 0x30 + *(int *)(param_1 + 0xb0) * 4);
      *(undefined4 *)(param_1 + 0x2c) =
           *(undefined4 *)(param_1 + 0x70 + *(int *)(param_1 + 0xb0) * 4);
      *(undefined4 *)(param_1 + 0xf8) = 0;
    }
  }
  return 1;
}

