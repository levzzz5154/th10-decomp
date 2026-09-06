/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C5B0 */

void __fastcall FUN_0041c5b0(undefined4 param_1)

{
  int iVar1;
  undefined4 *unaff_EBX;
  undefined4 *puVar2;
  
  FUN_0041c030(param_1,unaff_EBX);
  *unaff_EBX = &PTR_LAB_0046da60;
  puVar2 = unaff_EBX + 0x109;
  for (iVar1 = 0x77; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_EBX[0x19b] = unaff_EBX[0x19b] & 0xfffffffe;
  unaff_EBX[0x1ac] = unaff_EBX[0x1ac] & 0xfffffffe;
  unaff_EBX[0x1bf] = unaff_EBX[0x1bf] & 0xfffffffe;
  unaff_EBX[0x1ca] = unaff_EBX[0x1ca] & 0xfffffffe;
  unaff_EBX[0x1dd] = unaff_EBX[0x1dd] & 0xfffffffe;
  unaff_EBX[0x1ec] = unaff_EBX[0x1ec] & 0xfffffffe;
  unaff_EBX[0x1ff] = unaff_EBX[0x1ff] & 0xfffffffe;
  unaff_EBX[0x20a] = unaff_EBX[0x20a] & 0xfffffffe;
  unaff_EBX[0x25e] = unaff_EBX[0x25e] & 0xfffffffe;
  puVar2 = unaff_EBX + 0x180;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_EBX + 0x261) = 0xffff;
  unaff_EBX[0x286] = unaff_EBX[0x286] & 0xfffffffe;
  unaff_EBX[0x297] = unaff_EBX[0x297] & 0xfffffffe;
  unaff_EBX[0x2aa] = unaff_EBX[0x2aa] & 0xfffffffe;
  unaff_EBX[0x2b5] = unaff_EBX[0x2b5] & 0xfffffffe;
  unaff_EBX[0x2c8] = unaff_EBX[0x2c8] & 0xfffffffe;
  unaff_EBX[0x2d7] = unaff_EBX[0x2d7] & 0xfffffffe;
  unaff_EBX[0x2ea] = unaff_EBX[0x2ea] & 0xfffffffe;
  unaff_EBX[0x2f5] = unaff_EBX[0x2f5] & 0xfffffffe;
  unaff_EBX[0x349] = unaff_EBX[0x349] & 0xfffffffe;
  puVar2 = unaff_EBX + 0x26b;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_EBX + 0x34c) = 0xffff;
  return;
}

