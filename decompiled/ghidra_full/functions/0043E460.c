/* Raw Ghidra reference; not compilable reconstruction. Address: 0043E460 */

void __fastcall FUN_0043e460(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar2 = 0;
  piVar3 = (int *)(in_EAX + 0x1f88);
  do {
    if (*piVar3 == 0) {
      iVar2 = iVar2 * 0x10c + in_EAX;
      *(undefined4 *)(iVar2 + 0x1f88) = param_3;
      *(undefined4 *)(iVar2 + 0x1f8c) = param_4;
      iVar4 = (iVar2 + 0x1f94) - (int)param_2;
      do {
        cVar1 = *param_2;
        param_2[iVar4] = cVar1;
        param_2 = param_2 + 1;
      } while (cVar1 != '\0');
      *(undefined4 *)(iVar2 + 0x1f90) = 0;
      return;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0x43;
  } while (iVar2 < 0x1f);
  return;
}

