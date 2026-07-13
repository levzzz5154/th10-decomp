/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00447700
 * Tracking name: FUN_00447700
 * Ghidra name: FUN_00447700
 * Tracked span: 208 bytes
 */


int __thiscall FUN_00447700(void *this,int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = 0;
  piVar3 = (int *)(param_1 + 0x3ad06c);
  do {
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x128) == 0) {
        if (*(int *)(iVar1 + 0x124) != 0) {
          iVar1 = FUN_004473c0(param_1,*(int *)(param_1 + 0x3ad06c + uVar2 * 4));
          return (iVar1 != 0) - 1;
        }
      }
      else {
        if ((-1 < (int)uVar2) && (uVar2 < 0x21)) {
          FUN_00447810(this);
          _free((void *)*piVar3);
          *piVar3 = 0;
        }
        this = (void *)*piVar3;
        *(undefined4 *)((int)this + 0x128) = 0;
      }
    }
    uVar2 = uVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (uVar2 < 0x21);
  return 0;
}

