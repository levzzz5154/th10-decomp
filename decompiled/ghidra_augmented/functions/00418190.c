/* Raw Ghidra reference; not compilable reconstruction. Address: 00418190 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00418190(void *this,int param_1)

{
  uint *puVar1;
  uint uVar2;
  void *pvVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar4;
  undefined4 extraout_ECX_01;
  int extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  void *this_00;
  undefined4 extraout_ECX_05;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 local_40 [16];
  
  if (*(int *)(param_1 + 0x14) == 0) {
    if ((*(byte *)(param_1 + 0x58) & 8) != 0) {
      FUN_0044c150();
      DAT_00491fb8 = ~(DAT_00491ff4 >> 0xc) & 1 | 2;
      return 1;
    }
    FUN_00404450(DAT_004776e8);
    if (DAT_004776e4 == (void *)0x0) {
      *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) & 0xfffff7ff;
      FUN_00405ed0(extraout_ECX);
      FUN_00424d90();
      iVar4 = DAT_00477704;
      puVar6 = (undefined4 *)(DAT_00477818 + 0x14);
      for (iVar5 = 0x873a8; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      FUN_00409f90((void *)0x0,iVar4);
      CleanupLinkedResources();
      DAT_00474c88 = 0;
      DAT_00474c8c = 0;
      FUN_0042a450();
      puVar6 = local_40;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      FUN_0040cfb0(DAT_00477704,&DAT_0046d278);
      FUN_00413bc0(extraout_ECX_01);
      iVar4 = DAT_00477830;
      if (*(int *)(DAT_00477830 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477830 + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar5 = DAT_00477834;
      puVar1 = (uint *)(*(int *)(DAT_00477834 + 8) + 4);
      *puVar1 = *puVar1 | 2;
      iVar4 = *(int *)(iVar5 + 0xc);
      *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 2;
      FUN_00426f70(iVar5);
      iVar4 = DAT_004776f0;
      if (*(int *)(DAT_004776f0 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_004776f0 + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar4 = DAT_00477704;
      if (*(int *)(DAT_00477704 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477704 + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar4 = DAT_00477818;
      if (*(int *)(DAT_00477818 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477818 + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar4 = DAT_0047781c;
      if (*(int *)(DAT_0047781c + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_0047781c + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar4 = DAT_004776fc;
      puVar1 = (uint *)(*(int *)(DAT_004776fc + 8) + 4);
      *puVar1 = *puVar1 | 2;
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
      iVar4 = DAT_004776ec;
      if (*(int *)(DAT_004776ec + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_004776ec + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar4 = DAT_00477840;
      puVar1 = (uint *)(*(int *)(DAT_00477840 + 8) + 4);
      *puVar1 = *puVar1 | 2;
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
      iVar4 = DAT_004776f4;
      if (*(int *)(DAT_004776f4 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_004776f4 + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar5 = *(int *)(iVar4 + 0xc);
      if (iVar5 != 0) {
        puVar1 = (uint *)(iVar5 + 4);
        *puVar1 = *puVar1 | 2;
      }
      puVar1 = (uint *)(*(int *)(iVar4 + 0x37ac) + 4);
      *puVar1 = *puVar1 | 2;
      iVar4 = DAT_00477814;
      if (*(int *)(DAT_00477814 + 8) != 0) {
        puVar1 = (uint *)(*(int *)(DAT_00477814 + 8) + 4);
        *puVar1 = *puVar1 | 2;
      }
      iVar4 = *(int *)(iVar4 + 0xc);
      if (iVar4 != 0) {
        *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 2;
      }
      if ((DAT_00474ca0 & 0x20) == 0) {
        FUN_00420b10(DAT_00477848,0,*(int *)((int)DAT_00477848 + 0x24));
        iVar4 = extraout_ECX_02;
      }
      pvVar3 = g_pGameThread;
      FUN_00409e50(iVar4);
      FUN_00409e50(extraout_ECX_03);
      *(undefined4 *)((int)pvVar3 + 0x89a4) = 0;
    }
    else {
      FUN_00404530();
      FUN_004045b0();
      *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) | 0x800;
      FUN_00409e50(extraout_ECX_00);
    }
  }
  else if ((*(int *)(param_1 + 0x14) == 0x1e) && ((*(uint *)(param_1 + 0x58) & 0x800) != 0)) {
    *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) & 0xfffff7ff;
    FUN_00405ed0(this);
    FUN_00424d90();
    puVar6 = (undefined4 *)(DAT_00477818 + 0x14);
    for (iVar4 = 0x873a8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    FUN_00409f90((void *)0x0,DAT_00477704);
    CleanupLinkedResources();
    DAT_00474c88 = 0;
    DAT_00474c8c = 0;
    FUN_0042a450();
    puVar6 = local_40;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    FUN_0040cfb0(DAT_00477704,&DAT_0046d278);
    FUN_00413bc0(extraout_ECX_04);
    iVar4 = DAT_00477830;
    if (*(int *)(DAT_00477830 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_00477830 + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    if (*(int *)(iVar4 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar5 = DAT_00477834;
    puVar1 = (uint *)(*(int *)(DAT_00477834 + 8) + 4);
    *puVar1 = *puVar1 | 2;
    iVar4 = *(int *)(iVar5 + 0xc);
    *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 2;
    FUN_00426f70(iVar5);
    iVar4 = DAT_004776f0;
    if (*(int *)(DAT_004776f0 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_004776f0 + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    if (*(int *)(iVar4 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar4 = DAT_00477704;
    if (*(int *)(DAT_00477704 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_00477704 + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    if (*(int *)(iVar4 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar4 = DAT_00477818;
    if (*(int *)(DAT_00477818 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_00477818 + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    if (*(int *)(iVar4 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar4 = DAT_0047781c;
    if (*(int *)(DAT_0047781c + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_0047781c + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    if (*(int *)(iVar4 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar4 = DAT_004776fc;
    puVar1 = (uint *)(*(int *)(DAT_004776fc + 8) + 4);
    *puVar1 = *puVar1 | 2;
    puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
    iVar4 = DAT_004776ec;
    if (*(int *)(DAT_004776ec + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_004776ec + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    if (*(int *)(iVar4 + 0xc) != 0) {
      puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar4 = DAT_00477840;
    puVar1 = (uint *)(*(int *)(DAT_00477840 + 8) + 4);
    *puVar1 = *puVar1 | 2;
    puVar1 = (uint *)(*(int *)(iVar4 + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
    iVar4 = DAT_004776f4;
    if (*(int *)(DAT_004776f4 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_004776f4 + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar5 = *(int *)(iVar4 + 0xc);
    if (iVar5 != 0) {
      puVar1 = (uint *)(iVar5 + 4);
      *puVar1 = *puVar1 | 2;
    }
    puVar1 = (uint *)(*(int *)(iVar4 + 0x37ac) + 4);
    *puVar1 = *puVar1 | 2;
    iVar4 = DAT_00477814;
    if (*(int *)(DAT_00477814 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(DAT_00477814 + 8) + 4);
      *puVar1 = *puVar1 | 2;
    }
    iVar4 = *(int *)(iVar4 + 0xc);
    if (iVar4 != 0) {
      *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 2;
    }
    if (((byte)DAT_00491d78 & 0x10) == 0) {
      uVar7 = 3;
    }
    else {
      uVar7 = 4;
    }
    FUN_0043e460(iVar4,"dummy",uVar7,0);
    FUN_00420b10(this_00,0,*(int *)((int)DAT_00477848 + 0x24));
    puVar6 = (undefined4 *)((int)g_pGameThread + 0x89a4);
    FUN_00409e50(extraout_ECX_05);
    *puVar6 = 0;
    FUN_00405410(0);
  }
  pvVar3 = DAT_004776e4;
  if (((DAT_004776e4 != (void *)0x0) && ((*(byte *)((int)DAT_004776e4 + 0x2a18) & 8) != 0)) &&
     (DAT_004776e4 != (void *)0x0)) {
    DestroyGameState((int)DAT_004776e4);
    _free(pvVar3);
  }
  if ((*(uint *)(param_1 + 0x58) & 4) == 0) {
    FUN_0044c150();
    if ((DAT_00474ca0 & 0x20) != 0) {
      if (((_DAT_00474e30 & 0x160b) != 0) || ((*(byte *)(param_1 + 0x58) & 0x70) != 0)) {
        DAT_00491fb8 = (-(uint)((DAT_00491ff4 & 0x1000) != 0) & 0xfffffffe) + 4;
      }
      if (*(int *)(param_1 + 0x14) == 0xb7c) {
        FUN_0043c8b0(5,0x3c,0,0,0);
      }
      else if (*(int *)(param_1 + 0x14) == 3000) {
        FUN_0040ac90(4);
      }
    }
    FUN_00417040();
    uVar2 = *(uint *)(param_1 + 0x58);
    if ((((uVar2 & 0x10) == 0) && ((uVar2 & 0x20) == 0)) && ((uVar2 & 0x40) == 0)) {
      if (*(int *)(DAT_00477838 + 0x10) != 1) {
        iVar5 = (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c;
        iVar4 = *(int *)(iVar5 + 0x4cc + DAT_0047783c);
        if (iVar4 < 215999999) {
          *(int *)(iVar5 + 0x4cc + DAT_0047783c) = iVar4 + 1;
        }
      }
      if (((*(int *)(DAT_00477704 + 0x10) == 0) && (*(int *)(DAT_0047770c + 0x9eb8) == 0)) &&
         (0x59 < *(int *)(param_1 + 0x14))) {
        FUN_00418a00();
      }
      DAT_00474c88 = DAT_00474c88 + 1;
      DAT_00474c8c = DAT_00474c8c + 1;
      FUN_00404ed0();
      return 1;
    }
    return 3;
  }
  *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) | 0x80;
  return 1;
}

