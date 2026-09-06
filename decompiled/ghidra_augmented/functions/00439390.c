/* Raw Ghidra reference; not compilable reconstruction. Address: 00439390 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00439390(int param_1)

{
  void *pvVar1;
  char cVar2;
  int iVar3;
  float10 fVar4;
  
  fVar4 = FUN_00439540();
  *(double *)(param_1 + 0x38) = (double)fVar4;
  if (fVar4 < (float10)*(double *)(param_1 + 0x40)) {
    *(double *)(param_1 + 0x48) = (double)fVar4;
  }
  *(double *)(param_1 + 0x40) = (double)fVar4;
  if (fVar4 <= (float10)*(double *)(param_1 + 0x48)) {
    Sleep(0);
    return 0;
  }
  if ((float10)*(double *)(param_1 + 0x48) < fVar4) {
    do {
      *(double *)(param_1 + 0x48) = *(double *)(param_1 + 0x48) + _DAT_00470c90;
    } while (*(double *)(param_1 + 0x48) < *(double *)(param_1 + 0x38));
  }
  FUN_00442f50();
  DAT_00491fac = &DAT_00491e94;
  FUN_00421480();
  (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0xcc);
  _DAT_00491fb0 = 1;
  iVar3 = FUN_00449c00(DAT_00491be4);
  FUN_0043ddf0(&DAT_00492590);
  if (iVar3 != 0) {
    if (iVar3 != -1) {
      cVar2 = *(char *)(param_1 + 0x14) + '\x01';
      *(char *)(param_1 + 0x14) = cVar2;
      if ((int)(DAT_00491d66 + 1) <= (int)cVar2) {
        (**(code **)(*(int *)g_pD3DDevice + 0xa4))(g_pD3DDevice);
        pvVar1 = g_pGameStateManager;
        iVar3 = (int)g_pGameStateManager + 0x3adacc;
        *(undefined4 *)((int)g_pGameStateManager + 0x3adac8) = 0;
        *(int *)((int)pvVar1 + 0x72dacc) = iVar3;
        *(int *)((int)pvVar1 + 0x72dad0) = iVar3;
        DAT_00492378 = 0xff;
        FUN_00420cd0();
        FUN_00449d40(DAT_00491be4);
        FUN_00442f50();
        (**(code **)(*(int *)g_pD3DDevice + 0x104))(g_pD3DDevice,0,0);
        (**(code **)(*(int *)g_pD3DDevice + 0xa8))(g_pD3DDevice);
        *(undefined1 *)(param_1 + 0x14) = 0;
        FUN_004391f0();
      }
      fVar4 = FUN_00439540();
      _DAT_004923a0 = (double)(fVar4 - (float10)*(double *)(param_1 + 0x38));
      return 0;
    }
    FUN_0044c150();
    return 2;
  }
  FUN_0044c150();
  return 1;
}

