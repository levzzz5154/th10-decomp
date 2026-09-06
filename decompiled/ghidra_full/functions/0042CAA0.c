/* Raw Ghidra reference; not compilable reconstruction. Address: 0042CAA0 */

undefined4 FUN_0042caa0(void)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  int unaff_EBX;
  
  iVar3 = FUN_00449ed0(&LAB_0042d2e0);
  iVar1 = DAT_00491be4;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
  *(int *)(iVar3 + 0x20) = unaff_EBX;
  FUN_00449ae0(iVar1);
  *(int *)(unaff_EBX + 0xc) = iVar3;
  iVar3 = FUN_00449ed0(&LAB_0042d2f0);
  iVar1 = DAT_00491be4;
  *(int *)(iVar3 + 0x20) = unaff_EBX;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
  FUN_00449b70(iVar1);
  pvVar2 = g_pGameStateManager;
  *(int *)(unaff_EBX + 0x10) = iVar3;
  piVar4 = FUN_00447280(0x19,(int)pvVar2,"title.anm");
  *(int **)(unaff_EBX + 0x14) = piVar4;
  if (piVar4 != (int *)0x0) {
    piVar4 = FUN_00447280(0x1a,(int)g_pGameStateManager,"title_v.anm");
    *(int **)(unaff_EBX + 0x18) = piVar4;
    if (piVar4 != (int *)0x0) {
      *(undefined4 *)(unaff_EBX + 0xf4) = 1;
      DAT_004918a4 = 0;
      return 0;
    }
  }
  FUN_0044b810(&DAT_00474f70,&DAT_0046cb68);
  return 0xffffffff;
}

