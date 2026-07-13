/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00438590
 * Tracking name: FUN_00438590
 * Ghidra name: FUN_00438590
 * Tracked span: 288 bytes
 */


void __thiscall FUN_00438590(void *this,int param_1)

{
  *(int *)((int)this + 0x14) = param_1;
  if (0xf < *(uint *)((int)this + 0x18)) {
    *(undefined1 *)(*(int *)((int)this + 4) + param_1) = 0;
    return;
  }
  *(undefined1 *)((int)this + param_1 + 4) = 0;
  return;
}

