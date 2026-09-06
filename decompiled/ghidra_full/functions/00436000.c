/* Raw Ghidra reference; not compilable reconstruction. Address: 00436000 */

int __fastcall FUN_00436000(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar4 = 0;
  iVar1 = DAT_0048f860;
  do {
    iVar5 = iVar1;
    iVar1 = 0;
    do {
      iVar3 = (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + param_2 & 0x1fffU)) -
              (uint)*(byte *)((int)&DAT_0048f868 + ((iVar5 - param_2) + iVar1 + param_2 & 0x1fffU));
      if (iVar3 != 0) break;
      iVar3 = (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 1 + param_2 & 0x1fffU)) -
              (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 1 + iVar5 & 0x1fffU));
      if (iVar3 != 0) {
        iVar1 = iVar1 + 1;
        break;
      }
      iVar3 = (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 2 + param_2 & 0x1fffU)) -
              (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 2 + iVar5 & 0x1fffU));
      if (iVar3 != 0) {
        iVar1 = iVar1 + 2;
        break;
      }
      iVar3 = (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 3 + param_2 & 0x1fffU)) -
              (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 3 + iVar5 & 0x1fffU));
      if (iVar3 != 0) {
        iVar1 = iVar1 + 3;
        break;
      }
      iVar3 = (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 4 + param_2 & 0x1fffU)) -
              (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 4 + iVar5 & 0x1fffU));
      if (iVar3 != 0) {
        iVar1 = iVar1 + 4;
        break;
      }
      iVar3 = (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 5 + param_2 & 0x1fffU)) -
              (uint)*(byte *)((int)&DAT_0048f868 + (iVar1 + 5 + iVar5 & 0x1fffU));
      if (iVar3 != 0) {
        iVar1 = iVar1 + 5;
        break;
      }
      iVar1 = iVar1 + 6;
    } while (iVar1 < 0x12);
    if ((iVar4 <= iVar1) && (*param_3 = iVar5, iVar4 = iVar1, 0x11 < iVar1)) {
      piVar2 = &DAT_00477858 + iVar5 * 3;
      iVar4 = *piVar2;
      if ((&DAT_0047785c)[iVar4 * 3] == iVar5) {
        (&DAT_0047785c)[iVar4 * 3] = param_2;
      }
      else {
        (&DAT_00477860)[iVar4 * 3] = param_2;
      }
      (&DAT_00477858)[param_2 * 3] = *piVar2;
      (&DAT_0047785c)[param_2 * 3] = (&DAT_0047785c)[iVar5 * 3];
      (&DAT_00477860)[param_2 * 3] = (&DAT_00477860)[iVar5 * 3];
      (&DAT_00477858)[(&DAT_0047785c)[param_2 * 3] * 3] = param_2;
      (&DAT_00477858)[(&DAT_00477860)[param_2 * 3] * 3] = param_2;
      *piVar2 = 0;
      return iVar1;
    }
    if (iVar3 < 0) {
      piVar2 = &DAT_0047785c + iVar5 * 3;
    }
    else {
      piVar2 = &DAT_00477860 + iVar5 * 3;
    }
    iVar1 = *piVar2;
    if (*piVar2 == 0) {
      *piVar2 = param_2;
      (&DAT_00477858)[param_2 * 3] = iVar5;
      (&DAT_00477860)[param_2 * 3] = 0;
      (&DAT_0047785c)[param_2 * 3] = 0;
      return iVar4;
    }
  } while( true );
}

