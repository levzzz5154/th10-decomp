/* Raw Ghidra reference; not compilable reconstruction. Address: 00453FDD */

/* Library Function - Single Match
    ___sbh_alloc_new_region
   
   Library: Visual Studio 2003 Release */

undefined4 * ___sbh_alloc_new_region(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  if (DAT_00499328 == DAT_00499338) {
    pvVar2 = HeapReAlloc(DAT_00499340,0,DAT_0049932c,(DAT_00499338 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_00499338 = DAT_00499338 + 0x10;
    DAT_0049932c = pvVar2;
  }
  puVar1 = (undefined4 *)((int)DAT_0049932c + DAT_00499328 * 0x14);
  pvVar2 = HeapAlloc(DAT_00499340,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_00499328 = DAT_00499328 + 1;
      *(undefined4 *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(DAT_00499340,0,(LPVOID)puVar1[4]);
  }
  return (undefined4 *)0x0;
}

