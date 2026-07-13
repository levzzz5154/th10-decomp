/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042B4D0
 * Tracking name: FUN_0042b4d0
 * Ghidra name: FUN_0042b4d0
 * Tracked span: 160 bytes
 */


undefined4 FUN_0042b4d0(void)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  undefined4 extraout_ECX;
  
  *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)((int)g_pGameThread + 0x8994);
  iVar2 = FUN_00449ed0(&LAB_0042b9a0);
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = in_EAX;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  FUN_00449ae0(iVar1);
  *(int *)(in_EAX + 8) = iVar2;
  iVar2 = FUN_00449ed0(&LAB_0042b9b0);
  iVar1 = DAT_00491be4;
  *(int *)(iVar2 + 0x20) = in_EAX;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xfffffffd;
  FUN_00449b70(iVar1);
  *(int *)(in_EAX + 0xc) = iVar2;
  iVar1 = *(int *)(in_EAX + 0x10);
  FUN_00401de0(extraout_ECX,(undefined4 *)(in_EAX + 0x18));
  *(int *)(in_EAX + 800) = iVar1;
  FUN_0043e5a0(iVar1,0xc4);
  return 0;
}

