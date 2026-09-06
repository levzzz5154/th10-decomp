/* Raw Ghidra reference; not compilable reconstruction. Address: 0040B250 */

undefined4 __fastcall FUN_0040b250(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = operator_new(0x2c);
  *(undefined4 **)(param_1 + 0x358) = puVar1;
  puVar3 = puVar1;
  for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_2;
    param_2 = param_2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(param_1 + 0x340) = *puVar1;
  *(undefined4 *)(param_1 + 0x344) = puVar1[1];
  *(undefined4 *)(param_1 + 0x348) = puVar1[2];
  return 0;
}

