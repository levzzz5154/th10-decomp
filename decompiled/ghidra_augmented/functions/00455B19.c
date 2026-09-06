/* Raw Ghidra reference; not compilable reconstruction. Address: 00455B19 */

uint * FUN_00455b19(void)

{
  bool bVar1;
  int iVar2;
  uint *puVar3;
  undefined **ppuVar4;
  int iVar5;
  
  iVar5 = 1;
  bVar1 = true;
  if ((DAT_0047334c != (uint *)0x0) ||
     (DAT_0047334c = _malloc(0x351), puVar3 = DAT_0047334c, DAT_0047334c != (uint *)0x0)) {
    *(undefined1 *)DAT_0047334c = 0;
    __strcats(DAT_0047334c,3);
    iVar2 = 0xc;
    ppuVar4 = &PTR_DAT_00473358;
    do {
      FUN_0045bd90(DAT_0047334c,(uint *)&DAT_0046a9fc);
      iVar2 = _strcmp(*ppuVar4,*(char **)((int)&PTR_DAT_00473358 + iVar2));
      if (iVar2 != 0) {
        bVar1 = false;
      }
      iVar5 = iVar5 + 1;
      iVar2 = iVar5 * 0xc;
      ppuVar4 = (undefined **)(&DAT_0047334c + iVar5 * 3);
      __strcats(DAT_0047334c,3);
    } while (iVar5 < 5);
    puVar3 = DAT_0047334c;
    if (bVar1) {
      _free(DAT_0047334c);
      DAT_0047334c = (uint *)0x0;
      puVar3 = (uint *)PTR_DAT_00473364;
    }
  }
  return puVar3;
}

