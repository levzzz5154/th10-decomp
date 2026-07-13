/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00427C70
 * Tracking name: FUN_00427c70
 * Ghidra name: FUN_00427c70
 * Tracked span: 272 bytes
 */


undefined4 __thiscall FUN_00427c70(void *this,int param_1)

{
  if ((*(int *)((int)this + 4) != *(int *)this) && (*(int *)((int)this + 4) % param_1 == 0)) {
    return 1;
  }
  return 0;
}

