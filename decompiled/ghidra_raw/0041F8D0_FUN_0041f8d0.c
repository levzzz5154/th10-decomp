/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041F8D0
 * Tracking name: FUN_0041f8d0
 * Ghidra name: FUN_0041f8d0
 * Tracked span: 96 bytes
 */


undefined4 FUN_0041f8d0(void)

{
  int *piVar1;
  char *pcVar2;
  
  piVar1 = FUN_00447280(6,(int)g_pGameStateManager,"front.anm");
  if (piVar1 == (int *)0x0) {
    pcVar2 = &DAT_0046cb68;
  }
  else {
    piVar1 = FUN_00447280(7,(int)g_pGameStateManager,"bullet.anm");
    if (piVar1 != (int *)0x0) {
      return 0;
    }
    pcVar2 = &DAT_0046cd54;
  }
  FUN_0044b810(&DAT_00474f70,pcVar2);
  return 0xffffffff;
}

