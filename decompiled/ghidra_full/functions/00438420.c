/* Raw Ghidra reference; not compilable reconstruction. Address: 00438420 */

void * __thiscall FUN_00438420(void *this,undefined4 *param_1,uint param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar4 = *(uint *)((int)this + 0x18);
  if (uVar4 < 0x10) {
    puVar1 = (undefined4 *)((int)this + 4);
  }
  else {
    puVar1 = *(undefined4 **)((int)this + 4);
  }
  if (puVar1 <= param_1) {
    puVar1 = (undefined4 *)((int)this + 4);
    puVar3 = puVar1;
    if (0xf < uVar4) {
      puVar3 = (undefined4 *)*puVar1;
    }
    if (param_1 < (undefined4 *)(*(int *)((int)this + 0x14) + (int)puVar3)) {
      if (0xf < uVar4) {
        puVar1 = (undefined4 *)*puVar1;
      }
      pvVar2 = FUN_00438260(this,this,(int)param_1 - (int)puVar1,param_2);
      return pvVar2;
    }
  }
  if (param_2 == 0xffffffff) {
    FUN_004624e5();
  }
  if (*(uint *)((int)this + 0x18) < param_2) {
    FUN_004386b0(this,param_2);
  }
  else if (param_2 == 0) {
    *(undefined4 *)((int)this + 0x14) = 0;
    if (*(uint *)((int)this + 0x18) < 0x10) {
      *(undefined1 *)((int)this + 4) = 0;
      return this;
    }
    **(undefined1 **)((int)this + 4) = 0;
    return this;
  }
  if (param_2 != 0) {
    if (*(uint *)((int)this + 0x18) < 0x10) {
      puVar1 = (undefined4 *)((int)this + 4);
    }
    else {
      puVar1 = *(undefined4 **)((int)this + 4);
    }
    for (uVar4 = param_2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar1 = *param_1;
      param_1 = param_1 + 1;
      puVar1 = puVar1 + 1;
    }
    for (uVar4 = param_2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar1 = *(undefined1 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
    *(uint *)((int)this + 0x14) = param_2;
    if (0xf < *(uint *)((int)this + 0x18)) {
      *(undefined1 *)(*(int *)((int)this + 4) + param_2) = 0;
      return this;
    }
    *(undefined1 *)((int)this + param_2 + 4) = 0;
  }
  return this;
}

