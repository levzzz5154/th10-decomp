/* Raw Ghidra reference; not compilable reconstruction. Address: 0043BCD0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043bcd0(void)

{
  if (g_pGameStateManager != (void *)0x0) {
    FUN_00442f50();
  }
  _DAT_00491cf4 = 0;
  _DAT_00491cf8 = 0;
  _DAT_00491cfc = 0x280;
  _DAT_00491d00 = 0x1e0;
  _DAT_00491d04 = 0;
  _DAT_00491d08 = 0x3f800000;
  (**(code **)(*(int *)g_pD3DDevice + 0xbc))(g_pD3DDevice,&DAT_00491cf4);
  FUN_0043bc40();
  return;
}

