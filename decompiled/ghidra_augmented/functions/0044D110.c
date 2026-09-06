/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D110 */

/* WARNING: Removing unreachable block (ram,0x0044d158) */
/* WARNING: Removing unreachable block (ram,0x0044d160) */
/* WARNING: Removing unreachable block (ram,0x0044d16e) */
/* WARNING: Removing unreachable block (ram,0x0044d172) */

int FUN_0044d110(int *param_1)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  int in_EAX;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint unaff_ESI;
  uint *puVar7;
  uint uStack_30;
  uint local_4;
  
  if (param_1 == (int *)0x0) {
    return -0x7ffbfe10;
  }
  iVar4 = (**(code **)(*param_1 + 0x24))();
  if (iVar4 < 0) {
    return iVar4;
  }
  uStack_30 = 0;
  iVar4 = (**(code **)(*param_1 + 0x2c))(param_1,0,*(undefined4 *)(in_EAX + 8),&stack0xffffffec);
  if (iVar4 < 0) {
    return iVar4;
  }
  iVar4 = *(int *)(in_EAX + 0xc);
  if (*(int *)(iVar4 + 0x7c) == 0) {
    if (*(HANDLE *)(iVar4 + 0x8c) != (HANDLE)0x0) {
      SetFilePointer(*(HANDLE *)(iVar4 + 0x8c),
                     *(int *)(*(int *)(iVar4 + 0x90) + 0x10) + DAT_004977a4,(PLONG)0x0,0);
      *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(*(int *)(iVar4 + 0x90) + 0x1c);
    }
  }
  else {
    *(undefined4 *)(iVar4 + 0x84) = *(undefined4 *)(iVar4 + 0x80);
    iVar2 = *(int *)(*(int *)(iVar4 + 0x90) + 0x1c);
    if (0 < iVar2) {
      *(int *)(iVar4 + 0x88) = iVar2;
    }
  }
  iVar4 = FUN_0044de10(&uStack_30,unaff_ESI,&local_4,&uStack_30);
  if (iVar4 < 0) {
    return iVar4;
  }
  if (uStack_30 == 0) {
    sVar1 = *(short *)(*(int *)(*(int *)(in_EAX + 0xc) + 0x90) + 0x2e);
    uVar6 = unaff_ESI;
    puVar7 = &local_4;
  }
  else {
    if (unaff_ESI <= uStack_30) goto LAB_0044d2d2;
    uVar6 = uStack_30;
    if (param_1 != (int *)0x0) {
      do {
        iVar4 = FUN_0044dd40();
        if (iVar4 < 0) {
          return iVar4;
        }
        iVar4 = FUN_0044de10(&local_4,unaff_ESI - uVar6,(undefined4 *)(uVar6 + (int)&local_4),
                             &uStack_30);
        if (iVar4 < 0) {
          return iVar4;
        }
        uVar6 = uVar6 + uStack_30;
      } while (uVar6 < unaff_ESI);
      goto LAB_0044d2d2;
    }
    uVar6 = unaff_ESI - uStack_30;
    sVar1 = *(short *)(*(int *)(*(int *)(in_EAX + 0xc) + 0x90) + 0x2e);
    puVar7 = (uint *)(uStack_30 + (int)&local_4);
  }
  bVar3 = (sVar1 != 8) - 1;
  for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar7 = CONCAT22(CONCAT11(bVar3,bVar3),CONCAT11(bVar3,bVar3)) & 0x80808080;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(byte *)puVar7 = bVar3 & 0x80;
    puVar7 = (uint *)((int)puVar7 + 1);
  }
LAB_0044d2d2:
  (**(code **)(*param_1 + 0x4c))(param_1,&local_4,unaff_ESI,0,0);
  return 0;
}

