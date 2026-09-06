/* Raw Ghidra reference; not compilable reconstruction. Address: 00404F30 */

void __thiscall FUN_00404f30(void *this,undefined2 *param_1)

{
  undefined2 in_AX;
  undefined4 *unaff_ESI;
  
  InitializeEntity(this,unaff_ESI);
  unaff_ESI[0xd0] = 0;
  unaff_ESI[0xd1] = 0;
  unaff_ESI[0xd2] = 0;
  unaff_ESI[0xcd] = 0;
  unaff_ESI[0xce] = 0;
  unaff_ESI[0xcf] = 0;
  unaff_ESI[0xd3] = 0;
  unaff_ESI[0xd4] = 0;
  unaff_ESI[0xd5] = 0;
  *(undefined1 *)((int)unaff_ESI + 0x3a1) = 0x10;
  *(undefined1 *)(unaff_ESI + 0xe8) = 0x10;
  *(undefined2 *)((int)unaff_ESI + 0x38a) = in_AX;
  FUN_0043e710(param_1);
  return;
}

