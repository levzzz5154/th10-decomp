/* Raw Ghidra reference; not compilable reconstruction. Address: 004356F0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined * __fastcall FUN_004356f0(uint *param_1)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  undefined *puVar9;
  bool bVar10;
  byte local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_108;
  puVar3 = FUN_00452730(param_1,'/');
  puVar4 = param_1;
  if (puVar3 != (uint *)0x0) {
    puVar4 = (uint *)((int)puVar3 + 1);
  }
  iVar5 = (int)puVar4 + (-1 - (int)param_1);
  iVar7 = -(int)param_1;
  do {
    uVar2 = *param_1;
    (local_108 + iVar7)[(int)param_1] = (byte)uVar2;
    param_1 = (uint *)((int)param_1 + 1);
  } while ((byte)uVar2 != 0);
  if (-1 < iVar5) {
    *(undefined4 *)(local_108 + iVar5) = DAT_0046f274;
    local_108[iVar5 + 4] = DAT_0046f278;
  }
  iVar7 = 0;
  puVar9 = &DAT_004923b0;
  if (0 < DAT_00477850) {
    do {
      pbVar6 = *(byte **)(puVar9 + 8);
      pbVar8 = local_108;
      do {
        bVar1 = *pbVar6;
        bVar10 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_00435794:
          iVar5 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00435799;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar6[1];
        bVar10 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_00435794;
        pbVar6 = pbVar6 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_00435799:
      if (iVar5 == 0) {
        return puVar9;
      }
      iVar7 = iVar7 + 1;
      puVar9 = puVar9 + 0x10;
    } while (iVar7 < DAT_00477850);
  }
  return (undefined *)0x0;
}

