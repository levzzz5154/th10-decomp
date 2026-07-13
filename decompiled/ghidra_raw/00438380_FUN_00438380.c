/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00438380
 * Tracking name: FUN_00438380
 * Ghidra name: FUN_00438380
 * Tracked span: 160 bytes
 */


void __thiscall FUN_00438380(void *this,char param_1,uint param_2)

{
  undefined4 *_Memory;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if ((param_1 != '\0') && (0xf < *(uint *)((int)this + 0x18))) {
    _Memory = *(undefined4 **)((int)this + 4);
    if (param_2 != 0) {
      puVar2 = _Memory;
      puVar3 = this;
      for (uVar1 = param_2 >> 2; puVar3 = puVar3 + 1, uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
      }
      for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
        puVar2 = (undefined4 *)((int)puVar2 + 1);
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
    _free(_Memory);
  }
  *(uint *)((int)this + 0x14) = param_2;
  *(undefined4 *)((int)this + 0x18) = 0xf;
  *(undefined1 *)((int)this + param_2 + 4) = 0;
  return;
}

