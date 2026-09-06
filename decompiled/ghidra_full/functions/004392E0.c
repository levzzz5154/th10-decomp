/* Raw Ghidra reference; not compilable reconstruction. Address: 004392E0 */

void FUN_004392e0(void)

{
  SystemParametersInfoA(0x10,0,&DAT_0049251c,0);
  SystemParametersInfoA(0x53,0,&DAT_00492520,0);
  SystemParametersInfoA(0x54,0,&DAT_00492524,0);
  SystemParametersInfoA(0x11,0,(PVOID)0x0,2);
  SystemParametersInfoA(0x55,0,(PVOID)0x0,2);
  SystemParametersInfoA(0x56,0,(PVOID)0x0,2);
  QueryPerformanceFrequency((LARGE_INTEGER *)&DAT_00492508);
  QueryPerformanceCounter((LARGE_INTEGER *)&DAT_00492510);
  return;
}

