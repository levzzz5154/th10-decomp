/* Raw Ghidra reference; not compilable reconstruction. Address: 00438260 */

void * __thiscall FUN_00438260(void *this,void *param_1,uint param_2,uint param_3)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *piVar6;
  
  if (*(uint *)((int)param_1 + 0x14) < param_2) {
    FUN_00462428();
  }
  uVar4 = *(int *)((int)param_1 + 0x14) - param_2;
  if (param_3 < uVar4) {
    uVar4 = param_3;
  }
  if (this != param_1) {
    if (uVar4 == 0xffffffff) {
      FUN_004624e5();
    }
    if (*(uint *)((int)this + 0x18) < uVar4) {
      FUN_004386b0(this,uVar4);
    }
    else if (uVar4 == 0) {
      *(undefined4 *)((int)this + 0x14) = 0;
      if (*(uint *)((int)this + 0x18) < 0x10) {
        *(undefined1 *)((int)this + 4) = 0;
        return this;
      }
      **(undefined1 **)((int)this + 4) = 0;
      return this;
    }
    if (uVar4 != 0) {
      if (*(uint *)((int)param_1 + 0x18) < 0x10) {
        iVar3 = (int)param_1 + 4;
      }
      else {
        iVar3 = *(int *)((int)param_1 + 4);
      }
      piVar1 = (int *)((int)this + 4);
      piVar6 = piVar1;
      if (0xf < *(uint *)((int)this + 0x18)) {
        piVar6 = (undefined4 *)*piVar1;
      }
      puVar5 = (undefined4 *)(param_2 + iVar3);
      for (uVar2 = uVar4 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *piVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        piVar6 = piVar6 + 1;
      }
      for (uVar2 = uVar4 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)piVar6 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        piVar6 = (undefined4 *)((int)piVar6 + 1);
      }
      *(uint *)((int)this + 0x14) = uVar4;
      if (0xf < *(uint *)((int)this + 0x18)) {
        piVar1 = (int *)*piVar1;
      }
      *(undefined1 *)((int)piVar1 + uVar4) = 0;
    }
    return this;
  }
  FUN_00438510(this,uVar4 + param_2,0xffffffff);
  FUN_00438510(this,0,param_2);
  return this;
}

