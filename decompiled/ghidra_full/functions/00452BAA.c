/* Raw Ghidra reference; not compilable reconstruction. Address: 00452BAA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _localtime
   
   Library: Visual Studio 2003 Release */

tm * __cdecl _localtime(time_t *_Time)

{
  time_t *_Time_00;
  tm *_Time_01;
  int iVar1;
  
  _Time_00 = _Time;
  if ((int)*_Time < 0) {
    _Time_01 = (tm *)0x0;
  }
  else {
    ___tzset();
    iVar1 = (int)*_Time_00;
    if ((iVar1 < 0x3f481) || (0x7ffc0b7e < iVar1)) {
      _Time_01 = _gmtime(_Time_00);
      if ((DAT_00473524 == 0) || (iVar1 = __isindst(_Time_01), iVar1 == 0)) {
        _Time = (time_t *)(_Time_01->tm_sec - _DAT_00473520);
      }
      else {
        _Time = (time_t *)((_Time_01->tm_sec - DAT_00473528) - _DAT_00473520);
        _Time_01->tm_isdst = 1;
      }
      iVar1 = (int)_Time % 0x3c;
      _Time_01->tm_sec = iVar1;
      if (iVar1 < 0) {
        _Time_01->tm_sec = iVar1 + 0x3c;
        _Time = (time_t *)((int)_Time + -0x3c);
      }
      _Time = (time_t *)((int)_Time / 0x3c + _Time_01->tm_min);
      iVar1 = (int)_Time % 0x3c;
      _Time_01->tm_min = iVar1;
      if (iVar1 < 0) {
        _Time_01->tm_min = iVar1 + 0x3c;
        _Time = (time_t *)((int)_Time + -0x3c);
      }
      _Time = (time_t *)((int)_Time / 0x3c + _Time_01->tm_hour);
      iVar1 = (int)_Time % 0x18;
      _Time_01->tm_hour = iVar1;
      if (iVar1 < 0) {
        _Time_01->tm_hour = iVar1 + 0x18;
        _Time = _Time + -3;
      }
      iVar1 = (int)_Time / 0x18;
      if (iVar1 < 1) {
        if (-1 < iVar1) {
          return _Time_01;
        }
        _Time_01->tm_wday = (_Time_01->tm_wday + 7 + iVar1) % 7;
        _Time_01->tm_mday = _Time_01->tm_mday + iVar1;
        if (_Time_01->tm_mday < 1) {
          _Time_01->tm_year = _Time_01->tm_year + -1;
          _Time_01->tm_mday = _Time_01->tm_mday + 0x1f;
          _Time_01->tm_yday = 0x16c;
          _Time_01->tm_mon = 0xb;
          return _Time_01;
        }
      }
      else {
        _Time_01->tm_wday = (_Time_01->tm_wday + iVar1) % 7;
        _Time_01->tm_mday = _Time_01->tm_mday + iVar1;
      }
      _Time_01->tm_yday = _Time_01->tm_yday + iVar1;
    }
    else {
      _Time = (time_t *)(iVar1 - _DAT_00473520);
      _Time_01 = _gmtime((time_t *)&_Time);
      if ((DAT_00473524 != 0) && (iVar1 = __isindst(_Time_01), iVar1 != 0)) {
        _Time = (time_t *)((int)_Time - DAT_00473528);
        _Time_01 = _gmtime((time_t *)&_Time);
        _Time_01->tm_isdst = 1;
      }
    }
  }
  return _Time_01;
}

