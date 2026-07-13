/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00438723
 * Tracking name: Catch@00438723
 * Ghidra name: Catch@00438723
 * Tracked span: 41 bytes
 */


undefined * Catch_00438723(void)

{
  void *pvVar1;
  int unaff_EBP;
  
  *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + 8);
  *(BADSPACEBASE **)(unaff_EBP + -0x10) = register0x00000010;
  *(undefined1 *)(unaff_EBP + -4) = 2;
  pvVar1 = operator_new(*(int *)(unaff_EBP + 8) + 1);
  *(void **)(unaff_EBP + 8) = pvVar1;
  return &DAT_00438743;
}

