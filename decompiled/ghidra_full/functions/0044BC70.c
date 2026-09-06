/* Raw Ghidra reference; not compilable reconstruction. Address: 0044BC70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void NormalizeAngle(float param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  do {
    if (param_1 <= _DAT_00470b18) break;
    param_1 = param_1 - _DAT_00470b14;
    iVar3 = iVar2 + 1;
    bVar1 = iVar2 < 0x21;
    iVar2 = iVar3;
  } while (bVar1);
  do {
    if (_DAT_00470b10 <= param_1) {
      return;
    }
    param_1 = param_1 + _DAT_00470b14;
    bVar1 = iVar2 < 0x21;
    iVar2 = iVar2 + 1;
  } while (bVar1);
  return;
}

