/* Raw Ghidra reference; not compilable reconstruction. Address: 00413980 */

undefined4 FUN_00413980(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  
  piVar1 = FUN_00447280(6,(int)g_pGameStateManager,"front.anm");
  *(int **)(unaff_EBX + 0x9ec8) = piVar1;
  if (piVar1 == (int *)0x0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046cb68);
  }
  else {
    iVar2 = FUN_00413a20(unaff_EBX);
    if (iVar2 == 0) {
      iVar3 = FUN_00449ed0(FUN_00415ae0);
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
      iVar2 = DAT_00491be4;
      *(int *)(iVar3 + 0x20) = unaff_EBX;
      FUN_00449ae0(iVar2);
      *(int *)(unaff_EBX + 8) = iVar3;
      iVar3 = FUN_00449ed0(FUN_00415af0);
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
      iVar2 = DAT_00491be4;
      *(int *)(iVar3 + 0x20) = unaff_EBX;
      FUN_00449b70(iVar2);
      *(int *)(unaff_EBX + 0xc) = iVar3;
      return 0;
    }
  }
  return 0xffffffff;
}

