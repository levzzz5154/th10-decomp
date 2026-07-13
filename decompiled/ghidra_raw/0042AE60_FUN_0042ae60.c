/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042AE60
 * Tracking name: FUN_0042ae60
 * Ghidra name: FUN_0042ae60
 * Tracked span: 192 bytes
 */


void FUN_0042ae60(void)

{
  undefined4 *in_EAX;
  byte *pbVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 *puVar3;
  size_t local_4;
  
  puVar3 = in_EAX;
  for (iVar2 = 0x772d; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  pbVar1 = FUN_0044b360(&local_4,1);
  *in_EAX = pbVar1;
  FUN_0042add0(extraout_ECX,in_EAX + 0x761b);
  puVar3 = in_EAX + 2;
  for (iVar2 = (int)puVar3 + (-8 - (int)in_EAX); (uint)(iVar2 / 0x437c) < 7; iVar2 = iVar2 + 0x437c)
  {
    FUN_0042acb0(puVar3);
    puVar3 = puVar3 + 0x10df;
  }
  FUN_0042b030();
  return;
}

