/* Raw Ghidra reference; not compilable reconstruction. Address: 00420EA0 */

undefined4 FUN_00420ea0(_StartAddress *param_1,void *param_2)

{
  uintptr_t uVar1;
  int unaff_EDI;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(unaff_EDI + 0x6dc));
  *(char *)(unaff_EDI + 0x6fa) = *(char *)(unaff_EDI + 0x6fa) + '\x01';
  FUN_0044c150();
  *(_StartAddress **)(unaff_EDI + 0x644) = param_1;
  *(undefined4 *)(unaff_EDI + 0x63c) = 1;
  *(undefined4 *)(unaff_EDI + 0x638) = 0;
  uVar1 = __beginthreadex((void *)0x0,0,param_1,param_2,0,(uint *)(unaff_EDI + 0x634));
  *(uintptr_t *)(unaff_EDI + 0x630) = uVar1;
  LeaveCriticalSection((LPCRITICAL_SECTION)(unaff_EDI + 0x6dc));
  *(char *)(unaff_EDI + 0x6fa) = *(char *)(unaff_EDI + 0x6fa) + -1;
  return 0;
}

