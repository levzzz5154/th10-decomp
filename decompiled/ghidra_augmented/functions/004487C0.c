/* Raw Ghidra reference; not compilable reconstruction. Address: 004487C0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004487c0(void)

{
  DAT_00491fac = &DAT_00491e94;
  FUN_00421480();
  (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,DAT_00491fac + 0xcc);
  _DAT_00491fb0 = 1;
  FUN_00448980();
  return;
}

