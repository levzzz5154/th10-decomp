/* Raw Ghidra reference; not compilable reconstruction. Address: 00434C30 */

undefined4 __fastcall FUN_00434c30(int param_1)

{
  undefined4 in_EAX;
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  FUN_00434d10();
  puVar1 = operator_new(0xc);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = &PTR_FUN_0046f230;
    puVar1[1] = 0xffffffff;
    puVar1[2] = 0;
  }
  *(undefined4 **)(param_1 + 0xc) = puVar1;
  uVar4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = FUN_00434f70(in_EAX);
    if ((char)uVar2 != '\0') {
      iVar3 = FUN_00435220();
      *(int *)(param_1 + 8) = iVar3;
      if (iVar3 != 0) {
        uVar2 = (**(code **)**(undefined4 **)(param_1 + 0xc))(iVar3,PTR_DAT_00474908);
        return CONCAT31((int3)((uint)uVar2 >> 8),1);
      }
    }
    uVar4 = FUN_00434d10();
  }
  return uVar4 & 0xffffff00;
}

