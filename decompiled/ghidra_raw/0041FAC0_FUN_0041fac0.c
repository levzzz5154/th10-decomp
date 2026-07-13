/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041FAC0
 * Tracking name: FUN_0041fac0
 * Ghidra name: FUN_0041fac0
 * Tracked span: 144 bytes
 */


undefined4 FUN_0041fac0(void)

{
  int iVar1;
  int iVar2;
  uintptr_t uVar3;
  void *unaff_EBX;
  
  iVar2 = FUN_00449ed0(&LAB_0041feb0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  iVar1 = DAT_00491be4;
  *(void **)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)((int)unaff_EBX + 8) = iVar2;
  iVar2 = FUN_00449ed0(&LAB_0041fef0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  iVar1 = DAT_00491be4;
  *(void **)(iVar2 + 0x20) = unaff_EBX;
  FUN_00449b70(iVar1);
  *(int *)((int)unaff_EBX + 0xc) = iVar2;
  FUN_0044c150();
  *(code **)((int)unaff_EBX + 0x28) = FUN_0041f990;
  *(undefined4 *)((int)unaff_EBX + 0x20) = 1;
  *(undefined4 *)((int)unaff_EBX + 0x1c) = 0;
  uVar3 = __beginthreadex((void *)0x0,0,FUN_0041f990,unaff_EBX,0,(uint *)((int)unaff_EBX + 0x18));
  *(uintptr_t *)((int)unaff_EBX + 0x14) = uVar3;
  return 0;
}

