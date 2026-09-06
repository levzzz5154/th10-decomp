/* Raw Ghidra reference; not compilable reconstruction. Address: 0045650F */

void __cdecl __freeptd(void *param_1)

{
  if (DAT_00473390 != -1) {
    if (param_1 == (void *)0x0) {
      param_1 = (void *)(*DAT_00477378)(DAT_00473390);
    }
    __freefls_4(param_1);
    (*DAT_0047737c)(DAT_00473390,0);
  }
  return;
}

