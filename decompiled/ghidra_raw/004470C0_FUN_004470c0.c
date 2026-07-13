/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004470C0
 * Tracking name: FUN_004470c0
 * Ghidra name: FUN_004470c0
 * Tracked span: 448 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int * FUN_004470c0(int param_1,int param_2,char *param_3)

{
  char cVar1;
  byte *pbVar2;
  int *piVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  void *pvVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int local_110;
  int local_10c;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_110;
  local_110 = param_1;
  if (param_2 < 0x21) {
    _sprintf(local_108,"%s",param_3);
    pbVar2 = FUN_0044b360((size_t *)0x0,0);
    local_10c = 0;
    piVar3 = operator_new(0x130);
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar11 = piVar3;
      for (iVar7 = 0x4c; iVar7 != 0; iVar7 = iVar7 + -1) {
        *piVar11 = 0;
        piVar11 = piVar11 + 1;
      }
    }
    *(int **)(local_110 + 0x3ad06c + param_2 * 4) = piVar3;
    if (pbVar2 != (byte *)0x0) {
      *piVar3 = param_2;
      piVar3[0x42] = (int)pbVar2;
      iVar7 = 4 - (int)param_3;
      do {
        cVar1 = *param_3;
        param_3[(int)piVar3 + iVar7] = cVar1;
        param_3 = param_3 + 1;
      } while (cVar1 != '\0');
      local_110 = *(int *)pbVar2;
      iVar10 = *(int *)(pbVar2 + 4);
      uVar8 = 1;
      iVar7 = *(int *)(pbVar2 + 0x38);
      pbVar4 = pbVar2;
      while (iVar7 != 0) {
        pbVar4 = pbVar4 + iVar7;
        iVar10 = iVar10 + *(int *)(pbVar4 + 4);
        local_110 = local_110 + *(int *)pbVar4;
        uVar8 = uVar8 + 1;
        iVar7 = *(int *)(pbVar4 + 0x38);
      }
      piVar3[0x43] = uVar8;
      puVar5 = _malloc(uVar8 << 4);
      iVar7 = local_110;
      piVar3[0x48] = (int)puVar5;
      for (iVar9 = (uVar8 & 0xfffffff) << 2; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
        *(undefined1 *)puVar5 = 0;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
      pvVar6 = _malloc(local_110 * 0x44);
      piVar3[0x46] = (int)pvVar6;
      pvVar6 = _malloc(iVar10 * 4);
      piVar3[0x47] = (int)pvVar6;
      piVar3[0x44] = iVar10;
      piVar3[0x45] = iVar7;
      iVar7 = FUN_004472e0(0,(int)piVar3,(int)pbVar2);
      while (-1 < iVar7) {
        local_10c = local_10c + 1;
        if (*(int *)(pbVar2 + 0x38) == 0) {
          return piVar3;
        }
        pbVar2 = pbVar2 + *(int *)(pbVar2 + 0x38);
        iVar7 = FUN_004472e0(local_10c,(int)piVar3,(int)pbVar2);
      }
    }
  }
  else {
    FUN_0044b8e0(&DAT_00470384);
  }
  return (int *)0x0;
}

