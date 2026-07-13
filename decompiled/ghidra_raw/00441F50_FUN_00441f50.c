/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00441F50
 * Tracking name: FUN_00441f50
 * Ghidra name: FUN_00441f50
 * Tracked span: 256 bytes
 */


void __fastcall FUN_00441f50(undefined4 param_1,uint param_2,byte param_3,byte param_4)

{
  int in_EAX;
  
  *(uint *)(in_EAX + 0x230) = param_2 & 0xff;
  *(undefined4 *)(in_EAX + 0x22c) = param_1;
  *(uint *)(in_EAX + 0x20c) = (uint)param_4;
  *(uint *)(in_EAX + 0x208) = (uint)param_3;
  if ((*(uint *)(in_EAX + 0x228) & 1) == 0) {
    *(undefined4 *)(in_EAX + 0x21c) = 0;
    *(undefined4 *)(in_EAX + 0x218) = 0xfff0bdc1;
    *(undefined4 *)(in_EAX + 0x220) = 0;
    *(undefined4 **)(in_EAX + 0x224) = &DAT_00476f78;
    *(uint *)(in_EAX + 0x228) = *(uint *)(in_EAX + 0x228) | 1;
  }
  *(undefined4 *)(in_EAX + 0x21c) = 0;
  *(undefined4 *)(in_EAX + 0x220) = 0;
  *(undefined4 *)(in_EAX + 0x218) = 0xffffffff;
  return;
}

