/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00449AE0
 * Tracking name: FUN_00449ae0
 * Ghidra name: FUN_00449ae0
 * Tracked span: 144 bytes
 */


undefined4 FUN_00449ae0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *unaff_ESI;
  int unaff_EDI;
  
  uVar4 = 0;
  if ((code *)unaff_ESI[3] != (code *)0x0) {
    uVar4 = (*(code *)unaff_ESI[3])();
    unaff_ESI[3] = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
  DAT_0049231c = DAT_0049231c + '\x01';
  *unaff_ESI = unaff_EDI;
  iVar1 = *(int *)(param_1 + 0x18);
  puVar3 = (undefined4 *)(param_1 + 0x14);
  while ((iVar1 != 0 && (puVar2 = (undefined4 *)puVar3[1], *(int *)*puVar2 < unaff_EDI))) {
    iVar1 = puVar2[1];
    puVar3 = puVar2;
  }
  if (puVar3[1] != 0) {
    unaff_ESI[6] = puVar3[1];
    *(int **)(puVar3[1] + 8) = unaff_ESI + 5;
  }
  puVar3[1] = unaff_ESI + 5;
  unaff_ESI[7] = (int)puVar3;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
  DAT_0049231c = DAT_0049231c + -1;
  return uVar4;
}

