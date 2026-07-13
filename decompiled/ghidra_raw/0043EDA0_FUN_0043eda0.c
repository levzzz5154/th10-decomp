/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043EDA0
 * Tracking name: FUN_0043eda0
 * Ghidra name: FUN_0043eda0
 * Tracked span: 144 bytes
 */


undefined4 * __fastcall FUN_0043eda0(byte param_1,int param_2,ushort param_3)

{
  undefined4 *in_EAX;
  
  if (((uint)param_3 & 1 << (param_1 & 0x1f)) != 0) {
    switch(*in_EAX) {
    case 10000:
      return (undefined4 *)(param_2 + 0x30c);
    case 0x2711:
      return (undefined4 *)(param_2 + 0x310);
    case 0x2712:
      return (undefined4 *)(param_2 + 0x314);
    case 0x2713:
      return (undefined4 *)(param_2 + 0x318);
    case 0x2718:
      return (undefined4 *)(param_2 + 0x32c);
    case 0x2719:
      in_EAX = (undefined4 *)(param_2 + 0x330);
    }
  }
  return in_EAX;
}

