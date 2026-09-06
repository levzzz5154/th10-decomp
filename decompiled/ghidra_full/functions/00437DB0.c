/* Raw Ghidra reference; not compilable reconstruction. Address: 00437DB0 */

void FUN_00437db0(undefined4 param_1,int param_2,int param_3,COLORREF param_4,char *param_5,
                 int *param_6)

{
  char *pcVar1;
  char cVar2;
  HDC hdc;
  int iVar3;
  HGDIOBJ pvVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 unaff_retaddr;
  int *piVar9;
  
  uVar7 = DAT_00474dbc;
  pvVar4 = DAT_004918a0;
  if (((((0x11 < param_3) && (pvVar4 = DAT_0049189c, 0x12 < param_3)) &&
       (pvVar4 = DAT_00491898, 0x13 < param_3)) &&
      ((((pvVar4 = DAT_00491894, 0x14 < param_3 && (pvVar4 = DAT_00491890, 0x15 < param_3)) &&
        ((pvVar4 = DAT_0049188c, 0x16 < param_3 &&
         ((pvVar4 = DAT_00491888, 0x17 < param_3 && (pvVar4 = DAT_00491884, 0x18 < param_3)))))) &&
       (pvVar4 = DAT_00491880, 0x19 < param_3)))) &&
     ((((pvVar4 = DAT_0049187c, 0x1a < param_3 && (pvVar4 = DAT_00491878, 0x1b < param_3)) &&
       (pvVar4 = DAT_00491874, 0x1c < param_3)) &&
      ((pvVar4 = DAT_00491870, 0x1d < param_3 && (pvVar4 = DAT_0049186c, 0x1e < param_3)))))) {
    pvVar4 = DAT_00491868;
  }
  if (param_3 < 0x11) {
    param_3 = 0x11;
  }
  iVar3 = param_3;
  puVar8 = DAT_00474dd0;
  for (uVar6 = DAT_00474dbc >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  for (uVar7 = uVar7 & 3; hdc = DAT_00474dc4, uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar8 = 0;
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  pvVar4 = SelectObject(DAT_00474dc4,pvVar4);
  uVar7 = iVar3 * 2 + 6;
  FUN_00437160(&DAT_00474cb0,uVar7);
  SetBkMode(hdc,1);
  pcVar1 = param_5 + 1;
  pcVar5 = param_5;
  do {
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  SetTextColor(hdc,0);
  TextOutA(hdc,param_2 * 2 + 2,2,param_5,(int)pcVar5 - (int)pcVar1);
  SetTextColor(hdc,param_4);
  TextOutA(hdc,param_2 * 2,0,param_5,(int)pcVar5 - (int)pcVar1);
  SelectObject(hdc,pvVar4);
  FUN_00437160(&DAT_00474cb0,uVar7);
  FUN_00436da0(0x474cb0,uVar7);
  SelectObject(hdc,pvVar4);
  piVar9 = &param_3;
  (**(code **)(*param_6 + 0x48))(param_6,0);
  D3DXLoadSurfaceFromMemory
            (unaff_retaddr,0,param_1,DAT_00474dd0,DAT_00474db0,DAT_00474dc0,0,&stack0xffffffe4,4,0);
  if (piVar9 != (int *)0x0) {
    (**(code **)(*piVar9 + 8))(piVar9);
  }
  return;
}

