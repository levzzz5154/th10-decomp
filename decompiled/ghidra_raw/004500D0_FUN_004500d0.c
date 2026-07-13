/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004500D0
 * Tracking name: FUN_004500d0
 * Ghidra name: FUN_004500d0
 * Tracked span: 144 bytes
 */


void FUN_004500d0(undefined4 param_1,float *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int unaff_EDI;
  
  puVar1 = operator_new(0x1024);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[0x402] = 0;
    puVar1[0x403] = 0;
  }
  puVar2 = operator_new(0xc);
  puVar1[0x404] = param_1;
  puVar1[0x405] = unaff_EDI;
  *puVar1 = 0;
  puVar1[1] = 0;
  *(undefined1 *)(puVar1 + 0x407) = *(undefined1 *)(*(int *)(unaff_EDI + 4) + 0x101c);
  *puVar2 = puVar1;
  puVar2[1] = 0;
  puVar2[2] = 0;
  if (*(int *)(unaff_EDI + 0x1034) != 0) {
    puVar2[1] = *(int *)(unaff_EDI + 0x1034);
    *(undefined4 **)(*(int *)(unaff_EDI + 0x1034) + 8) = puVar2;
  }
  *(undefined4 **)(unaff_EDI + 0x1034) = puVar2;
  puVar2[2] = unaff_EDI + 0x1030;
  FUN_0044df70(*(undefined4 **)(unaff_EDI + 4),param_2);
  return;
}

