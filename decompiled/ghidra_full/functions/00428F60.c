/* Raw Ghidra reference; not compilable reconstruction. Address: 00428F60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00428f60(char *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int in_EAX;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 extraout_ECX;
  int iVar6;
  int unaff_EBX;
  undefined4 *puVar7;
  
  *(int *)(unaff_EBX + 0x10) = in_EAX;
  if (in_EAX == 0) {
    DAT_00477838 = unaff_EBX;
    FUN_0042ab20(unaff_EBX);
    uVar4 = FUN_0042aa50(unaff_EBX);
    *(undefined4 *)(unaff_EBX + 0x9c) = uVar4;
    puVar5 = operator_new(0x24);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      *puVar5 = 0;
      puVar5[1] = 0;
      puVar5[2] = 0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0;
      puVar5[8] = 0;
      *puVar5 = 0x72303174;
      *(undefined2 *)(puVar5 + 1) = 5;
      puVar5[4] = 0x100;
    }
    *(undefined4 **)(unaff_EBX + 0x14) = puVar5;
    puVar5 = operator_new(100);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      FUN_00418c40(extraout_ECX,puVar5 + 5);
      puVar7 = puVar5;
      for (iVar6 = 0x19; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
    }
    *(undefined4 **)(unaff_EBX + 0x18) = puVar5;
    puVar5 = operator_new(0x1c4);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      puVar7 = puVar5;
      for (iVar6 = 0x71; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
    }
    *(undefined4 **)(unaff_EBX + 0x1c + DAT_00474c7c * 4) = puVar5;
    puVar1 = *(undefined2 **)(unaff_EBX + 0x1c + DAT_00474c7c * 4);
    *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x50) = DAT_00474c68;
    *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x54) = DAT_00474c6c;
    *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x58) = DAT_00474c74;
    if (DAT_00477810 != 0) {
      puVar5 = (undefined4 *)(DAT_00477810 + 0x24);
      puVar7 = (undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x14);
      for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
    }
    *puVar1 = (undefined2)DAT_00474c7c;
    puVar1[1] = DAT_004918b0;
    DAT_004918b4 = 0;
    *(uint *)(puVar1 + 0xe0) =
         *(uint *)(puVar1 + 0xe0) ^ (*(uint *)(puVar1 + 0xe0) ^ DAT_00491fc4) & 1;
    if (DAT_00491fc4 != 0) {
      *(undefined4 *)(puVar1 + 0x12) = 0;
      *(undefined4 *)(puVar1 + 0x14) = 0;
    }
    *(undefined4 *)(puVar1 + 6) = DAT_00474c44;
    puVar1[8] = DAT_00474c48;
    *(undefined4 *)(puVar1 + 10) = DAT_00474c4c;
    *(undefined4 *)(puVar1 + 0xc) = DAT_00474c58;
    *(undefined4 *)(puVar1 + 0xe) = DAT_00474c70;
    *(undefined4 *)(puVar1 + 0x10) = DAT_00474c98;
    *(undefined4 *)(puVar1 + 0xda) = _DAT_00474c90;
    *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x60) = _DAT_00474c90;
    puVar5 = operator_new(0x24);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      puVar5[2] = 0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      *puVar5 = 0;
      puVar5[1] = puVar5[1] & 0xfffffffe;
      puVar5[5] = puVar5;
      puVar5[6] = 0;
      puVar5[7] = 0;
    }
    iVar6 = DAT_00491be4;
    puVar5[2] = &LAB_0042a3d0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[8] = unaff_EBX;
    puVar5[1] = puVar5[1] & 0xfffffffd | 1;
    FUN_00449ae0(iVar6);
    *(undefined4 **)(unaff_EBX + 8) = puVar5;
    puVar5 = operator_new(0x24);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      puVar5[2] = 0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      *puVar5 = 0;
      puVar5[1] = puVar5[1] & 0xfffffffe;
      puVar5[5] = puVar5;
      puVar5[6] = 0;
      puVar5[7] = 0;
    }
    iVar6 = DAT_00491be4;
    puVar5[2] = &LAB_0042a3e0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[8] = unaff_EBX;
    puVar5[1] = puVar5[1] & 0xfffffffd | 1;
    FUN_00449ae0(iVar6);
    *(undefined4 **)(unaff_EBX + 0x1cc) = puVar5;
    puVar5 = operator_new(0x24);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      puVar5[2] = 0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      *puVar5 = 0;
      puVar5[1] = puVar5[1] & 0xfffffffe;
      puVar5[5] = puVar5;
      puVar5[6] = 0;
      puVar5[7] = 0;
    }
    iVar6 = DAT_00491be4;
    puVar5[2] = &LAB_0042a430;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[8] = unaff_EBX;
    puVar5[1] = puVar5[1] & 0xfffffffd | 1;
    FUN_00449b70(iVar6);
    *(undefined4 **)(unaff_EBX + 0xc) = puVar5;
    *(int *)(unaff_EBX + 0x1d0) = DAT_00474c7c;
    return 0;
  }
  if (in_EAX == 1) {
    DAT_00477838 = unaff_EBX;
    iVar6 = FUN_0042a200(param_1);
    if (iVar6 == 0) {
      puVar5 = (undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x14);
      puVar7 = (undefined4 *)(DAT_00477810 + 0x24);
      for (iVar6 = 0xd; iVar3 = DAT_00474c7c, iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
      iVar2 = *(int *)(unaff_EBX + 0xb0 + DAT_00474c7c * 0x24);
      *(undefined4 *)(unaff_EBX + 0xa4 + DAT_00474c7c * 0x24) =
           *(undefined4 *)(unaff_EBX + 0xa0 + DAT_00474c7c * 0x24);
      *(undefined4 *)(unaff_EBX + 0xb4 + iVar3 * 0x24) = 0;
      iVar6 = unaff_EBX + 0xa0 + iVar3 * 0x24;
      *(undefined4 *)(iVar6 + 0xc) = *(undefined4 *)(iVar6 + 8);
      DAT_00474c68 = *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x50);
      DAT_00474c6c = *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x54);
      DAT_00474c74 = *(undefined4 *)(*(int *)(unaff_EBX + 0x18) + 0x58);
      DAT_004918b0 = *(undefined2 *)(iVar2 + 2);
      DAT_004918b4 = 0;
      DAT_00474c44 = *(undefined4 *)(iVar2 + 0xc);
      DAT_00474c48 = *(undefined2 *)(iVar2 + 0x10);
      FUN_00418b80(&DAT_00474c40,*(int *)(iVar2 + 0x14) * 10);
      FUN_0042a930(*(int *)(iVar2 + 0x18));
      DAT_00474c70 = *(undefined4 *)(iVar2 + 0x1c);
      DAT_00474c98 = *(undefined4 *)(iVar2 + 0x20);
      _DAT_00474c90 = *(undefined4 *)(iVar2 + 0x1b4);
      DAT_00474c9c = *(undefined4 *)(*(int *)(unaff_EBX + 0xb0 + DAT_00474c7c * 0x24) + 0x1b8);
      puVar5 = operator_new(0x24);
      if (puVar5 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        puVar5[2] = 0;
        puVar5[3] = 0;
        puVar5[4] = 0;
        *puVar5 = 0;
        puVar5[1] = puVar5[1] & 0xfffffffe;
        puVar5[5] = puVar5;
        puVar5[6] = 0;
        puVar5[7] = 0;
      }
      iVar6 = DAT_00491be4;
      puVar5[2] = &LAB_0042a3d0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[8] = unaff_EBX;
      puVar5[1] = puVar5[1] & 0xfffffffd | 1;
      FUN_00449ae0(iVar6);
      *(undefined4 **)(unaff_EBX + 8) = puVar5;
      puVar5 = operator_new(0x24);
      if (puVar5 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        puVar5[2] = 0;
        puVar5[3] = 0;
        puVar5[4] = 0;
        *puVar5 = 0;
        puVar5[1] = puVar5[1] & 0xfffffffe;
        puVar5[5] = puVar5;
        puVar5[6] = 0;
        puVar5[7] = 0;
      }
      iVar6 = DAT_00491be4;
      puVar5[2] = &LAB_0042a3e0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[8] = unaff_EBX;
      puVar5[1] = puVar5[1] & 0xfffffffd | 1;
      FUN_00449ae0(iVar6);
      *(undefined4 **)(unaff_EBX + 0x1cc) = puVar5;
      puVar5 = operator_new(0x24);
      if (puVar5 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        puVar5[2] = 0;
        puVar5[3] = 0;
        puVar5[4] = 0;
        *puVar5 = 0;
        puVar5[1] = puVar5[1] & 0xfffffffe;
        puVar5[5] = puVar5;
        puVar5[6] = 0;
        puVar5[7] = 0;
      }
      iVar6 = DAT_00491be4;
      puVar5[2] = &LAB_0042a430;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[8] = unaff_EBX;
      puVar5[1] = puVar5[1] & 0xfffffffd | 1;
      FUN_00449b70(iVar6);
      *(undefined4 **)(unaff_EBX + 0xc) = puVar5;
      *(undefined4 *)(unaff_EBX + 0x1d0) = 0xffffffff;
      return 0;
    }
  }
  else {
    if (in_EAX != 2) {
      return 0;
    }
    iVar6 = FUN_0042a200(param_1);
    if (iVar6 == 0) {
      return 0;
    }
  }
  return 0xffffffff;
}

