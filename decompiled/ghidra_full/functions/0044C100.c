/* Raw Ghidra reference; not compilable reconstruction. Address: 0044C100 */

undefined4 * __thiscall FUN_0044c100(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004703e4;
  FUN_0044c150();
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

