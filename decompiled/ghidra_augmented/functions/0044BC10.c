/* Raw Ghidra reference; not compilable reconstruction. Address: 0044BC10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044bc10(float param_1,float param_2)

{
  bool bVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  fVar2 = param_1 + param_2;
  iVar3 = 0;
  do {
    if (fVar2 <= _DAT_00470b18) break;
    fVar2 = fVar2 - _DAT_00470b14;
    iVar4 = iVar3 + 1;
    bVar1 = iVar3 < 0x21;
    iVar3 = iVar4;
  } while (bVar1);
  do {
    if (_DAT_00470b10 <= fVar2) {
      return;
    }
    fVar2 = fVar2 + _DAT_00470b14;
    bVar1 = iVar3 < 0x21;
    iVar3 = iVar3 + 1;
  } while (bVar1);
  return;
}

