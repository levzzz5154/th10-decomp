/* Raw Ghidra reference; not compilable reconstruction. Address: 00438800 */

uint __thiscall FUN_00438800(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)((int)this + 4);
  puVar2 = puVar1;
  if (0xf < *(uint *)((int)this + 0x18)) {
    puVar2 = (undefined4 *)*puVar1;
  }
  if (puVar2 <= param_1) {
    if (0xf < *(uint *)((int)this + 0x18)) {
      puVar1 = (undefined4 *)*puVar1;
    }
    if (param_1 < (undefined4 *)(*(int *)((int)this + 0x14) + (int)puVar1)) {
      return CONCAT31((int3)((uint)puVar1 >> 8),1);
    }
  }
  return (uint)puVar1 & 0xffffff00;
}

