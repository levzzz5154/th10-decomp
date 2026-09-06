/* Raw Ghidra reference; not compilable reconstruction. Address: 0044A950 */

void __fastcall FUN_0044a950(int param_1)

{
  ushort in_AX;
  int iVar1;
  ushort *puVar2;
  ushort *puVar3;
  ushort uVar4;
  int iVar5;
  
  iVar1 = param_1 * 0x6a;
  puVar2 = &DAT_00474e30 + param_1 * 0x35;
  *(ushort *)(&DAT_00474e32 + iVar1) = *puVar2;
  *puVar2 = in_AX;
  uVar4 = 1;
  *(undefined2 *)(&DAT_00474e34 + iVar1) = 0;
  puVar3 = (ushort *)(&DAT_00474e3a + iVar1);
  iVar5 = 0x10;
  do {
    if ((in_AX & 1) == 0) {
      *puVar3 = 0;
    }
    else {
      *puVar3 = *puVar3 + 1;
      if (0x19 < *puVar3) {
        *(ushort *)(&DAT_00474e34 + iVar1) = *(ushort *)(&DAT_00474e34 + iVar1) | uVar4;
        *puVar3 = *puVar3 - 8;
      }
    }
    in_AX = in_AX >> 1;
    puVar3 = puVar3 + 1;
    uVar4 = uVar4 << 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  uVar4 = *puVar2;
  *(ushort *)(&DAT_00474e36 + iVar1) = (*(ushort *)(&DAT_00474e32 + iVar1) ^ uVar4) & uVar4;
  *(ushort *)(&DAT_00474e38 + iVar1) = ~uVar4 & (*(ushort *)(&DAT_00474e32 + iVar1) ^ uVar4);
  return;
}

