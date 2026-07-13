/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004391F0
 * Tracking name: FUN_004391f0
 * Ghidra name: FUN_004391f0
 * Tracked span: 240 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004391f0(void)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_ECX;
  void *pvStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined1 auStack_104 [256];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)auStack_104;
  uStack_108 = 0;
  uStack_10c = 0;
  uStack_110 = 0;
  uStack_114 = 0;
  pvStack_118 = g_pD3DDevice;
  iVar1 = (**(code **)(*(int *)g_pD3DDevice + 0x44))();
  if (iVar1 < 0) {
    FUN_00438a30();
    (**(code **)(*(int *)g_pD3DDevice + 0x40))(g_pD3DDevice,&DAT_00491d0c);
    FUN_00439d20(extraout_ECX);
    _DAT_00491fd4 = 2;
  }
  FUN_00438a60();
  if ((_DAT_00474e36 & 0x800) != 0) {
    FUN_00452abc("snapshot");
    iVar1 = 0;
    while( true ) {
      _sprintf((char *)&pvStack_118,"snapshot/th%.3d.bmp",iVar1);
      iVar2 = FUN_0044b4d0((LPCSTR)&pvStack_118);
      if (iVar2 == 0) break;
      iVar1 = iVar1 + 1;
      if (999 < iVar1) {
        return;
      }
    }
    if (iVar1 < 1000) {
      FUN_00420670();
    }
  }
  return;
}

