/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044CE80
 * Tracking name: FUN_0044ce80
 * Ghidra name: FUN_0044ce80
 * Tracked span: 128 bytes
 */


void FUN_0044ce80(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int in_EAX;
  void *pvVar2;
  uint uVar3;
  undefined4 *unaff_ESI;
  uint unaff_EDI;
  
  *unaff_ESI = &PTR_FUN_004705d8;
  pvVar2 = operator_new(unaff_EDI * 4);
  unaff_ESI[1] = pvVar2;
  uVar3 = 0;
  if (unaff_EDI != 0) {
    do {
      *(undefined4 *)(unaff_ESI[1] + uVar3 * 4) = *(undefined4 *)(in_EAX + uVar3 * 4);
      uVar3 = uVar3 + 1;
    } while (uVar3 < unaff_EDI);
  }
  unaff_ESI[2] = param_1;
  unaff_ESI[4] = unaff_EDI;
  unaff_ESI[3] = param_2;
  FUN_0044d110(*(int **)unaff_ESI[1]);
  uVar3 = 0;
  if (unaff_EDI != 0) {
    do {
      piVar1 = *(int **)(unaff_ESI[1] + uVar3 * 4);
      (**(code **)(*piVar1 + 0x34))(piVar1,0);
      uVar3 = uVar3 + 1;
    } while (uVar3 < unaff_EDI);
  }
  unaff_ESI[0xc] = 0;
  return;
}

