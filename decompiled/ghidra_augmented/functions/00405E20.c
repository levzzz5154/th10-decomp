/* Raw Ghidra reference; not compilable reconstruction. Address: 00405E20 */

undefined4 FUN_00405e20(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int unaff_EBX;
  
  piVar2 = FUN_00447280(7,(int)g_pGameStateManager,"bullet.anm");
  *(int **)(unaff_EBX + 0x3e0b50) = piVar2;
  if (piVar2 == (int *)0x0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046cd54);
    return 0xffffffff;
  }
  *(int *)(unaff_EBX + 0x10) = unaff_EBX + 0x60;
  *(undefined2 *)(unaff_EBX + 0x3e07a6) = 5;
  iVar3 = FUN_00449ed0(FUN_00406770);
  iVar1 = DAT_00491be4;
  *(int *)(iVar3 + 0x20) = unaff_EBX;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 8) = iVar3;
  iVar3 = FUN_00449ed0(FUN_004067a0);
  iVar1 = DAT_00491be4;
  *(int *)(iVar3 + 0x20) = unaff_EBX;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
  FUN_00449b70(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar3;
  return 0;
}

