/* Raw Ghidra reference; not compilable reconstruction. Address: 00417C80 */

void FUN_00417c80(int param_1)

{
  uint *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  void *extraout_ECX_02;
  void *extraout_ECX_03;
  void *extraout_ECX_04;
  void *extraout_ECX_05;
  void *extraout_ECX_06;
  void *extraout_ECX_07;
  void *extraout_ECX_08;
  void *extraout_ECX_09;
  void *extraout_ECX_10;
  void *extraout_ECX_11;
  void *extraout_ECX_12;
  void *extraout_ECX_13;
  void *extraout_ECX_14;
  int iVar4;
  void *pvVar5;
  void *extraout_ECX_15;
  void *extraout_ECX_16;
  void *extraout_ECX_17;
  void *extraout_ECX_18;
  void *extraout_ECX_19;
  void *extraout_ECX_20;
  void *extraout_ECX_21;
  undefined4 *puVar6;
  undefined4 uVar7;
  
  FUN_0042b1e0();
  DAT_00474ca0 = DAT_00474ca0 & 0xfffffffc;
  DAT_00476f78 = 0x3f800000;
  if (DAT_00491fb8 == 10) {
    puVar6 = (undefined4 *)((int)g_pGameThread + 0x89a4);
    if (*(int *)((int)g_pGameThread + 0x89a4) == 0) {
      puVar3 = (undefined4 *)FUN_00448d50(*(undefined2 **)((int)g_pGameThread + 0x8994));
      *puVar6 = *puVar3;
    }
    pvVar5 = DAT_00474c80;
    if (DAT_00474c80 == DAT_00474c7c) {
      DAT_00474ca0 = DAT_00474ca0 | 1;
    }
  }
  else if (DAT_00491fb8 == 0xb) {
    FUN_0040c540();
    DAT_00474ca0 = DAT_00474ca0 | 2;
    pvVar5 = extraout_ECX_00;
  }
  else if ((DAT_00491fb8 == 4) || (DAT_00491fb8 == 0xf)) {
    FUN_0040c540();
    pvVar5 = extraout_ECX_01;
  }
  else {
    pvVar5 = extraout_ECX;
    if (DAT_00491fb8 == 0xd) {
      FUN_0040c540();
      pvVar5 = extraout_ECX_02;
      if (DAT_00474c80 != DAT_00474c7c) {
        FUN_00418a90();
        DAT_00474ca0 = DAT_00474ca0 | 8;
        pvVar5 = extraout_ECX_03;
      }
      DAT_00474ca0 = DAT_00474ca0 | 1;
    }
  }
  pvVar2 = DAT_00477838;
  if ((DAT_00474ca0 & 2) == 0) {
    if (((DAT_00491fb8 != 0xe) && (DAT_00491fb8 != 0xf)) && (DAT_00477838 != (void *)0x0)) {
      FUN_004294a0((int)DAT_00477838);
      _free(pvVar2);
      pvVar5 = extraout_ECX_04;
    }
    pvVar2 = DAT_004776e8;
    if (DAT_004776e8 != (void *)0x0) {
      DestroyGameState((int)DAT_004776e8);
      _free(pvVar2);
      pvVar5 = extraout_ECX_05;
    }
    pvVar2 = DAT_004776e4;
    if (DAT_004776e4 != (void *)0x0) {
      DestroyGameState((int)DAT_004776e4);
      _free(pvVar2);
      pvVar5 = extraout_ECX_06;
    }
    pvVar2 = DAT_00477830;
    if (DAT_00477830 != (void *)0x0) {
      FUN_00422220((int)DAT_00477830);
      _free(pvVar2);
      pvVar5 = extraout_ECX_07;
    }
    pvVar2 = DAT_0047770c;
    if (DAT_0047770c != (void *)0x0) {
      FUN_004145f0(pvVar5,(int)DAT_0047770c);
      _free(pvVar2);
      pvVar5 = extraout_ECX_08;
    }
    pvVar2 = DAT_00477834;
    if (DAT_00477834 != (void *)0x0) {
      FUN_00424ed0(pvVar5,(int)DAT_00477834);
      _free(pvVar2);
      pvVar5 = extraout_ECX_09;
    }
    pvVar2 = DAT_004776f0;
    if (DAT_004776f0 != (void *)0x0) {
      FUN_00405f70((int)DAT_004776f0);
      _free(pvVar2);
      pvVar5 = extraout_ECX_10;
    }
    pvVar2 = DAT_00477818;
    if (DAT_00477818 != (void *)0x0) {
      FUN_0041adf0((int)DAT_00477818);
      _free(pvVar2);
      pvVar5 = extraout_ECX_11;
    }
    pvVar2 = DAT_0047781c;
    if (DAT_0047781c != (void *)0x0) {
      FUN_0041c1c0((int)DAT_0047781c);
      _free(pvVar2);
      pvVar5 = extraout_ECX_12;
    }
    pvVar2 = DAT_00477814;
    if (DAT_00477814 != (void *)0x0) {
      FUN_00418ee0((int)DAT_00477814);
      _free(pvVar2);
      pvVar5 = extraout_ECX_13;
    }
    pvVar2 = DAT_00477840;
    if (DAT_00477840 != (void *)0x0) {
      FUN_0042b570((int)DAT_00477840);
      _free(pvVar2);
      pvVar5 = extraout_ECX_14;
    }
  }
  else {
    FUN_00414570(pvVar5);
    pvVar5 = DAT_004776e4;
    if (DAT_004776e4 != (void *)0x0) {
      DestroyGameState((int)DAT_004776e4);
      _free(pvVar5);
    }
    pvVar5 = DAT_00477830;
    DAT_004776e4 = DAT_004776e8;
    if (*(int *)((int)DAT_00477830 + 8) != 0) {
      puVar1 = (uint *)(*(int *)((int)DAT_00477830 + 8) + 4);
      *puVar1 = *puVar1 & 0xfffffffd;
    }
    if (*(int *)((int)pvVar5 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)((int)pvVar5 + 0xc) + 4);
      *puVar1 = *puVar1 & 0xfffffffd;
    }
    pvVar5 = DAT_004776f0;
    if (*(int *)((int)DAT_004776f0 + 8) != 0) {
      puVar1 = (uint *)(*(int *)((int)DAT_004776f0 + 8) + 4);
      *puVar1 = *puVar1 & 0xfffffffd;
    }
    if (*(int *)((int)pvVar5 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)((int)pvVar5 + 0xc) + 4);
      *puVar1 = *puVar1 & 0xfffffffd;
    }
    pvVar5 = DAT_00477838;
    if (*(int *)((int)DAT_00477838 + 0x1cc) != 0) {
      puVar1 = (uint *)(*(int *)((int)DAT_00477838 + 0x1cc) + 4);
      *puVar1 = *puVar1 & 0xfffffffd;
    }
    if (*(int *)((int)pvVar5 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)((int)pvVar5 + 0xc) + 4);
      *puVar1 = *puVar1 & 0xfffffffd;
    }
    puVar6 = (undefined4 *)((int)DAT_00477818 + 0x14);
    for (iVar4 = 0x873a8; pvVar5 = (void *)0x0, iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
  }
  pvVar2 = DAT_00477704;
  if ((DAT_00474ca0 & 9) == 0) {
    if (DAT_00477704 != (void *)0x0) {
      FUN_0040d530(pvVar5);
      _free(pvVar2);
      pvVar5 = extraout_ECX_15;
    }
  }
  else {
    FUN_00409f90(DAT_00477704,(int)DAT_00477704);
    pvVar5 = extraout_ECX_16;
  }
  pvVar2 = DAT_004776fc;
  if (DAT_004776fc != (void *)0x0) {
    FUN_0040af00((int)DAT_004776fc);
    _free(pvVar2);
    pvVar5 = extraout_ECX_17;
  }
  pvVar2 = DAT_004776ec;
  if (DAT_004776ec != (void *)0x0) {
    FUN_00405620((int)DAT_004776ec);
    _free(pvVar2);
    pvVar5 = extraout_ECX_18;
  }
  pvVar2 = DAT_004776f4;
  if (DAT_004776f4 != (void *)0x0) {
    FUN_00408af0(pvVar5,(int)DAT_004776f4);
    _free(pvVar2);
    pvVar5 = extraout_ECX_19;
  }
  iVar4 = DAT_00491be4;
  pvVar2 = *(void **)(param_1 + 8);
  if (pvVar2 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    pvVar5 = extraout_ECX_20;
  }
  iVar4 = DAT_00491be4;
  pvVar2 = *(void **)(param_1 + 0xc);
  if (pvVar2 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    pvVar5 = extraout_ECX_21;
  }
  DAT_00477810 = 0;
  if ((DAT_00474ca0 & 0x22) == 0) {
    if (((byte)DAT_00491d78 & 0x10) == 0) {
      uVar7 = 3;
    }
    else {
      uVar7 = 4;
    }
    FUN_0043e460(pvVar5,"dummy",uVar7,0);
  }
  DAT_004918a4 = 1;
  DAT_004923a8 = (-(uint)((DAT_00474ca0 & 1) != 0) & 0x1000000) - 0x1000000;
  return;
}

