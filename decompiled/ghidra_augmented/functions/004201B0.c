/* Raw Ghidra reference; not compilable reconstruction. Address: 004201B0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004201b0(void)

{
  DWORD local_4;
  
  FUN_00420100();
  DAT_00476f78 = 0x3f800000;
  DAT_004923a8 = 0xff000000;
  FUN_004216f0();
  _DAT_00491ff8 = timeGetTime();
  _DAT_004918a8 = (undefined2)_DAT_00491ff8;
  DAT_004918b0 = _DAT_004918a8;
  _DAT_004977ac = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_0043d080,&DAT_00492590,0,&local_4);
  FUN_00413350();
  FUN_0044c150();
  _DAT_00474dec = FUN_0043ba90;
  _DAT_00474de4 = 1;
  _DAT_00474de0 = 0;
  _DAT_00474dd8 = __beginthreadex((void *)0x0,0,FUN_0043ba90,&DAT_00491c28,0,(uint *)&DAT_00474ddc);
  FUN_004462f0();
  FUN_00437a00();
  return 0;
}

