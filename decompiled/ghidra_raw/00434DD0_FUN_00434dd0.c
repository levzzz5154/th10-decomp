/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00434DD0
 * Tracking name: FUN_00434dd0
 * Ghidra name: FUN_00434dd0
 * Tracked span: 288 bytes
 */


/* WARNING: Removing unreachable block (ram,0x00434e80) */

byte * FUN_00434dd0(int param_1,byte *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  byte bVar6;
  char *pcVar7;
  undefined1 *unaff_EBP;
  undefined1 *_Size;
  byte *unaff_retaddr;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    return (byte *)0x0;
  }
  puVar2 = FUN_00434f30();
  if ((puVar2 != (undefined4 *)0x0) &&
     (((_Size = (undefined1 *)(puVar2[5] - puVar2[1]), _Size == (undefined1 *)puVar2[2] &&
       (param_2 != (byte *)0x0)) || (param_2 = _malloc((size_t)_Size), param_2 != (byte *)0x0)))) {
    cVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x18))(puVar2[1],0);
    if ((cVar1 != '\0') &&
       (iVar3 = (**(code **)(**(int **)(param_1 + 0xc) + 8))(param_2,_Size), iVar3 != 0)) {
      pcVar7 = (char *)*puVar2;
      pcVar4 = pcVar7;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      iVar3 = (int)pcVar4 - (int)(pcVar7 + 1);
      bVar6 = 0;
      if (iVar3 != 0) {
        bVar6 = 0;
        do {
          bVar6 = bVar6 + *pcVar7;
          pcVar7 = pcVar7 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      iVar3 = (bVar6 & 0x80000007) * 0xc;
      FUN_0044b0d0(param_2,(uint)_Size,(&DAT_00474bd9)[iVar3],*(int *)(&DAT_00474bdc + iVar3),
                   *(uint *)(&DAT_00474be0 + iVar3));
      pbVar5 = param_2;
      if (_Size != unaff_EBP) {
        pbVar5 = FUN_00435dc0(param_2,(int)_Size,unaff_retaddr,unaff_EBP);
      }
      if ((param_2 != unaff_retaddr) && (param_2 != (byte *)0x0)) {
        _free(param_2);
      }
      return pbVar5;
    }
    if (param_2 != (byte *)0x0) {
      _free(param_2);
    }
  }
  return (byte *)0x0;
}

