/* Raw Ghidra reference; not compilable reconstruction. Address: 0043BC40 */

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

