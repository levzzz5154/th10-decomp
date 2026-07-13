/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044BEA0
 * Tracking name: FUN_0044bea0
 * Ghidra name: FUN_0044bea0
 * Tracked span: 160 bytes
 */


int FUN_0044bea0(int param_1)

{
  int iVar1;
  int *in_EAX;
  int iVar2;
  int *piVar3;
  
  iVar1 = in_EAX[2];
  if (0 < iVar1) {
    do {
      iVar2 = *in_EAX;
      *in_EAX = iVar2 + param_1;
      if (iVar1 <= iVar2 + param_1) {
        do {
          if (in_EAX[0x34] == 0) {
            iVar2 = iVar1 + -1;
          }
          else {
            iVar2 = *in_EAX - iVar1;
          }
          *in_EAX = iVar2;
        } while (in_EAX[2] <= iVar2);
      }
      if (*in_EAX < 0) {
        do {
          if (in_EAX[0x34] == 0) {
            *in_EAX = 0;
          }
          else {
            *in_EAX = *in_EAX + iVar1;
          }
        } while (*in_EAX < 0);
      }
      iVar2 = 0;
      piVar3 = in_EAX + 0x24;
      while( true ) {
        if (in_EAX[0x35] <= iVar2) goto LAB_0044bf1a;
        if (*piVar3 == *in_EAX) break;
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
      }
    } while( true );
  }
LAB_0044bf1a:
  return *in_EAX;
}

