/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042C850
 * Tracking name: FUN_0042c850
 * Ghidra name: FUN_0042c850
 * Tracked span: 112 bytes
 */


undefined4 FUN_0042c850(void)

{
  int in_EAX;
  
  if ((((*(char *)(in_EAX + 0x1d888) == '\0') && (*(char *)(in_EAX + 0x1d889) == '\0')) &&
      (*(char *)(in_EAX + 0x1d88a) == '\0')) &&
     (((*(char *)(in_EAX + 0x1d88b) == '\0' && (*(char *)(in_EAX + 0x1d88c) == '\0')) &&
      (*(char *)(in_EAX + 0x1d88d) == '\0')))) {
    return 0;
  }
  return 1;
}

