/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040E5F0
 * Tracking name: FUN_0040e5f0
 * Ghidra name: FUN_0040e5f0
 * Tracked span: 176 bytes
 */


undefined4 FUN_0040e5f0(int param_1)

{
  if (-1 < *(int *)(param_1 + 0x2444)) {
    FUN_0043dd10();
  }
  if (-1 < *(int *)(param_1 + 0x2448)) {
    FUN_00448db0(*(undefined2 **)(DAT_00477704 + 0x30 + *(int *)(param_1 + 0x244c) * 4));
  }
  if (0 < *(int *)(param_1 + 0x2408)) {
    FUN_0041bb00((void *)(param_1 + 0x1068),*(int *)(param_1 + 0x2408),0xffffffff,-1.5707964,2.2);
  }
  FUN_0040c9d0((float)(param_1 + 0x2408));
  *(undefined4 *)(param_1 + 0x2408) = 0;
  FUN_00412ff0(10);
  return 1;
}

