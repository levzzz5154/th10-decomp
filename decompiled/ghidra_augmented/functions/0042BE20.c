/* Raw Ghidra reference; not compilable reconstruction. Address: 0042BE20 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_0042be20(void)

{
  byte *pbVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  undefined4 *puVar5;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_108;
  _sprintf(local_108,"%s",
           *(undefined4 *)(*(int *)(unaff_ESI + 0x34) + *(int *)(unaff_ESI + 0x114) * 4));
  iVar4 = 0;
  if (*(int **)(unaff_ESI + 0x2dc) != (int *)0x0) {
    (**(code **)(**(int **)(unaff_ESI + 0x2dc) + 0x14))(1);
    *(undefined4 *)(unaff_ESI + 0x2dc) = 0;
  }
  *(undefined4 *)(unaff_ESI + 0x2dc) = 0;
  if (*(void **)(unaff_ESI + 0x2e0) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x2e0));
    *(undefined4 *)(unaff_ESI + 0x2e0) = 0;
  }
  pbVar1 = FUN_0044b360((size_t *)0x0,0);
  *(byte **)(unaff_ESI + 0x2e0) = pbVar1;
  puVar2 = operator_new(0x1098);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    *puVar2 = &PTR_FUN_0046d0f0;
    puVar2[0x424] = 0;
    puVar2[0x425] = 0;
    puVar5 = puVar2;
    for (iVar3 = 0x426; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  *(undefined4 **)(unaff_ESI + 0x2d8) = puVar2;
  (**(code **)*puVar2)(*(undefined4 *)(unaff_ESI + 0x2e0));
  iVar3 = *(int *)(*(int *)(unaff_ESI + 0x2d8) + 8);
  *(int *)(unaff_ESI + 500) = iVar3;
  if ((iVar3 != 0) && (iVar3 < 1)) {
    iVar4 = iVar3 + -1;
  }
  *(int *)(unaff_ESI + 0x1ec) = iVar4;
  *(undefined4 *)(unaff_ESI + 0x30) = 1;
  return 0;
}

