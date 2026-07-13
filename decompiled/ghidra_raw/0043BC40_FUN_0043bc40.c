/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043BC40
 * Tracking name: FUN_0043bc40
 * Ghidra name: FUN_0043bc40
 * Tracked span: 144 bytes
 */


void FUN_0043bc40(void)

{
  int iVar1;
  
  (**(code **)(*(int *)g_pD3DDevice + 0xac))(g_pD3DDevice,0,0,3);
  iVar1 = (**(code **)(*(int *)g_pD3DDevice + 0x44))(g_pD3DDevice,0,0,0,0);
  if (iVar1 < 0) {
    (**(code **)(*(int *)g_pD3DDevice + 0x40))(g_pD3DDevice,&DAT_00491d0c);
  }
  (**(code **)(*(int *)g_pD3DDevice + 0xac))(g_pD3DDevice,0,0,3);
  iVar1 = (**(code **)(*(int *)g_pD3DDevice + 0x44))(g_pD3DDevice,0,0,0,0);
  if (iVar1 < 0) {
    (**(code **)(*(int *)g_pD3DDevice + 0x40))(g_pD3DDevice,&DAT_00491d0c);
  }
  return;
}

