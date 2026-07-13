/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00437FE0
 * Tracking name: FUN_00437fe0
 * Ghidra name: FUN_00437fe0
 * Tracked span: 528 bytes
 */


void FUN_00437fe0(undefined4 param_1,int param_2,int param_3,uint param_4,char *param_5,int *param_6
                 )

{
  char *pcVar1;
  uint uVar2;
  char cVar3;
  HDC hdc;
  HGDIOBJ pvVar4;
  char *pcVar5;
  int *unaff_EDI;
  
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
  FUN_00436ca0(param_4);
  hdc = DAT_00474dc4;
  pvVar4 = SelectObject(DAT_00474dc4,pvVar4);
  uVar2 = param_3 * 2 + 6;
  FUN_00437160(&DAT_00474cb0,uVar2);
  SetBkMode(hdc,1);
  pcVar1 = param_5 + 1;
  pcVar5 = param_5;
  do {
    cVar3 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar3 != '\0');
  SetTextColor(hdc,param_4);
  TextOutA(hdc,param_2 * 2,0,param_5,(int)pcVar5 - (int)pcVar1);
  SelectObject(hdc,pvVar4);
  FUN_00437160(&DAT_00474cb0,uVar2);
  FUN_00436da0(0x474cb0,uVar2);
  SelectObject(hdc,pvVar4);
  (**(code **)(*param_6 + 0x48))(param_6,0,&param_4);
  D3DXLoadSurfaceFromMemory
            (param_1,0,param_1,DAT_00474dd0,DAT_00474db0,DAT_00474dc0,0,&stack0xffffffe4,4,0);
  if (unaff_EDI != (int *)0x0) {
    (**(code **)(*unaff_EDI + 8))(unaff_EDI);
  }
  return;
}

