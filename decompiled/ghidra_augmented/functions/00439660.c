/* Raw Ghidra reference; not compilable reconstruction. Address: 00439660 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00439660(void)

{
  DWORD DVar1;
  float10 fVar2;
  LARGE_INTEGER local_8;
  
  if (DAT_00492508 == 0 && DAT_0049250c == 0) {
    timeBeginPeriod(1);
    DVar1 = timeGetTime();
    local_8.QuadPart = (LONGLONG)(int)DVar1;
    if ((int)DVar1 < 0) {
      local_8.QuadPart = local_8.QuadPart + _DAT_00470b30;
    }
    timeEndPeriod(1);
    fVar2 = (float10)local_8.QuadPart * (float10)_DAT_00470b28;
  }
  else {
    QueryPerformanceCounter(&local_8);
    local_8.s.HighPart =
         (local_8.s.HighPart - DAT_00492514) - (uint)(local_8.s.LowPart < DAT_00492510);
    local_8.s.LowPart = local_8.s.LowPart - DAT_00492510;
    fVar2 = (float10)(longlong)local_8 / (float10)CONCAT44(DAT_0049250c,DAT_00492508);
  }
  if (fVar2 < (float10)_DAT_00492540) {
    _DAT_00492540 = (double)fVar2;
  }
  return fVar2 - (float10)_DAT_00492540;
}

