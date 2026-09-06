/* Raw Ghidra reference; not compilable reconstruction. Address: 00408210 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00408210(int param_1)

{
  float *this;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  int *piVar8;
  int iVar9;
  undefined4 extraout_ECX;
  undefined4 uVar10;
  int unaff_EBX;
  uint *puVar11;
  int local_38;
  
  fVar6 = *(float *)(unaff_EBX + 0x50) * _DAT_00470b0c;
  puVar11 = (uint *)(unaff_EBX + 0x60);
  local_38 = 2000;
  fVar7 = *(float *)(unaff_EBX + 0x54) * _DAT_00470b0c;
  fVar1 = *(float *)(unaff_EBX + 0x44);
  fVar2 = *(float *)(unaff_EBX + 0x48);
  fVar3 = *(float *)(unaff_EBX + 0x44);
  fVar4 = *(float *)(unaff_EBX + 0x48);
  do {
    if ((*(short *)((int)puVar11 + 0x446) != 0) && (*(short *)((int)puVar11 + 0x446) != 3)) {
      this = (float *)(puVar11 + 0xed);
      if ((fVar1 - fVar6 <= (float)puVar11[0xfc] * _DAT_00470b0c + *this) &&
         (((*this - (float)puVar11[0xfc] * _DAT_00470b0c <= fVar6 + fVar3 &&
           (fVar2 - fVar7 <= (float)puVar11[0xfd] * _DAT_00470b0c + (float)puVar11[0xee])) &&
          ((float)puVar11[0xee] - (float)puVar11[0xfd] * _DAT_00470b0c <= fVar7 + fVar4)))) {
        *puVar11 = *puVar11 | 8;
        if (param_1 != 0) {
          FUN_0041bb00(this,8,0xffffffff,-1.5707964,0.6);
        }
        piVar8 = (int *)FUN_00448db0(*(undefined2 **)(unaff_EBX + 0x3e0b50));
        iVar9 = FUN_004491c0(extraout_ECX,(int)g_pGameStateManager,*piVar8);
        uVar5 = puVar11[0xe7];
        if (uVar5 != 0) {
          if (*(float *)(uVar5 + 0x34) < _DAT_00470b48 ==
              (*(float *)(uVar5 + 0x34) == _DAT_00470b48)) {
            if (*(float *)(uVar5 + 0x34) < _DAT_00470bcc ==
                (*(float *)(uVar5 + 0x34) == _DAT_00470bcc)) {
              uVar10 = *(undefined4 *)(&DAT_004743b0 + (short)puVar11[0x1fb] * 4);
            }
            else {
              uVar10 = *(undefined4 *)(&DAT_00474390 + (short)puVar11[0x1fb] * 4);
            }
          }
          else {
            uVar10 = *(undefined4 *)(&DAT_00474350 + (short)puVar11[0x1fb] * 4);
          }
          *(undefined4 *)(iVar9 + 0x2fc) = uVar10;
        }
        puVar11[0x114] = 0;
      }
    }
    puVar11 = puVar11 + 0x1fc;
    local_38 = local_38 + -1;
  } while (local_38 != 0);
  return 0;
}

