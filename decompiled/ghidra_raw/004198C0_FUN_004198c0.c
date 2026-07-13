/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004198C0
 * Tracking name: FUN_004198c0
 * Ghidra name: FUN_004198c0
 * Tracked span: 160 bytes
 */


undefined4 __fastcall FUN_004198c0(undefined4 param_1,byte *param_2,int param_3,int param_4)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  bool bVar6;
  
  iVar5 = 0;
  if (0 < param_4) {
    do {
      pbVar4 = *(byte **)(param_3 + iVar5 * 8);
      pbVar2 = param_2;
      do {
        bVar1 = *pbVar2;
        bVar6 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_004198fc:
          iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_00419901;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar6 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_004198fc;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00419901:
      if (iVar3 == 0) {
        return *(undefined4 *)(param_3 + 4 + iVar5 * 8);
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < param_4);
  }
  return 0;
}

