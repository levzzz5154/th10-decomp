/* Raw Ghidra reference; not compilable reconstruction. Address: 00436460 */

uint __thiscall FUN_00436460(void *this,undefined4 *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)((int)this + 8);
  uVar1 = (*(int *)((int)this + 0xc) + *(int *)((int)this + 4)) - (int)puVar3;
  if (param_2 <= uVar1) {
    for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *param_1 = *puVar3;
      puVar3 = puVar3 + 1;
      param_1 = param_1 + 1;
    }
    for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)param_1 = *(undefined1 *)puVar3;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      param_1 = (undefined4 *)((int)param_1 + 1);
    }
    *(uint *)((int)this + 8) = *(int *)((int)this + 8) + param_2;
    return param_2;
  }
  if (uVar1 != 0) {
    for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_1 = *puVar3;
      puVar3 = puVar3 + 1;
      param_1 = param_1 + 1;
    }
    for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)param_1 = *(undefined1 *)puVar3;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      param_1 = (undefined4 *)((int)param_1 + 1);
    }
    *(uint *)((int)this + 8) = *(int *)((int)this + 8) + uVar1;
    return uVar1;
  }
  return 0;
}

