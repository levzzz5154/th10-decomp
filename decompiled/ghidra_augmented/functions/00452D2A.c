/* Raw Ghidra reference; not compilable reconstruction. Address: 00452D2A */

/* Library Function - Single Match
    __onexit_lk
   
   Library: Visual Studio 2003 Release */

void __onexit_lk(void)

{
  size_t sVar1;
  int *piVar2;
  size_t sVar3;
  int unaff_EDI;
  
  sVar1 = __msize(DAT_00499310);
  if (sVar1 < (uint)((int)DAT_0049930c + (4 - (int)DAT_00499310))) {
    sVar3 = 0x800;
    if (sVar1 < 0x800) {
      sVar3 = sVar1;
    }
    piVar2 = FUN_00457395(DAT_00499310,(uint *)(sVar3 + sVar1));
    if (piVar2 == (int *)0x0) {
      piVar2 = FUN_00457395(DAT_00499310,(uint *)(sVar1 + 0x10));
      if (piVar2 == (int *)0x0) {
        return;
      }
    }
    DAT_0049930c = piVar2 + ((int)DAT_0049930c - (int)DAT_00499310 >> 2);
    DAT_00499310 = piVar2;
  }
  *DAT_0049930c = unaff_EDI;
  DAT_0049930c = DAT_0049930c + 1;
  return;
}

