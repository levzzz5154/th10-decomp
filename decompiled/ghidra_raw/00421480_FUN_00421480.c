/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421480
 * Tracking name: FUN_00421480
 * Ghidra name: FUN_00421480
 * Tracked span: 288 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00421480(void)

{
  void *pvVar1;
  int unaff_EDI;
  float10 fVar2;
  float10 fVar3;
  undefined4 *puVar4;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (g_pGameStateManager != (void *)0x0) {
    FUN_00442f50();
  }
  local_18 = (float)*(int *)(unaff_EDI + 0xd4);
  if (*(int *)(unaff_EDI + 0xd4) < 0) {
    local_18 = local_18 + _DAT_00470b98;
  }
  local_18 = local_18 * _DAT_00470b0c;
  fVar2 = (float10)*(int *)(unaff_EDI + 0xd8);
  if (*(int *)(unaff_EDI + 0xd8) < 0) {
    fVar2 = fVar2 + (float10)_DAT_00470b98;
  }
  puVar4 = &local_24;
  fVar2 = fVar2 * (float10)_DAT_00470b0c;
  local_10 = 0;
  local_24 = 0;
  local_20 = 0xbf800000;
  local_1c = 0;
  local_8 = (float)fVar2;
  fVar3 = (float10)fptan((float10)_DAT_00470ba0);
  local_4 = (float)(fVar2 / fVar3);
  local_14 = (float)fVar2;
  local_c = local_18;
  D3DXMatrixLookAtLH(unaff_EDI + 0x4c,&local_c,&local_18,puVar4);
  D3DXMatrixPerspectiveFovLH(unaff_EDI + 0x8c,0x3ea0d97c,puVar4,0x3f800000,0x461c4000);
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,2,unaff_EDI + 0x4c);
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,3,unaff_EDI + 0x8c);
  pvVar1 = g_pGameStateManager;
  if (g_pGameStateManager != (void *)0x0) {
    *(undefined4 *)((int)g_pGameStateManager + 0x5c) = *(undefined4 *)(unaff_EDI + 0xe8);
    *(undefined4 *)((int)pvVar1 + 0x60) = *(undefined4 *)(unaff_EDI + 0xec);
  }
  return;
}

