/* Raw Ghidra reference; not compilable reconstruction. Address: 00460B90 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00460b90(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  ushort local_14;
  undefined4 local_12;
  undefined2 uStack_e;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  iVar3 = 0x473d60;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = 0x473ec0;
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      uVar1 = (int)param_2 >> 3;
      uVar2 = param_2 & 7;
      iVar3 = iVar3 + 0x54;
      param_2 = uVar1;
      if (uVar2 != 0) {
        puVar4 = (ushort *)(iVar3 + uVar2 * 0xc);
        if (0x7fff < *puVar4) {
          local_14 = (ushort)*(undefined4 *)puVar4;
          local_12._0_2_ = (undefined2)((uint)*(undefined4 *)puVar4 >> 0x10);
          local_12._2_2_ = (undefined2)*(undefined4 *)(puVar4 + 2);
          uStack_e = (undefined2)((uint)*(undefined4 *)(puVar4 + 2) >> 0x10);
          uStack_c = *(undefined4 *)(puVar4 + 4);
          local_12 = CONCAT22(local_12._2_2_,(undefined2)local_12) + -1;
          puVar4 = &local_14;
        }
        FUN_0046095a(param_1,(int *)puVar4);
      }
    }
  }
  return;
}

