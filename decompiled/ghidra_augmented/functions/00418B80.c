/* Raw Ghidra reference; not compilable reconstruction. Address: 00418B80 */

void __thiscall FUN_00418b80(void *this,int param_1)

{
  *(int *)((int)this + 0xc) = param_1 / 10;
  if ((*(uint *)((int)this + 0x24) & 1) == 0) {
    *(undefined4 *)((int)this + 0x18) = 0;
    *(undefined4 *)((int)this + 0x14) = 0xfff0bdc1;
    *(undefined4 *)((int)this + 0x1c) = 0;
    *(undefined4 **)((int)this + 0x20) = &DAT_00476f78;
    *(uint *)((int)this + 0x24) = *(uint *)((int)this + 0x24) | 1;
  }
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x14) = 0xffffffff;
  return;
}

