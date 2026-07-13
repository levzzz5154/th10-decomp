/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041F990
 * Tracking name: FUN_0041f990
 * Ghidra name: FUN_0041f990
 * Tracked span: 304 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041f990(void)

{
  uint *puVar1;
  int iVar2;
  void *pvVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  
  iVar2 = DAT_00477820;
  piVar4 = FUN_00447280(1,(int)g_pGameStateManager,"sig.anm");
  *(int **)(iVar2 + 0x3e0) = piVar4;
  if (piVar4 != (int *)0x0) {
    puVar1 = (uint *)(*(int *)(iVar2 + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
    *(undefined4 *)(iVar2 + 0x3e4) = 1;
    puVar5 = FUN_00401440();
    pvVar3 = g_pGameStateManager;
    if (puVar5 == (undefined4 *)0x0) {
      FUN_0044b810(&DAT_00474f70,&DAT_0046dc28);
    }
    else {
      *(undefined4 *)(iVar2 + 1000) = 1;
      DAT_00491fec = FUN_00447280(0,(int)pvVar3,"text.anm");
      if (DAT_00491fec != (int *)0x0) {
        _DAT_00494514 = FUN_0044b360((size_t *)0x0,0);
        if (_DAT_00494514 == (byte *)0x0) {
          FUN_0044b810(&DAT_00474f70,&DAT_0046dbec);
        }
        FUN_0043db60();
        iVar6 = FUN_0044b4d0("thbgm.dat");
        if (iVar6 != 0) {
          if (((byte)DAT_00491d78 & 0x10) == 0) {
            FUN_0043d690("thbgm.dat");
          }
          else {
            _DAT_00497698 = DAT_0046dbe0;
            _DAT_0049769c = DAT_0046dbe4;
            _DAT_004976a0 = DAT_0046dbe8;
          }
        }
        FUN_0041f8d0();
        puVar1 = (uint *)(*(int *)(iVar2 + 8) + 4);
        *puVar1 = *puVar1 | 2;
        FUN_0042af20();
        return 0;
      }
    }
  }
  DAT_00491fb8 = 3;
  puVar1 = (uint *)(*(int *)(iVar2 + 8) + 4);
  *puVar1 = *puVar1 | 2;
  return 0;
}

