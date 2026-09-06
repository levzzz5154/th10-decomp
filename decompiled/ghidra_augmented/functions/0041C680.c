/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C680 */

void __fastcall FUN_0041c680(undefined4 param_1)

{
  int iVar1;
  undefined4 *unaff_EBX;
  undefined4 *puVar2;
  
  FUN_0041c030(param_1,unaff_EBX);
  *unaff_EBX = &PTR_LAB_0046da10;
  puVar2 = unaff_EBX + 0x109;
  for (iVar1 = 0x7e; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_EBX[0x114] = 0x41000000;
  unaff_EBX[0x1a2] = unaff_EBX[0x1a2] & 0xfffffffe;
  unaff_EBX[0x1b3] = unaff_EBX[0x1b3] & 0xfffffffe;
  unaff_EBX[0x1c6] = unaff_EBX[0x1c6] & 0xfffffffe;
  unaff_EBX[0x1d1] = unaff_EBX[0x1d1] & 0xfffffffe;
  unaff_EBX[0x1e4] = unaff_EBX[0x1e4] & 0xfffffffe;
  unaff_EBX[499] = unaff_EBX[499] & 0xfffffffe;
  unaff_EBX[0x206] = unaff_EBX[0x206] & 0xfffffffe;
  unaff_EBX[0x211] = unaff_EBX[0x211] & 0xfffffffe;
  unaff_EBX[0x265] = unaff_EBX[0x265] & 0xfffffffe;
  puVar2 = unaff_EBX + 0x187;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_EBX + 0x268) = 0xffff;
  unaff_EBX[0x28d] = unaff_EBX[0x28d] & 0xfffffffe;
  unaff_EBX[0x29e] = unaff_EBX[0x29e] & 0xfffffffe;
  unaff_EBX[0x2b1] = unaff_EBX[0x2b1] & 0xfffffffe;
  unaff_EBX[700] = unaff_EBX[700] & 0xfffffffe;
  unaff_EBX[0x2cf] = unaff_EBX[0x2cf] & 0xfffffffe;
  unaff_EBX[0x2de] = unaff_EBX[0x2de] & 0xfffffffe;
  unaff_EBX[0x2f1] = unaff_EBX[0x2f1] & 0xfffffffe;
  unaff_EBX[0x2fc] = unaff_EBX[0x2fc] & 0xfffffffe;
  unaff_EBX[0x350] = unaff_EBX[0x350] & 0xfffffffe;
  puVar2 = unaff_EBX + 0x272;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(unaff_EBX + 0x353) = 0xffff;
  return;
}

