/* Raw Ghidra reference; not compilable reconstruction. Address: 004215A0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004215a0(void)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  void *pvVar5;
  float *unaff_EDI;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (g_pGameStateManager != (void *)0x0) {
    FUN_00442f50();
  }
  pfVar1 = unaff_EDI + 6;
  local_18 = unaff_EDI[3] + *unaff_EDI;
  local_14 = unaff_EDI[4] + unaff_EDI[1];
  local_10 = unaff_EDI[5] + unaff_EDI[2];
  local_c = unaff_EDI[0xf] + *unaff_EDI;
  local_8 = unaff_EDI[0x10] + unaff_EDI[1];
  local_4 = unaff_EDI[0x11] + unaff_EDI[2];
  D3DXMatrixLookAtLH(unaff_EDI + 0x13,&local_c,&local_18,pfVar1);
  fVar3 = (float)(int)unaff_EDI[0x35];
  if ((int)unaff_EDI[0x35] < 0) {
    fVar3 = fVar3 + _DAT_00470b98;
  }
  fVar4 = (float)(int)unaff_EDI[0x36];
  if ((int)unaff_EDI[0x36] < 0) {
    fVar4 = fVar4 + _DAT_00470b98;
  }
  D3DXMatrixPerspectiveFovLH(unaff_EDI + 0x23,unaff_EDI[0x12],fVar3 / fVar4,0x41f00000,0x44e10000);
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,2,unaff_EDI + 0x13);
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,3,unaff_EDI + 0x23);
  pfVar2 = unaff_EDI + 0xc;
  *pfVar2 = unaff_EDI[8] * unaff_EDI[4] - unaff_EDI[7] * unaff_EDI[5];
  unaff_EDI[0xd] = *pfVar1 * unaff_EDI[5] - unaff_EDI[8] * unaff_EDI[3];
  unaff_EDI[0xe] = unaff_EDI[7] * unaff_EDI[3] - *pfVar1 * unaff_EDI[4];
  D3DXVec3Normalize(pfVar2,pfVar2);
  pvVar5 = g_pGameStateManager;
  if (g_pGameStateManager != (void *)0x0) {
    *(float *)((int)g_pGameStateManager + 0x5c) = unaff_EDI[0x3a];
    *(float *)((int)pvVar5 + 0x60) = unaff_EDI[0x3b];
  }
  return;
}

