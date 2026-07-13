/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043DC90
 * Tracking name: FUN_0043dc90
 * Ghidra name: FUN_0043dc90
 * Tracked span: 128 bytes
 */


void __thiscall FUN_0043dc90(void *this,undefined4 param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int unaff_EDI;
  
  sVar1 = *(short *)(&DAT_004749ce + unaff_EDI * 8);
  iVar3 = 0;
  piVar4 = (int *)((int)this + 0x620);
  do {
    if (*piVar4 < 0) {
      if (0xb < iVar3) {
        return;
      }
      *(int *)((int)this + iVar3 * 4 + 0x620) = unaff_EDI;
      *(int *)((int)this + unaff_EDI * 4 + 0x408) = (int)sVar1;
      *(undefined4 *)(iVar3 * 0x200 + 0x680 + (int)this) = param_1;
LAB_0043dcfe:
      piVar4 = (int *)((int)this + iVar3 * 4 + 0x650);
      *piVar4 = *piVar4 + 1;
      return;
    }
    if (*piVar4 == unaff_EDI) {
      iVar2 = *(int *)((int)this + iVar3 * 4 + 0x650);
      if (0x7f < iVar2) {
        return;
      }
      *(undefined4 *)((int)this + (iVar3 * 0x80 + iVar2) * 4 + 0x680) = param_1;
      goto LAB_0043dcfe;
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
    if (0xb < iVar3) {
      return;
    }
  } while( true );
}

