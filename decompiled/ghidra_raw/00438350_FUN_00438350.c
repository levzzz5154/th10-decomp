/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00438350
 * Tracking name: FUN_00438350
 * Ghidra name: FUN_00438350
 * Tracked span: 48 bytes
 */


void __thiscall FUN_00438350(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_00438420(this,(undefined4 *)param_1,(int)pcVar2 - (int)(param_1 + 1));
  return;
}

