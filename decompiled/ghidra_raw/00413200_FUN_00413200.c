/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413200
 * Tracking name: FUN_00413200
 * Ghidra name: FUN_00413200
 * Tracked span: 112 bytes
 */


void __fastcall FUN_00413200(int param_1)

{
  int in_EAX;
  
  if (*(int *)(param_1 + 4) != 0) {
    *(int *)(in_EAX + 4) = *(int *)(param_1 + 4);
    *(int *)(*(int *)(param_1 + 4) + 8) = in_EAX;
  }
  *(int *)(param_1 + 4) = in_EAX;
  *(int *)(in_EAX + 8) = param_1;
  return;
}

