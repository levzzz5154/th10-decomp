/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00442F50
 * Tracking name: FUN_00442f50
 * Ghidra name: FUN_00442f50
 * Tracked span: 144 bytes
 */


void FUN_00442f50(void)

{
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 0x3adac8) != 0) {
    (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,6,0);
    (**(code **)(*(int *)g_pD3DDevice + 0x10c))(g_pD3DDevice,0,3,0);
    (**(code **)(*(int *)g_pD3DDevice + 0x164))(g_pD3DDevice,0x144);
    (**(code **)(*(int *)g_pD3DDevice + 0x14c))
              (g_pD3DDevice,4,*(int *)(unaff_ESI + 0x3adac8) << 1,
               *(undefined4 *)(unaff_ESI + 0x72dad0),0x1c);
    *(undefined4 *)(unaff_ESI + 0x72dad0) = *(undefined4 *)(unaff_ESI + 0x72dacc);
    *(undefined4 *)(unaff_ESI + 0x3adac8) = 0;
    *(int *)(unaff_ESI + 0x58) = *(int *)(unaff_ESI + 0x58) + 1;
  }
  return;
}

