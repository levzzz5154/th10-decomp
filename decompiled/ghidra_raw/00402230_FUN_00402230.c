/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00402230
 * Tracking name: FUN_00402230
 * Ghidra name: FUN_00402230
 * Tracked span: 528 bytes
 */


undefined4 __thiscall FUN_00402230(void *this,int param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = in_EAX;
  if (param_1 == 0) {
    iVar1 = DAT_004776e4;
    DAT_004776e8 = in_EAX;
  }
  DAT_004776e4 = iVar1;
  *(undefined4 *)(in_EAX + 0x2a30) = DAT_00474c7c;
  iVar1 = FUN_00403850(this);
  if (iVar1 == 0) {
    puVar3 = &DAT_00491d7c;
    puVar4 = (undefined4 *)(in_EAX + 0x2a4c);
    for (iVar1 = 0x46; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 *)(in_EAX + 0x2a4c) = 0;
    *(undefined4 *)(in_EAX + 0x2a50) = 0;
    *(undefined4 *)(in_EAX + 0x2a54) = 0xc4160000;
    *(undefined4 *)(in_EAX + 0x2a58) = 0;
    *(undefined4 *)(in_EAX + 0x2a5c) = 0x43960000;
    *(undefined4 *)(in_EAX + 0x2a60) = 0x44160000;
    *(undefined4 *)(in_EAX + 0x2a64) = 0;
    *(undefined4 *)(in_EAX + 0x2a68) = 0x3f800000;
    *(undefined4 *)(in_EAX + 0x2a6c) = 0;
    *(undefined4 *)(in_EAX + 0x2a88) = 0;
    *(undefined4 *)(in_EAX + 0x2a8c) = 0;
    *(undefined4 *)(in_EAX + 0x2a90) = 0;
    *(undefined4 *)(in_EAX + 0x1ee0) = 0x4b12a310;
    iVar2 = FUN_00449ed0(&LAB_00403050);
    iVar1 = DAT_00491be4;
    *(int *)(iVar2 + 0x20) = in_EAX;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
    FUN_00449ae0(iVar1);
    *(int *)(in_EAX + 8) = iVar2;
    iVar2 = FUN_00449ed0(&LAB_00403060);
    iVar1 = DAT_00491be4;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
    *(int *)(iVar2 + 0x20) = in_EAX;
    FUN_00449b70(iVar1);
    *(int *)(in_EAX + 0xc) = iVar2;
    iVar2 = FUN_00449ed0(&LAB_00403070);
    iVar1 = DAT_00491be4;
    *(int *)(iVar2 + 0x20) = in_EAX;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
    FUN_00449b70(iVar1);
    *(int *)(in_EAX + 0x2a40) = iVar2;
    *(undefined4 *)(in_EAX + 0x2a34) = 0;
    if ((*(uint *)(in_EAX + 0x48) & 1) == 0) {
      *(undefined4 *)(in_EAX + 0x3c) = 0;
      *(undefined4 *)(in_EAX + 0x38) = 0xfff0bdc1;
      *(undefined4 *)(in_EAX + 0x40) = 0;
      *(undefined4 **)(in_EAX + 0x44) = &DAT_00476f78;
      *(uint *)(in_EAX + 0x48) = *(uint *)(in_EAX + 0x48) | 1;
    }
    *(undefined4 *)(in_EAX + 0x3c) = 0;
    *(undefined4 *)(in_EAX + 0x40) = 0;
    *(undefined4 *)(in_EAX + 0x38) = 0xffffffff;
    *(uint *)(in_EAX + 0x2a18) = *(uint *)(in_EAX + 0x2a18) | 1;
    *(undefined4 *)(in_EAX + 0x94) = 0;
    *(undefined4 *)(in_EAX + 0xe0) = 0;
    return 0;
  }
  FUN_0044b8e0(&DAT_0046cc70);
  return 0xffffffff;
}

