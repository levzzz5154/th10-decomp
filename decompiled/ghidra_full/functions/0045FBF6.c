/* Raw Ghidra reference; not compilable reconstruction. Address: 0045FBF6 */

undefined4 __cdecl FUN_0045fbf6(int *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint _MaxCharCount;
  
  uVar2 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    _MaxCharCount = *param_1 - param_1[2];
    if (0 < (int)_MaxCharCount) {
      uVar1 = __write(param_1[4],(void *)param_1[2],_MaxCharCount);
      if (uVar1 == _MaxCharCount) {
        if ((char)param_1[3] < '\0') {
          param_1[3] = param_1[3] & 0xfffffffd;
        }
      }
      else {
        param_1[3] = param_1[3] | 0x20;
        uVar2 = 0xffffffff;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar2;
}

