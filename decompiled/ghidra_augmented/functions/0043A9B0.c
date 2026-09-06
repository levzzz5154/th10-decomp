/* Raw Ghidra reference; not compilable reconstruction. Address: 0043A9B0 */

undefined4 __fastcall FUN_0043a9b0(undefined4 param_1)

{
  void *_Memory;
  int in_EAX;
  byte *pbVar1;
  int unaff_ESI;
  
  if (*(int *)(in_EAX + 0x10) == unaff_ESI) {
    FUN_0043ae20(param_1);
  }
  _Memory = *(void **)(in_EAX + 0x98 + unaff_ESI * 4);
  if (_Memory != (void *)0x0) {
    _free(_Memory);
    *(undefined4 *)(in_EAX + 0x98 + unaff_ESI * 4) = 0;
  }
  *(undefined4 *)(in_EAX + 0x98 + unaff_ESI * 4) = 0;
  pbVar1 = FUN_0044b360((size_t *)0x0,0);
  *(byte **)(in_EAX + 0x98 + unaff_ESI * 4) = pbVar1;
  if (pbVar1 == (byte *)0x0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046f908);
    return 0xffffffff;
  }
  return 0;
}

