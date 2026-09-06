/* Raw Ghidra reference; not compilable reconstruction. Address: 0041F8D0 */

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

