/* Raw Ghidra reference; not compilable reconstruction. Address: 00448620 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448620(void)

{
  DAT_00491fac = &DAT_00491d7c;
  FUN_00421480();
  (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0x33);
  _DAT_00491fb0 = 0;
  if (DAT_00492378 != 0) {
    FUN_00442f50();
    DAT_00492378 = 0;
    (**(code **)(*(int *)g_pD3DDevice + 0xe4))(g_pD3DDevice,0x1c,0);
  }
  FUN_00448980();
  return;
}

