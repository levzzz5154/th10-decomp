/* Raw Ghidra reference; not compilable reconstruction. Address: 00420670 */

/* WARNING: Removing unreachable block (ram,0x00420859) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00420670(void)

{
  char cVar1;
  char *in_EAX;
  undefined4 *puVar2;
  void *pvVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 *puVar6;
  uint uVar7;
  int unaff_ESI;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  
  iVar5 = *(int *)(unaff_ESI + 0x50c);
  while (iVar5 != 0) {
    Sleep(10);
    iVar5 = *(int *)(unaff_ESI + 0x50c);
  }
  piVar10 = *(int **)(unaff_ESI + 8);
  iVar11 = 0;
  (**(code **)(*piVar10 + 0x48))(piVar10,0,0);
  *(undefined4 *)(unaff_ESI + 0x510) = 0;
  *(undefined4 *)(unaff_ESI + 0x514) = 0;
  *(undefined4 *)(unaff_ESI + 0x518) = 0;
  *(undefined2 *)(unaff_ESI + 0x51c) = 0;
  *(undefined2 *)(unaff_ESI + 0x510) = 0x4d42;
  iVar5 = unaff_ESI - (int)in_EAX;
  *(undefined4 *)(unaff_ESI + 0x51a) = 0x36;
  *(undefined4 *)(unaff_ESI + 0x512) = 0x36;
  do {
    cVar1 = *in_EAX;
    in_EAX[iVar5 + 0x528] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  if (*(int *)(unaff_ESI + 0xec) == 0x16) {
    puVar2 = _malloc(0x2c);
    *(undefined4 **)(unaff_ESI + 0x520) = puVar2;
    if (puVar2 != (undefined4 *)0x0) {
      for (iVar5 = 0xb; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      pvVar3 = _malloc(0xe1000);
      *(void **)(unaff_ESI + 0x524) = pvVar3;
      if (pvVar3 != (void *)0x0) {
        *(int *)(unaff_ESI + 0x512) = *(int *)(unaff_ESI + 0x512) + 0xe1000;
        *(undefined2 *)(*(int *)(unaff_ESI + 0x520) + 0xe) = 0x18;
        **(undefined4 **)(unaff_ESI + 0x520) = 0x28;
        *(undefined4 *)(*(int *)(unaff_ESI + 0x520) + 4) = 0x280;
        *(undefined4 *)(*(int *)(unaff_ESI + 0x520) + 8) = 0x1e0;
        *(undefined2 *)(*(int *)(unaff_ESI + 0x520) + 0xc) = 1;
        piVar9 = (int *)0x0;
        *(undefined4 *)(*(int *)(unaff_ESI + 0x520) + 0x10) = 0;
        (**(code **)(iRam00000000 + 0x34))(0,&stack0xffffffe4,0);
        uVar7 = 0x1df;
        iVar5 = 0;
        do {
          puVar6 = (undefined2 *)(*(int *)(unaff_ESI + 0x524) + iVar5);
          puVar4 = (undefined2 *)((int)piVar10 * uVar7 + iVar11);
          iVar8 = 0x280;
          do {
            *puVar6 = *puVar4;
            *(undefined1 *)(puVar6 + 1) = *(undefined1 *)(puVar4 + 1);
            puVar4 = puVar4 + 2;
            puVar6 = (undefined2 *)((int)puVar6 + 3);
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          uVar7 = uVar7 - 1;
          iVar5 = iVar5 + 0x780;
        } while (uVar7 < 0x80000000);
        (**(code **)(*piVar9 + 0x38))(piVar9);
        _DAT_00492134 = __beginthread((_StartAddress *)"QUhP!I",0,(void *)0x0);
        return 0;
      }
    }
    FUN_0044b810(&DAT_00474f70,&DAT_0046def0);
  }
  else {
    if (*(int *)(unaff_ESI + 0xec) != 0x17) {
      FUN_0044b810(&DAT_00474f70,"error ? .\\src\\game\\mother.cpp\r\n");
      return 1;
    }
    FUN_0044b810(&DAT_00474f70,&DAT_0046df38);
  }
  return 0;
}

