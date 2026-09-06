/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E204 */

/* Library Function - Multiple Matches With Different Base Names
    __ungetc_lk
    _ungetc
   
   Library: Visual Studio 2003 Release */

int __cdecl FID_conflict__ungetc(int _Ch,FILE *_File)

{
  uint uVar1;
  char *pcVar2;
  
  if (_Ch != -1) {
    uVar1 = _File->_flag;
    if (((uVar1 & 1) != 0) || (((char)uVar1 < '\0' && ((uVar1 & 2) == 0)))) {
      if (_File->_base == (char *)0x0) {
        __getbuf(_File);
      }
      if (_File->_ptr == _File->_base) {
        if (_File->_cnt != 0) {
          return -1;
        }
        _File->_ptr = _File->_ptr + 1;
      }
      _File->_ptr = _File->_ptr + -1;
      pcVar2 = _File->_ptr;
      if ((_File->_flag & 0x40) == 0) {
        *pcVar2 = (char)_Ch;
      }
      else if (*pcVar2 != (char)_Ch) {
        _File->_ptr = pcVar2 + 1;
        return -1;
      }
      _File->_cnt = _File->_cnt + 1;
      _File->_flag = _File->_flag & 0xffffffefU | 1;
      return _Ch & 0xff;
    }
  }
  return -1;
}

