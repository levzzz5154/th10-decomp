/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004392E0
 * Tracking name: FUN_004392e0
 * Ghidra name: FUN_004392e0
 * Tracked span: 176 bytes
 */


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

