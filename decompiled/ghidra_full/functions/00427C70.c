/* Raw Ghidra reference; not compilable reconstruction. Address: 00427C70 */

undefined4 __thiscall FUN_00427c70(void *this,int param_1)

{
  if ((*(int *)((int)this + 4) != *(int *)this) && (*(int *)((int)this + 4) % param_1 == 0)) {
    return 1;
  }
  return 0;
}

