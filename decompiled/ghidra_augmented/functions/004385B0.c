/* Raw Ghidra reference; not compilable reconstruction. Address: 004385B0 */

bool __thiscall FUN_004385b0(void *this,uint param_1,char param_2)

{
  undefined4 *_Memory;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (param_1 == 0xffffffff) {
    FUN_004624e5();
  }
  uVar1 = *(uint *)((int)this + 0x18);
  if (param_1 <= uVar1) {
    if ((param_2 != '\0') && (param_1 < 0x10)) {
      uVar2 = *(uint *)((int)this + 0x14);
      if (param_1 < *(uint *)((int)this + 0x14)) {
        uVar2 = param_1;
      }
      if (0xf < uVar1) {
        _Memory = *(undefined4 **)((int)this + 4);
        if (uVar2 != 0) {
          puVar3 = _Memory;
          puVar4 = this;
          for (uVar1 = uVar2 >> 2; puVar4 = puVar4 + 1, uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
          }
          for (uVar1 = uVar2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
            puVar3 = (undefined4 *)((int)puVar3 + 1);
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
        }
        _free(_Memory);
      }
      *(uint *)((int)this + 0x14) = uVar2;
      *(undefined4 *)((int)this + 0x18) = 0xf;
      *(undefined1 *)(uVar2 + 4 + (int)this) = 0;
      return param_1 != 0;
    }
    if (param_1 == 0) {
      *(undefined4 *)((int)this + 0x14) = 0;
      if (0xf < uVar1) {
        **(undefined1 **)((int)this + 4) = 0;
        return false;
      }
      *(undefined1 *)((int)this + 4) = 0;
    }
    return param_1 != 0;
  }
  FUN_004386b0(this,param_1);
  return param_1 != 0;
}

