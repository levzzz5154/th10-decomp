/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00450160
 * Tracking name: FUN_00450160
 * Ghidra name: FUN_00450160
 * Tracked span: 48 bytes
 */


int * __fastcall FUN_00450160(int param_1)

{
  int in_EAX;
  int *piVar1;
  
  piVar1 = (int *)(in_EAX + 0x1030);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*(int *)(*piVar1 + 0x1010) == param_1) break;
    piVar1 = (int *)piVar1[1];
  }
  return piVar1;
}

