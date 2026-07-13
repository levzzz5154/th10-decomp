/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040AC20
 * Tracking name: FUN_0040ac20
 * Ghidra name: FUN_0040ac20
 * Tracked span: 112 bytes
 */


void __fastcall FUN_0040ac20(int param_1)

{
  ushort uVar1;
  ushort *puVar2;
  ushort uVar3;
  int iVar4;
  
  uVar1 = *(ushort *)(param_1 + 0x2c);
  *(undefined2 *)(param_1 + 4) = 0;
  iVar4 = 0x10;
  puVar2 = (ushort *)(param_1 + 0x38);
  do {
    if ((uVar1 & 1) == 0) {
      *puVar2 = 0;
    }
    else {
      *puVar2 = *puVar2 + 1;
      if (0x19 < *puVar2) {
        *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
        *puVar2 = *puVar2 - 8;
      }
    }
    uVar1 = uVar1 >> 1;
    puVar2 = puVar2 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  uVar1 = *(ushort *)(param_1 + 0x2c);
  uVar3 = *(ushort *)(param_1 + 0x2e) ^ uVar1;
  *(ushort *)(param_1 + 0x32) = uVar3 & uVar1;
  *(ushort *)(param_1 + 0x34) = ~uVar1 & uVar3;
  return;
}

