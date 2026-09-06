/* Raw Ghidra reference; not compilable reconstruction. Address: 004364F0 */

undefined4 __thiscall FUN_004364f0(void *this,uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = param_1;
  if (param_2 == 0) {
    if ((-1 < (int)param_1) && (param_1 < *(uint *)((int)this + 4))) {
      *(uint *)((int)this + 8) = *(int *)((int)this + 0xc) + param_1;
      return CONCAT31((int3)(param_1 >> 8),1);
    }
  }
  else if (param_2 == 1) {
    uVar1 = *(uint *)((int)this + 8);
    if ((int)param_1 < (int)((*(int *)((int)this + 0xc) + *(int *)((int)this + 4)) - uVar1)) {
LAB_0043651a:
      *(uint *)((int)this + 8) = uVar1 + param_1;
      return CONCAT31((int3)(uVar1 + param_1 >> 8),1);
    }
  }
  else {
    uVar1 = param_2 - 2;
    if (uVar1 == 0) {
      if ((int)param_1 < 1) {
        uVar1 = param_1;
        if ((int)param_1 < 0) {
          uVar1 = -param_1;
        }
        if (uVar1 < *(uint *)((int)this + 4)) {
          uVar1 = *(int *)((int)this + 0xc) + *(uint *)((int)this + 4);
          goto LAB_0043651a;
        }
      }
    }
  }
  return uVar1 & 0xffffff00;
}

