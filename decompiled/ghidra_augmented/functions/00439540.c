/* Raw Ghidra reference; not compilable reconstruction. Address: 00439540 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00439540(void)

{
  double dVar1;
  DWORD DVar2;
  undefined8 local_14;
  LARGE_INTEGER local_c;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922ec);
  DAT_00492321 = DAT_00492321 + '\x01';
  if (DAT_00492508 == 0 && DAT_0049250c == 0) {
    timeBeginPeriod(1);
    DVar2 = timeGetTime();
    dVar1 = (double)(int)DVar2;
    if ((int)DVar2 < 0) {
      dVar1 = dVar1 + _DAT_00470b30;
    }
    timeEndPeriod(1);
    if (dVar1 < _DAT_00492540) {
      _DAT_00492540 = dVar1;
    }
    dVar1 = (dVar1 - _DAT_00492540 * _DAT_00470b88) * _DAT_00470b28;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922ec);
    DAT_00492321 = DAT_00492321 + -1;
    return (float10)dVar1;
  }
  QueryPerformanceCounter(&local_c);
  local_14 = CONCAT44((local_c.s.HighPart - DAT_00492514) - (uint)(local_c.s.LowPart < DAT_00492510)
                      ,local_c.s.LowPart - DAT_00492510);
  dVar1 = (double)local_14 / (double)CONCAT44(DAT_0049250c,DAT_00492508);
  if (dVar1 < _DAT_00492540) {
    _DAT_00492540 = dVar1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922ec);
  DAT_00492321 = DAT_00492321 + -1;
  return (float10)dVar1 - (float10)_DAT_00492540;
}

