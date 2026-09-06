/* Raw Ghidra reference; not compilable reconstruction. Address: 00437750 */

uint __fastcall FUN_00437750(int param_1,int param_2,int *param_3,undefined4 param_4,int param_5)

{
  char cVar1;
  int in_EAX;
  uint uVar2;
  int iVar3;
  short *psVar4;
  undefined4 uVar5;
  byte *pbVar6;
  uint uVar7;
  int unaff_EBX;
  uint unaff_EBP;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  undefined1 auStack_40 [8];
  int aiStack_38 [3];
  undefined4 uStack_2c;
  undefined1 local_20 [12];
  int *piStack_14;
  int iStack_10;
  int iStack_c;
  int *piStack_4;
  
  uVar2 = 0;
  if (*(int *)(param_2 + 0x11c) != 0) {
    (**(code **)(*param_3 + 0x30))(param_3,local_20);
    aiStack_38[2] = *(undefined4 *)(param_2 + 0x104);
    uStack_2c = *(undefined4 *)(param_2 + 0x108);
    aiStack_38[0] = 0;
    aiStack_38[1] = 0;
    uVar2 = (**(code **)(*piStack_4 + 0x34))(piStack_4,auStack_40,aiStack_38,0);
    if (uVar2 == 0) {
      iStack_c = *(int *)(param_2 + 0x110);
      pbVar6 = *(byte **)(param_2 + 0x120);
      iVar9 = *(int *)(param_2 + 0x100);
      if (aiStack_38[0] == iVar9) {
        if (iVar9 == 0x15) {
          pbVar10 = (byte *)(unaff_EBP * in_EAX + unaff_EBX + param_1 * 4);
          if (0 < param_5) {
            do {
              iVar9 = 0;
              iVar3 = iStack_10;
              if (0 < iStack_10) {
                do {
                  uVar2 = (uint)pbVar6[3];
                  *pbVar10 = (char)(((uint)*pbVar6 - (uint)*pbVar10) * uVar2 >> 8) + *pbVar10;
                  pbVar10[1] = (char)(((uint)pbVar6[1] - (uint)pbVar10[1]) * uVar2 >> 8) +
                               pbVar10[1];
                  pbVar10[2] = (char)(((uint)pbVar6[2] - (uint)pbVar10[2]) * uVar2 >> 8) +
                               pbVar10[2];
                  pbVar10 = pbVar10 + 4;
                  pbVar6 = pbVar6 + 4;
                  iVar3 = iVar3 + -1;
                  iVar9 = iStack_10;
                } while (iVar3 != 0);
              }
              pbVar6 = pbVar6 + iStack_c + iVar9 * -4;
              pbVar10 = pbVar10 + unaff_EBP + iVar9 * -4;
              param_5 = param_5 + -1;
            } while (param_5 != 0);
          }
        }
        else if (iVar9 == 0x19) {
          psVar4 = (short *)(unaff_EBP * in_EAX + unaff_EBX + param_1 * 2);
          if (0 < param_5) {
            do {
              iVar9 = iStack_10;
              iVar3 = 0;
              if (0 < iStack_10) {
                do {
                  if (*(short *)pbVar6 < 0) {
                    *psVar4 = *(short *)pbVar6;
                  }
                  psVar4 = psVar4 + 1;
                  pbVar6 = pbVar6 + 2;
                  iVar9 = iVar9 + -1;
                  iVar3 = iStack_10;
                } while (iVar9 != 0);
              }
              pbVar6 = pbVar6 + iStack_c + iVar3 * -2;
              psVar4 = (short *)((int)psVar4 + unaff_EBP + iVar3 * -2);
              param_5 = param_5 + -1;
            } while (param_5 != 0);
          }
        }
        else {
          uVar2 = unaff_EBP;
          if (iVar9 != 0x1a) goto LAB_004377f2;
          pbVar10 = (byte *)(unaff_EBP * in_EAX + unaff_EBX + param_1 * 2);
          if (0 < param_5) {
            do {
              iVar9 = 0;
              iVar3 = iStack_10;
              if (0 < iStack_10) {
                do {
                  uVar8 = (uint)(pbVar6[1] >> 4);
                  *pbVar10 = ((char)((int)(((uint)(*pbVar6 >> 4) - (uint)(*pbVar10 >> 4)) * uVar8)
                                    >> 4) + (*pbVar10 >> 4)) * '\x10';
                  *pbVar10 = *pbVar10 | (byte)((int)((*pbVar6 & 0xf) * uVar8) >> 4);
                  uVar2 = (pbVar10[1] >> 2 & 0x3c) + uVar8;
                  cVar1 = (char)uVar2;
                  uVar7 = pbVar10[1] & 0xf;
                  if (0xf < uVar2) {
                    cVar1 = '\x0f';
                  }
                  pbVar10[1] = (char)((int)(((pbVar6[1] & 0xf) - uVar7) * uVar8) >> 4) + (char)uVar7
                               | cVar1 << 4;
                  pbVar10 = pbVar10 + 2;
                  pbVar6 = pbVar6 + 2;
                  iVar3 = iVar3 + -1;
                  iVar9 = iStack_10;
                } while (iVar3 != 0);
              }
              pbVar6 = pbVar6 + iStack_c + iVar9 * -2;
              pbVar10 = pbVar10 + unaff_EBP + iVar9 * -2;
              param_5 = param_5 + -1;
            } while (param_5 != 0);
          }
        }
      }
      uVar5 = (**(code **)(*piStack_14 + 0x38))(piStack_14);
      return CONCAT31((int3)((uint)uVar5 >> 8),1);
    }
  }
LAB_004377f2:
  return uVar2 & 0xffffff00;
}

