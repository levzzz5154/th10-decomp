/* Raw Ghidra reference; not compilable reconstruction. Address: 00446B70 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_00446b70(void *this,size_t param_1,undefined4 param_2,undefined4 param_3)

{
  byte *_Memory;
  int iVar1;
  int unaff_ESI;
  size_t local_10c;
  char local_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_10c;
  local_10c = param_1;
  if (((byte)DAT_00491d78 & 1) != 0) {
    iVar1 = *(int *)(&DAT_0046f288 + (int)this * 4);
    if ((iVar1 == 0x15) || (iVar1 == 0)) {
      this = (void *)0x5;
    }
    else if (iVar1 == 0x14) {
      this = (void *)0x3;
    }
  }
  _sprintf(local_108,"%s",param_2);
  _Memory = FUN_0044b360(&local_10c,1);
  if (_Memory != (byte *)0x0) {
    *(size_t *)(unaff_ESI + 8) = local_10c;
    iVar1 = D3DXCreateTextureFromFileInMemoryEx
                      (g_pD3DDevice,_Memory,local_10c,0,0,0,0,
                       *(undefined4 *)(&DAT_0046f288 + (int)this * 4),1,3,0xffffffff,param_3,0,0);
    if (iVar1 == 0) {
      FUN_004465b0();
      *(undefined4 *)(unaff_ESI + 0xc) = *(undefined4 *)(&DAT_0046f2a0 + (int)this * 4);
      *(byte **)(unaff_ESI + 4) = _Memory;
      return 0;
    }
    _free(_Memory);
  }
  return 0xffffffff;
}

