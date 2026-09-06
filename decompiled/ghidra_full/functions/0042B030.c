/* Raw Ghidra reference; not compilable reconstruction. Address: 0042B030 */

undefined4 FUN_0042b030(void)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte bVar6;
  undefined1 *puVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  int iVar10;
  int *piVar11;
  int *unaff_EBX;
  int iVar12;
  int *piVar13;
  int *piVar14;
  int local_4;
  
  piVar11 = (int *)*unaff_EBX;
  if (piVar11 != (int *)0x0) {
    if ((*piVar11 == 0x30314854) && ((short)piVar11[2] == 3)) {
      DecryptDatBuffer((byte *)(piVar11 + 6),piVar11[4],'5',0x10,piVar11[4]);
      iVar10 = *unaff_EBX;
      puVar7 = _malloc(*(int *)(iVar10 + 0x14) << 2);
      unaff_EBX[1] = (int)puVar7;
      DecompressDatLzss((byte *)(iVar10 + 0x18),*(int *)(*unaff_EBX + 0x10),puVar7,
                        *(undefined1 **)(*unaff_EBX + 0x14));
      local_4 = *(int *)(*unaff_EBX + 0x14);
      piVar11 = (int *)unaff_EBX[1];
      if (local_4 < 1) {
        return 0;
      }
      do {
        piVar13 = piVar11;
        if ((short)*piVar11 == 0x5243) {
          if (*(short *)((int)piVar11 + 2) == 0) {
            iVar10 = 0;
            pbVar8 = (byte *)(piVar11 + 3);
            iVar12 = 0xb3e;
            do {
              pbVar1 = pbVar8 + -3;
              pbVar2 = pbVar8 + -4;
              pbVar3 = pbVar8 + -2;
              pbVar4 = pbVar8 + -1;
              pbVar5 = pbVar8 + 1;
              bVar6 = *pbVar8;
              pbVar8 = pbVar8 + 6;
              iVar12 = iVar12 + -1;
              iVar10 = (uint)*pbVar2 + (uint)*pbVar1 + (uint)*pbVar3 + (uint)*pbVar4 + (uint)*pbVar5
                       + (uint)bVar6 + iVar10;
            } while (iVar12 != 0);
            if ((iVar10 == piVar11[1]) && (piVar11[2] == 0x437c)) {
              iVar10 = 0x10df;
              piVar14 = unaff_EBX + piVar11[3] * 0x10df + 2;
code_r0x0042b15f:
              for (; iVar10 != 0; iVar10 = iVar10 + -1) {
                *piVar14 = *piVar13;
                piVar13 = piVar13 + 1;
                piVar14 = piVar14 + 1;
              }
            }
          }
        }
        else {
          if ((short)*piVar11 != 0x5453) break;
          if (*(short *)((int)piVar11 + 2) == 0) {
            iVar10 = 0;
            pbVar8 = (byte *)((int)piVar11 + 10);
            iVar12 = 0x110;
            do {
              pbVar1 = pbVar8 + -1;
              pbVar2 = pbVar8 + -2;
              pbVar3 = pbVar8 + 1;
              bVar6 = *pbVar8;
              pbVar8 = pbVar8 + 4;
              iVar12 = iVar12 + -1;
              iVar10 = (uint)*pbVar2 + (uint)*pbVar1 + (uint)*pbVar3 + (uint)bVar6 + iVar10;
            } while (iVar12 != 0);
            if ((iVar10 == piVar11[1]) && (piVar11[2] == 0x448)) {
              piVar14 = unaff_EBX + 0x761b;
              iVar10 = 0x112;
              goto code_r0x0042b15f;
            }
          }
        }
        local_4 = local_4 - piVar11[2];
        if (local_4 < 0) break;
        piVar11 = (int *)((int)piVar11 + piVar11[2]);
        if (local_4 < 1) {
          return 0;
        }
      } while( true );
    }
    if ((void *)*unaff_EBX != (void *)0x0) {
      _free((void *)*unaff_EBX);
      *unaff_EBX = 0;
    }
  }
  puVar9 = _malloc(0x18);
  *unaff_EBX = (int)puVar9;
  *puVar9 = 0;
  puVar9[1] = 0;
  puVar9[2] = 0;
  puVar9[3] = 0;
  puVar9[4] = 0;
  puVar9[5] = 0;
  *(undefined4 *)*unaff_EBX = 0x30314854;
  *(undefined2 *)(*unaff_EBX + 8) = 3;
  *(undefined4 *)(*unaff_EBX + 0xc) = 0x100;
  return 0;
}

