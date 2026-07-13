/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00447280
 * Tracking name: FUN_00447280
 * Ghidra name: FUN_00447280
 * Tracked span: 96 bytes
 */


int * __fastcall FUN_00447280(int param_1,int param_2,char *param_3)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_2 + 0x3ad06c + param_1 * 4);
  if (piVar1 == (int *)0x0) {
    piVar1 = FUN_004470c0(param_2,param_1,param_3);
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    piVar1[0x49] = 1;
    do {
      if ((char)DAT_00491ff4 < '\0') {
        return piVar1;
      }
      Sleep(1);
    } while (piVar1[0x49] != 0);
  }
  return piVar1;
}

