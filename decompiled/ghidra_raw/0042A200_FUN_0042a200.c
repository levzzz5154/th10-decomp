/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042A200
 * Tracking name: FUN_0042a200
 * Ghidra name: FUN_0042a200
 * Tracked span: 592 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_0042a200(char *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  byte *pbVar6;
  void *pvVar7;
  short *psVar8;
  char *pcVar9;
  int iVar10;
  int unaff_ESI;
  size_t local_108;
  char local_104 [256];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_108;
  pcVar9 = param_1;
  do {
    cVar1 = *pcVar9;
    pcVar9[(unaff_ESI - (int)param_1) + 0x1d4] = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (((byte)DAT_00474ca0 & 0x20) == 0) {
    _sprintf(local_104,"replay/%s",param_1);
    iVar3 = FUN_0044b4d0(local_104);
    if (iVar3 != 0) {
      iVar3 = FUN_0044b6b0(local_104);
      if (iVar3 == 0) {
        piVar4 = FUN_0044b790();
        *(int **)(unaff_ESI + 0x14) = piVar4;
        if ((*piVar4 == 0x72303174) && ((short)piVar4[1] == 5)) {
          pbVar6 = FUN_0044b790();
          FUN_0044b7e0();
          goto LAB_0042a2be;
        }
        FUN_0044b7e0();
      }
    }
    uVar5 = 0xffffffff;
  }
  else {
    pbVar6 = FUN_0044b360(&local_108,0);
    *(byte **)(unaff_ESI + 0x14) = pbVar6;
    pbVar6 = pbVar6 + 0x24;
LAB_0042a2be:
    pvVar7 = _malloc(*(size_t *)(*(int *)(unaff_ESI + 0x14) + 0x20));
    *(void **)(unaff_ESI + 0x1c0) = pvVar7;
    uVar2 = *(uint *)(*(int *)(unaff_ESI + 0x14) + 0x1c);
    FUN_0044b0d0(pbVar6,uVar2,-0x1f,0x400,uVar2);
    uVar2 = *(uint *)(*(int *)(unaff_ESI + 0x14) + 0x1c);
    FUN_0044b0d0(pbVar6,uVar2,'z',0x80,uVar2);
    FUN_00435dc0(pbVar6,*(int *)(*(int *)(unaff_ESI + 0x14) + 0x1c),
                 *(undefined1 **)(unaff_ESI + 0x1c0),
                 *(undefined1 **)(*(int *)(unaff_ESI + 0x14) + 0x20));
    *(int *)(unaff_ESI + 0x18) = *(int *)(unaff_ESI + 0x1c0);
    psVar8 = (short *)(*(int *)(unaff_ESI + 0x1c0) + 100);
    iVar3 = 0;
    while( true ) {
      iVar10 = *(int *)(*(int *)(unaff_ESI + 0x18) + 0x4c);
      if (7 < iVar10) {
        iVar10 = 6;
      }
      if (iVar10 <= iVar3) break;
      *(short **)(unaff_ESI + 0xb0 + *psVar8 * 0x24) = psVar8;
      *(short **)(unaff_ESI + 0xa0 + *psVar8 * 0x24) = psVar8 + 0xe2;
      *(int *)(unaff_ESI + *psVar8 * 0x24 + 0xa8) =
           *(int *)(unaff_ESI + 0xa0 + *psVar8 * 0x24) + *(int *)(psVar8 + 2) * 6;
      psVar8 = (short *)((int)psVar8 + *(int *)(psVar8 + 4) + 0x1c4);
      iVar3 = iVar3 + 1;
    }
    if ((((byte)DAT_00474ca0 & 0x20) == 0) && (pbVar6 != (byte *)0x0)) {
      _free(pbVar6);
    }
    uVar5 = 0;
  }
  return uVar5;
}

