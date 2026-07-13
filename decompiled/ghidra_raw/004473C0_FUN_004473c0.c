/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004473C0
 * Tracking name: FUN_004473c0
 * Ghidra name: FUN_004473c0
 * Tracked span: 176 bytes
 */


int FUN_004473c0(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int local_4;
  
  piVar4 = *(int **)(param_2 + 0x108);
  bVar1 = false;
  iVar3 = 0;
  local_4 = 0;
  iVar5 = 0;
  while( true ) {
    if (local_4 == *(int *)(param_2 + 0x124) + -1) {
      iVar2 = FUN_00447470(param_1,param_2,iVar5,iVar3,piVar4);
      if (iVar2 < 0) {
        *(undefined4 *)(param_2 + 0x124) = 0;
        return 0;
      }
      bVar1 = true;
    }
    iVar5 = iVar5 + *piVar4;
    iVar3 = iVar3 + piVar4[1];
    if (piVar4[0xe] == 0) break;
    piVar4 = (int *)((int)piVar4 + piVar4[0xe]);
    local_4 = local_4 + 1;
    if ((local_4 == *(int *)(param_2 + 0x124)) || (bVar1)) {
      *(int *)(param_2 + 0x124) = *(int *)(param_2 + 0x124) + 1;
      return param_2;
    }
  }
  *(undefined4 *)(param_2 + 0x124) = 0;
  return param_2;
}

