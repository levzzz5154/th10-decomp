/* Raw Ghidra reference; not compilable reconstruction. Address: 00449950 */

undefined4 * FUN_00449950(void)

{
  uint uVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int unaff_ESI;
  undefined4 *puVar2;
  
  uVar1 = *(uint *)(unaff_ESI + 0x3ad068);
  if (*(char *)(uVar1 + 0x3ac068 + unaff_ESI) != '\0') {
    uVar1 = uVar1 + 1 & 0x80000fff;
    if ((int)uVar1 < 0) {
      uVar1 = (uVar1 - 1 | 0xfffff000) + 1;
    }
    *(uint *)(unaff_ESI + 0x3ad068) = uVar1;
    if (*(char *)(uVar1 + 0x3ac068 + unaff_ESI) != '\0') {
      puVar2 = operator_new(0x3ac);
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
        InitializeEntity(extraout_ECX,(undefined4 *)0x0);
      }
      else {
        puVar2 = ConstructEntity(puVar2);
        InitializeEntity(extraout_ECX_00,puVar2);
      }
      goto LAB_004499d2;
    }
  }
  puVar2 = (undefined4 *)(uVar1 * 0x3ac + 0x68 + unaff_ESI);
  *(undefined1 *)(uVar1 + 0x3ac068 + unaff_ESI) = 1;
LAB_004499d2:
  uVar1 = *(int *)(unaff_ESI + 0x3ad068) + 1U & 0x80000fff;
  if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffff000) + 1;
  }
  *(uint *)(unaff_ESI + 0x3ad068) = uVar1;
  return puVar2;
}

