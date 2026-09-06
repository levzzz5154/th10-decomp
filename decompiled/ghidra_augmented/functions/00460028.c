/* Raw Ghidra reference; not compilable reconstruction. Address: 00460028 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _raise
   
   Library: Visual Studio 2003 Release */

int __cdecl _raise(int _SigNum)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  code *pcVar4;
  void *local_34;
  void *local_30;
  _ptiddata local_28;
  
  bVar1 = false;
  if (_SigNum == 2) {
    puVar3 = &DAT_004776b0;
    pcVar4 = DAT_004776b0;
LAB_004600b5:
    bVar1 = true;
  }
  else {
    if (((_SigNum != 4) && (_SigNum != 8)) && (_SigNum != 0xb)) {
      if (_SigNum == 0xf) {
        puVar3 = &DAT_004776bc;
        pcVar4 = DAT_004776bc;
      }
      else if (_SigNum == 0x15) {
        puVar3 = &DAT_004776b4;
        pcVar4 = DAT_004776b4;
      }
      else {
        if (_SigNum != 0x16) {
          return -1;
        }
        puVar3 = &DAT_004776b8;
        pcVar4 = DAT_004776b8;
      }
      goto LAB_004600b5;
    }
    local_28 = __getptd();
    iVar2 = siglookup();
    puVar3 = (undefined4 *)(iVar2 + 8);
    pcVar4 = (code *)*puVar3;
  }
  if (pcVar4 == (code *)0x1) {
    return 0;
  }
  if (pcVar4 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (bVar1) {
    __lock(0);
  }
  if (((_SigNum == 8) || (_SigNum == 0xb)) || (_SigNum == 4)) {
    local_30 = local_28->_initarg;
    local_28->_initarg = (void *)0x0;
    if (_SigNum == 8) {
      local_34 = local_28->_pxcptacttab;
      local_28->_pxcptacttab = (void *)0x8c;
      goto LAB_00460114;
    }
  }
  else {
LAB_00460114:
    iVar2 = DAT_00473648;
    if (_SigNum == 8) {
      for (; iVar2 < DAT_0047364c + DAT_00473648; iVar2 = iVar2 + 1) {
        *(undefined4 *)((int)local_28->_initaddr + iVar2 * 0xc + 8) = 0;
      }
      goto LAB_00460142;
    }
  }
  *puVar3 = 0;
LAB_00460142:
  FUN_00460163(0);
  if (_SigNum == 8) {
    (*pcVar4)(8,local_28->_pxcptacttab);
  }
  else {
    (*pcVar4)(_SigNum);
    if ((_SigNum != 0xb) && (_SigNum != 4)) {
      return 0;
    }
  }
  local_28->_initarg = local_30;
  if (_SigNum == 8) {
    local_28->_pxcptacttab = local_34;
  }
  return 0;
}

