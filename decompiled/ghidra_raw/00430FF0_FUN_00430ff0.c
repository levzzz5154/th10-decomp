/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00430FF0
 * Tracking name: FUN_00430ff0
 * Ghidra name: FUN_00430ff0
 * Tracked span: 1056 bytes
 */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00430ff0(void *this,int param_1)

{
  uint *puVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  uint uVar11;
  int iVar12;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 6;
    iVar12 = *(int *)(param_1 + 0x2c);
    uVar11 = DAT_00491c08;
    if (iVar12 != 0) {
      if ((int)DAT_00491c08 < iVar12) {
        uVar11 = ((int)DAT_00491c08 < 0) - 1 & DAT_00491c08;
      }
      else {
        uVar11 = iVar12 - 1;
      }
    }
    *(uint *)(param_1 + 0x24) = uVar11;
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c620(1);
  case 1:
    if (10 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
    }
    break;
  case 2:
    puVar1 = (uint *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    if (*(uint *)(param_1 + 0x28) != *puVar1) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 10) != 0) {
      FUN_0042c620(4);
      FUN_0043dc90(&DAT_00492590,0);
      DAT_00491c08 = *puVar1;
      return 1;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      if (*(char *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c + 0x4e9 +
                   (*puVar1 + DAT_00474c74 * 6) * 8) != '\0') {
        FUN_0042c620(3);
      }
      FUN_0043dc90(&DAT_00492590,0);
      DAT_00491c08 = *puVar1;
      DAT_00474cac = 0;
      iVar12 = FUN_0044b010(extraout_ECX,&DAT_00497aa8);
      bVar2 = DAT_00497aab;
      bVar3 = DAT_00497aac;
      bVar4 = DAT_00497aad;
      bVar5 = DAT_00497aae;
      bVar6 = DAT_00497aaf;
      bVar7 = DAT_00497ab0;
      bVar8 = DAT_00497ab1;
      bVar9 = DAT_00497ab2;
      bVar10 = DAT_00497aaa;
      if (iVar12 == 0) {
        bVar2 = DAT_00497ada;
        bVar3 = DAT_00497adb;
        bVar4 = DAT_00497adc;
        bVar5 = DAT_00497add;
        bVar6 = DAT_00497ade;
        bVar7 = DAT_00497adf;
        bVar8 = DAT_00497ae0;
        bVar9 = DAT_00497ae1;
        bVar10 = DAT_00497ad9;
      }
      if ((bVar10 & 0x80) != 0) {
        DAT_00474cac = 1;
        return 1;
      }
      if ((bVar2 & 0x80) != 0) {
        DAT_00474cac = 2;
        return 1;
      }
      if ((bVar3 & 0x80) != 0) {
        DAT_00474cac = 3;
        return 1;
      }
      if ((bVar4 & 0x80) != 0) {
        DAT_00474cac = 4;
        return 1;
      }
      if ((bVar5 & 0x80) != 0) {
        DAT_00474cac = 5;
        return 1;
      }
      if ((bVar6 & 0x80) != 0) {
        DAT_00474cac = 6;
        return 1;
      }
      if ((bVar7 & 0x80) != 0) {
        DAT_00474cac = 7;
        return 1;
      }
      if ((bVar8 & 0x80) != 0) {
        DAT_00474cac = 8;
        return 1;
      }
      if ((bVar9 & 0x80) != 0) {
        DAT_00474cac = 9;
        return 1;
      }
    }
    break;
  case 3:
    if (*(int *)(param_1 + 0x2b4) == 10) {
      FUN_0040c540();
      FUN_0043c8b0(5,0x20,0,0,0);
    }
    if (0x27 < *(int *)(param_1 + 0x2b4)) {
      FUN_0044be20();
      FUN_0042c5c0(3);
      DAT_00474c7c = *(int *)(param_1 + 0x24) + 1;
      DAT_00477848 = &DAT_00474788 + DAT_00474c7c * 0x30;
      DAT_00474c80 = DAT_00474c7c;
      FUN_00420c30();
      DAT_00491fb8 = 7;
      return 1;
    }
    break;
  case 4:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c6d0(extraout_ECX_00);
      FUN_0042c5c0(8);
      FUN_0044be70();
    }
  }
  return 1;
}

