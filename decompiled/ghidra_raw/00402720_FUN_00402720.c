/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00402720
 * Tracking name: FUN_00402720
 * Ghidra name: FUN_00402720
 * Tracked span: 304 bytes
 */


undefined4 FUN_00402720(void)

{
  undefined4 uVar1;
  int in_EAX;
  undefined4 extraout_ECX;
  undefined4 uVar2;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  uint extraout_EDX;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  ulonglong uVar8;
  
  if (((*(uint *)(in_EAX + 0x2a18) & 8) == 0) &&
     (((*(uint *)(in_EAX + 0x2a18) & 4) == 0 || (*(int *)(in_EAX + 0x2a20) < 0x3c)))) {
    *(undefined4 *)(in_EAX + 0x2b3c) = 0;
    *(undefined4 *)(in_EAX + 0x2b40) = 0;
    *(undefined4 *)(in_EAX + 0x2b44) = 0;
    *(undefined4 *)(in_EAX + 0x2b34) = 0;
    *(undefined4 *)(in_EAX + 0x2b38) = 0;
    D3DXVec3Normalize(in_EAX + 0x2a70,in_EAX + 0x2a58);
    *(undefined4 *)(in_EAX + 0x1ee8) = 0x808080;
    FUN_00403990();
    FUN_00403c80(in_EAX);
    iVar4 = in_EAX + 0x180;
    iVar6 = 8;
    uVar2 = extraout_ECX;
    uVar3 = extraout_EDX;
    do {
      uVar8 = FUN_0043ee30(uVar2,uVar3,iVar4);
      uVar1 = DAT_00476f78;
      uVar3 = (uint)(uVar8 >> 0x20);
      iVar4 = iVar4 + 0x3ac;
      iVar6 = iVar6 + -1;
      uVar2 = extraout_ECX_00;
    } while (iVar6 != 0);
    if (*(int *)(in_EAX + 0x1eec) != 0) {
      DAT_00476f78 = 0x3f800000;
      uVar8 = FUN_0043ee30(uVar1,in_EAX + 0x1f08U,in_EAX + 0x1f08U);
      uVar8 = FUN_0043ee30(extraout_ECX_01,(uint)(uVar8 >> 0x20),in_EAX + 0x22b4);
      FUN_0043ee30(in_EAX + 0x2660,(uint)(uVar8 >> 0x20),in_EAX + 0x2660);
    }
    DAT_00476f78 = uVar1;
    *(undefined4 *)(in_EAX + 0x1eec) = 0;
    puVar5 = (undefined4 *)(in_EAX + 0x2a4c);
    puVar7 = &DAT_00491d7c;
    for (iVar4 = 0x46; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar7 = puVar7 + 1;
    }
    *(int *)(in_EAX + 0x2a34) = *(int *)(in_EAX + 0x2a34) + 1;
  }
  return 1;
}

