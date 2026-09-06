/* Raw Ghidra reference; not compilable reconstruction. Address: 00439890 */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00439890(void)

{
  bool bVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 uVar3;
  int *piVar4;
  int *piVar5;
  float10 fVar6;
  void *pvVar7;
  char cVar8;
  undefined4 uVar9;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  float fStack_58;
  int local_48 [4];
  int local_38 [5];
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  piVar4 = local_48 + 4;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  uVar9 = 0;
  (**(code **)(*(int *)g_pD3D9 + 0x20))(g_pD3D9,0,local_48);
  if (DAT_00491d65 == '\0') {
    if ((DAT_00491d78 & 1) == 0) {
      if (DAT_00491d62 == -1) {
        local_48[3] = 0x16;
        DAT_00491d62 = '\0';
        FUN_0044b810(&DAT_00474f70,&DAT_0046f640);
      }
      else {
        local_48[3] = (DAT_00491d62 != '\0') + 0x16;
      }
    }
    else {
      local_48[3] = 0x17;
      DAT_00491d62 = '\x01';
    }
    if (DAT_00492518 == '\0') {
      if (DAT_00491fdc == 0) {
        uStack_14 = 0x3c;
        iStack_10 = 1;
        FUN_0044b810(&DAT_00474f70,&DAT_0046f614);
        goto LAB_004399a6;
      }
    }
    else {
      DAT_00491fdc = 1;
    }
    uStack_14 = 0;
    local_38[3] = 1;
    iStack_10 = -0x80000000;
    FUN_0044b810(&DAT_00474f70,&DAT_0046f5f0);
  }
  else {
    local_48[3] = local_48[0];
    uStack_24 = 1;
LAB_004399a6:
    local_38[3] = 1;
  }
  DAT_00491ff4 = DAT_00491ff4 | 2;
  local_48[1] = 0x280;
  local_48[2] = 0x1e0;
  uStack_20 = 1;
  uStack_1c = 0x50;
  uStack_18 = 1;
  _DAT_00491fe0 = 1;
  bVar1 = false;
  while( true ) {
    if ((DAT_00491d78 & 2) == 0) {
      iVar2 = (**(code **)(*(int *)g_pD3D9 + 0x40))
                        (g_pD3D9,0,1,g_pWnd,0x40,local_48 + 1,&g_pD3DDevice);
      if (-1 < iVar2) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046f4a8);
        DAT_00491ff4 = DAT_00491ff4 | 1;
        goto LAB_00439b68;
      }
      if (bVar1) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046f5cc);
      }
      iVar2 = (**(code **)(*(int *)g_pD3D9 + 0x40))
                        (g_pD3D9,0,1,g_pWnd,0x20,local_48 + 1,&g_pD3DDevice);
      if (-1 < iVar2) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046f4c4);
        DAT_00491ff4 = DAT_00491ff4 & 0xfffffffe;
        goto LAB_00439b68;
      }
      if (bVar1) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046f5ac);
      }
    }
    iVar2 = (**(code **)(*(int *)g_pD3D9 + 0x40))
                      (g_pD3D9,0,2,g_pWnd,0x20,local_48 + 1,&g_pD3DDevice);
    if (-1 < iVar2) break;
    if (DAT_00491fdc == 0) {
      FUN_0044b810(&DAT_00474f70,&DAT_0046f584);
      uStack_14 = 0;
      _DAT_00491fe0 = 0;
      bVar1 = true;
    }
    else {
      if (iStack_10 != -0x80000000) {
        FUN_0044b8e0(&DAT_0046f514);
        if (g_pD3D9 != (void *)0x0) {
          (**(code **)(*(int *)g_pD3D9 + 8))(g_pD3D9);
          g_pD3D9 = (void *)0x0;
        }
        return 1;
      }
      FUN_0044b810(&DAT_00474f70,&DAT_0046f54c);
      iStack_10 = 1;
      local_38[3] = 3;
    }
  }
  FUN_0044b810(&DAT_00474f70,&DAT_0046f4d8);
  DAT_00491ff4 = DAT_00491ff4 & 0xfffffffe;
LAB_00439b68:
  fVar6 = (float10)fptan((float10)_DAT_00470c00);
  piVar4 = local_48;
  piVar5 = &DAT_00491d0c;
  for (iVar2 = 0xe; piVar4 = (int *)((int)piVar4 + 4), iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = *piVar4;
    piVar5 = piVar5 + 1;
  }
  uStack_60 = 0x43a00000;
  uStack_5c = 0xc3700000;
  uStack_6c = 0x43a00000;
  uStack_68 = 0xc3700000;
  uStack_64 = 0;
  fStack_58 = (float)-((float10)_DAT_00470bfc / fVar6);
  D3DXMatrixLookAtLH(&DAT_00491c74,&uStack_60,&uStack_6c,&stack0xffffff88);
  D3DXMatrixPerspectiveFovLH(&DAT_00491cb4,0x3f060a92,0x3faaaaab,0x42c80000,0x461c4000);
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,2,&DAT_00491c74);
  pvVar7 = g_pD3DDevice;
  (**(code **)(*(int *)g_pD3DDevice + 0xb0))(g_pD3DDevice,3,&DAT_00491cb4);
  cVar8 = (char)((uint)pvVar7 >> 0x18);
  (**(code **)(*(int *)g_pD3DDevice + 0xc0))(g_pD3DDevice,&DAT_00491cf4);
  (**(code **)(*(int *)g_pD3DDevice + 0x1c))(g_pD3DDevice,&DAT_00492000);
  uVar3 = extraout_ECX;
  if ((DAT_00492090 & 0x40) == 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046f458);
    uVar3 = extraout_ECX_00;
  }
  if (DAT_00492058 < 0x101) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046f408);
    uVar3 = extraout_ECX_01;
  }
  if (((DAT_00491d78 & 1) == 0) && (cVar8 != '\0')) {
    iVar2 = (**(code **)(*(int *)g_pD3D9 + 0x28))(g_pD3D9,0,1,uVar9,0,3,0x15);
    if (iVar2 == 0) {
      DAT_00491ff4 = DAT_00491ff4 | 4;
      uVar3 = extraout_ECX_02;
    }
    else {
      DAT_00491d78 = DAT_00491d78 | 1;
      DAT_00491ff4 = DAT_00491ff4 & 0xfffffffb;
      FUN_0044b810(&DAT_00474f70,&DAT_0046f3c0);
      uVar3 = extraout_ECX_03;
    }
  }
  FUN_00439d20(uVar3);
  FUN_0043bcd0();
  DAT_004924f4 = 0;
  _DAT_00491fe4 = 0;
  return 0;
}

