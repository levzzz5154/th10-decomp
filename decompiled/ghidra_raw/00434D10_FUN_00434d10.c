/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00434D10
 * Tracking name: FUN_00434d10
 * Ghidra name: FUN_00434d10
 * Tracked span: 192 bytes
 */


void FUN_00434d10(void)

{
  void *pvVar1;
  undefined4 *unaff_ESI;
  
  if ((void *)unaff_ESI[2] != (void *)0x0) {
    _free((void *)unaff_ESI[2]);
    unaff_ESI[2] = 0;
  }
  pvVar1 = (void *)*unaff_ESI;
  unaff_ESI[2] = 0;
  if (pvVar1 != (void *)0x0) {
    _eh_vector_destructor_iterator_(pvVar1,0x10,*(int *)((int)pvVar1 + -4),FUN_00435250);
    _free((void *)((int)pvVar1 + -4));
  }
  *unaff_ESI = 0;
  if ((int *)unaff_ESI[3] != (int *)0x0) {
    (**(code **)(*(int *)unaff_ESI[3] + 0x1c))(1);
  }
  unaff_ESI[3] = 0;
  unaff_ESI[1] = 0;
  return;
}

