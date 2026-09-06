/* Raw Ghidra reference; not compilable reconstruction. Address: 00450470 */

int FUN_00450470(byte *param_1)

{
  byte bVar1;
  int in_EAX;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  bool bVar8;
  
  iVar5 = 0;
  iVar4 = *(int *)(in_EAX + 8) + -1;
  if (-1 < iVar4) {
    do {
      iVar7 = (iVar4 - iVar5) / 2 + iVar5;
      pbVar6 = *(byte **)(*(int *)(in_EAX + 0x8c) + iVar7 * 8);
      pbVar3 = param_1;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar6;
        if (bVar1 != *pbVar6) {
LAB_004504c4:
          iVar2 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_004504c9;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar6[1];
        if (bVar1 != pbVar6[1]) goto LAB_004504c4;
        pbVar3 = pbVar3 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
      iVar2 = 0;
LAB_004504c9:
      if (iVar2 == 0) {
        return *(int *)(*(int *)(in_EAX + 0x8c) + 4 + iVar7 * 8) + 0x10;
      }
      if (iVar2 < 0) {
        iVar4 = iVar7 + -1;
      }
      else {
        iVar5 = iVar7 + 1;
      }
    } while (iVar5 <= iVar4);
  }
  return 0;
}

