/* Raw Ghidra reference; not compilable reconstruction. Address: 004497D0 */

void __fastcall FUN_004497d0(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int unaff_EBX;
  int *unaff_ESI;
  undefined4 *unaff_EDI;
  
  iVar1 = FUN_004491c0(param_1,(int)g_pGameStateManager,*unaff_ESI);
  if (iVar1 == 0) {
    *unaff_ESI = 0;
  }
  piVar2 = (int *)(iVar1 + 0x10);
  while( true ) {
    if (piVar2 == (int *)0x0) {
      *unaff_EDI = 0;
      return;
    }
    if (*(short *)(*piVar2 + 0x38a) == unaff_EBX) break;
    piVar2 = (int *)piVar2[1];
  }
  *unaff_EDI = *(undefined4 *)*piVar2;
  return;
}

