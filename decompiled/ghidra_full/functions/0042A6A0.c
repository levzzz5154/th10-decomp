/* Raw Ghidra reference; not compilable reconstruction. Address: 0042A6A0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042a6a0(void)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_EBX;
  undefined4 *puVar5;
  
  if (*(int *)(unaff_EBX + 0x10) != 0) {
    if (*(int *)(unaff_EBX + 0x10) == 1) {
      iVar4 = unaff_EBX + 0xa0 + DAT_00474c7c * 0x24;
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(unaff_EBX + 0xa0 + DAT_00474c7c * 0x24);
      *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar4 + 8);
      *(undefined4 *)(iVar4 + 0x14) = 0;
      iVar4 = *(int *)(iVar4 + 0x10);
      DAT_004918b0 = *(undefined2 *)(iVar4 + 2);
      DAT_004918b4 = 0;
      DAT_00474c44 = *(undefined4 *)(iVar4 + 0xc);
      DAT_00474c48 = *(undefined2 *)(iVar4 + 0x10);
      FUN_00418b80(&DAT_00474c40,*(int *)(iVar4 + 0x14) * 10);
      DAT_00474c58 = *(int *)(iVar4 + 0x18);
      if ((DAT_00474c64 & 1) == 0) {
        DAT_00474c64 = DAT_00474c64 | 1;
        _DAT_00474c60 = &DAT_00476f78;
      }
      _DAT_00474c5c = (float)DAT_00474c58;
      _DAT_00474c54 = DAT_00474c58 + -1;
      DAT_00474c70 = *(undefined4 *)(iVar4 + 0x1c);
      DAT_00474c98 = *(undefined4 *)(iVar4 + 0x20);
      _DAT_00474c90 = *(undefined4 *)(iVar4 + 0x1b4);
      DAT_00474c9c = *(undefined4 *)(*(int *)(unaff_EBX + 0xb0 + DAT_00474c7c * 0x24) + 0x1b8);
    }
    return;
  }
  puVar2 = operator_new(0x1c4);
  puVar3 = (undefined4 *)0x0;
  if (puVar2 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar4 = 0x71; puVar3 = puVar2, iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  *(undefined4 **)(unaff_EBX + 0x1c + DAT_00474c7c * 4) = puVar3;
  puVar1 = *(undefined2 **)(unaff_EBX + 0x1c + DAT_00474c7c * 4);
  puVar1[1] = DAT_004918b0;
  DAT_004918b4 = 0;
  *puVar1 = (undefined2)DAT_00474c7c;
  *(uint *)(puVar1 + 0xe0) =
       *(uint *)(puVar1 + 0xe0) ^ (*(uint *)(puVar1 + 0xe0) ^ DAT_00491fc4) & 1;
  return;
}

